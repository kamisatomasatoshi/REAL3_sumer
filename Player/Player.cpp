#include "DebugText.h"
#include "Input.h"
#include <Player.h>
#include <Affin.h>

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
	worldTransform_.translation_ = { 1.0f, 1.0f, 1.0f };

}

void Player::Update() {

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
	Affin::UpdateRotateY(affinRotate, worldTransform_);
	Affin::UpdateTrans(affinTrans, worldTransform_);
	Affin::UpdateMatrixWorld(affinScale, affinTrans, affinRotate, worldTransform_);

	//�A�t�B���s��]��
	worldTransform_.TransferMatrix();

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}


}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}


}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_V)) {

		const float kBulletSpeed = 0.02f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//���x�x�N�g�������@�̌����ɉ�]������
		Affin::VectorUpdate(velocity, worldTransform_);

		//�e�𐶐���������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

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
