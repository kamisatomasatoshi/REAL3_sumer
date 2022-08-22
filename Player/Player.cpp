#include "DebugText.h"
#include "Input.h"
#include "Player/Player.h"

void Player::Initialize(Model* model, uint32_t &textureHandle) {

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
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {1.0f, 1.0f, 1.0f};

}

void Player::Update() {


		//�ړ�
		Vector3 move = {0.0f, 0.0f, 0.0f};

		//���_�̈ړ�����
		const float kEyeSpeed = 0.2f;

		//�����������ňړ��x�N�g����ύX
		if (input_->PushKey(DIK_W)) {
			move += {0, kEyeSpeed, 0};
		} else if (input_->PushKey(DIK_S)) {
			move -= {0, kEyeSpeed, 0};
		}

		if (input_->PushKey(DIK_A)) {
			move += {-kEyeSpeed, 0, 0};
		} else if (input_->PushKey(DIK_D)) {
			move += {kEyeSpeed, 0, 0};
		}

		worldTransform_.translation_ += move;

		//��]
		Vector3 rotateY = { 0.0f,0.0f,0.0f };

		const float kRotateSpeed = 0.1f;
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
		Affin::UpdateMatrixWorld(affinTrans, affinRotate, worldTransform_);

		//�A�t�B���s��]��
		worldTransform_.TransferMatrix();

	
}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

void Player::Attack()
{
	if (input_->PushKey(DIK_V)) {

		//�e�𐶐���������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_,worldTransform_.translation_);

		//�e��o�^
		bullet_ = newBullet;
	}

}
