#include "DebugText.h"
#include "Input.h"
#include <Player.h>
#include <Affin.h>
#include "MathUtility.h"
using namespace MathUtility;

void Player::Initialize(Model* model, uint32_t& textureHandle) {

	// nullcheck
	assert(model);

	//�����������o�ϐ��ɋL�^
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���؃C���X�^���X���擾����
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();

	// X,Y,Z�����X�P�[�����O�ݒ�
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTransform_.translation_ = { 1.0f, 1.0f, 20.0f };

	//3D���e�B�N���̏�����
	worldTransform3DReticle_.Initialize();

	//���e�B�N���p�e�N�X�`��
	uint32_t textureReticle = TextureManager::Load("reticle3.png");

	//�X�v���C�g����
	sprite2DReticle_.reset(Sprite::Create(textureReticle, Vector2(200,100), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

}

void Player::Update(const ViewProjection& viewProjection) {


	//bulletDelete
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//�ړ�
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	//���_�̈ړ�����
	const float kEyeSpeed = 0.02f;

	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_W)) {
		move += {0, kEyeSpeed, 0};
	}
	else if (input_->PushKey(DIK_S)) {
		move -= {0, kEyeSpeed, 0};
	}

	if (input_->PushKey(DIK_A)) {
		move += {-kEyeSpeed, 0, 0};
	}
	else if (input_->PushKey(DIK_D)) {
		move += {kEyeSpeed, 0, 0};
	}

	worldTransform_.translation_ += move;

	//��]
	Vector3 rotateY = { 0.0f,0.0f,0.0f };

	const float kRotateSpeed = 0.01f;
	if (input_->PushKey(DIK_E)) {
		rotateY += {0, kRotateSpeed, 0};
	}
	else if (input_->PushKey(DIK_Q)) {
		rotateY -= {0, kRotateSpeed, 0};
	}
	worldTransform_.rotation_ += rotateY;

	//�A�t�B���s��v�Z
	Affin::AffinUpdate(worldTransform_);

	//�y�A�����g��X�V
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;

	//�A�t�B���s��]��
	worldTransform_.TransferMatrix();

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}


#pragma region ���e�B�N���X�V
	//���@����3D���e�B�N���̋���
	const float kDistancePlayerTo3DReticle = 50.0f;
	//���@����3D���e�B�N���ւ̃I�t�Z�b�gz����
	Vector3 offset = { 0,0,1.0f };
	//���@��world�s��̉�]�𔽉f
	Affin::MatVec(offset, worldTransform_);
	//offset��������
	offset = MathUtility::Vector3Normalize(offset) *  kDistancePlayerTo3DReticle;
	//3D���e�B�N�����W�ݒ�
	Vector3 getWorldMat = Affin::GetVecTrans(worldTransform_.matWorld_);
	worldTransform3DReticle_.translation_ = Affin::AddVector(Affin::GetVecTrans(worldTransform_.matWorld_), offset);

	//�s��X�V
	Affin::AffinUpdate(worldTransform3DReticle_);
	worldTransform3DReticle_.TransferMatrix();


#pragma endregion

#pragma region 3D���e�B�N���ւ̍��W�ϊ�
	Vector3 positionReticle = Affin::GetVecTrans(worldTransform3DReticle_.matWorld_);

	Vector2 windowWH = Vector2(WinApp::GetInstance()->kWindowWidth, WinApp::GetInstance()->kWindowHeight);

	//�r���[�|�[�g�s��
	Matrix4 Viewport =
	{ windowWH.x / 2,0,0,0,
	0,-windowWH.y / 2,0,0,
	0,0,1,0,
	windowWH.x / 2, windowWH.y / 2,0,1 };

	//�r���[�s��ƃv���W�F�N�V�����s��,�r���[�|�[�g�s�����������
	Matrix4 matViewProjectionViewport = viewProjection.matView * viewProjection.matProjection * Viewport;

	//���[���h���X�N���[�����W�ϊ�(������3D�`2D�ɂȂ�)
	positionReticle = Affin::WDiv(positionReticle, matViewProjectionViewport);

	//�X�v���C�g�̃��e�B�N���ɍ��Ɛݒ�
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));


#pragma endregion
}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);


	debugText_->SetPos(50, 110);
	debugText_->Printf(
		"reticle:(%f,%f,%f)", worldTransform3DReticle_.matWorld_.m[3][0], worldTransform3DReticle_.matWorld_.m[3][1], worldTransform3DReticle_.matWorld_.m[3][2]);

}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_V)) {

		const float kBulletSpeed = 0.02f;
		Vector3 velocity(0, 0, kBulletSpeed);
		/*velocity = Affin::GetVecTrans(worldTransform3DReticle_.matWorld_)  - Affin::GetVecTrans(worldTransform_.matWorld_);
		MathUtility::Vector3Normalize(velocity);
		velocity *= kBulletSpeed;*/


		//���x�x�N�g�������@�̌����ɉ�]������
		Affin::MatVec(velocity, worldTransform_);
		
		

		Vector3 worldPos =	//�����l�p���[���h���W�擾
		{	worldTransform_.matWorld_.m[3][0],
			worldTransform_.matWorld_.m[3][1],
			worldTransform_.matWorld_.m[3][2] 
		};

		//�e�𐶐���������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_,worldPos, velocity);

		//�e��o�^
		bullets_.push_back(std::move(newBullet));
	}

}

Vector3 Player::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;

	//���[���h�s��ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision()
{
}

Matrix4 Player::GetMatrix()
{
	return worldTransform_.matWorld_;
}

void Player::SetWorldTransformPair(WorldTransform* worldTransform)
{
	worldTransform_.parent_ = worldTransform;
}

void Player::DrawUI()
{
	sprite2DReticle_->Draw();
}

