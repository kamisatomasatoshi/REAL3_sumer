#include "Enemy.h"
#include "DebugText.h"
#include "Input.h"

void Enemy::Initialize(Model* model, uint32_t& textureHandle)
{

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
	worldTransform_.translation_ = { 2.0f, 1.0f, 6.0f };

}

void Enemy::Update()
{
	

	//�ړ�
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	//���_�̈ړ�����
	const float kEyeSpeed = 0.02f;

	//�����������ňړ��x�N�g����ύX
	/*if (input_->PushKey(DIK_I)) {
		move += {0, kEyeSpeed, 0};
	}
	else if (input_->PushKey(DIK_K)) {
		move -= {0, kEyeSpeed, 0};
	}

	if (input_->PushKey(DIK_J)) {
		move += {-kEyeSpeed, 0, 0};
	}
	else if (input_->PushKey(DIK_L)) {
		move += {kEyeSpeed, 0, 0};
	}*/

	move += {0, 0, -kEyeSpeed};

	worldTransform_.translation_ += move;

	//��]
	Vector3 rotateY = { 0.0f,0.0f,0.0f };

	const float kRotateSpeed = 0.1f;

	/*if (input_->PushKey(DIK_E)) {
		rotateY += {0, kRotateSpeed, 0};
	}
	else if (input_->PushKey(DIK_Q)) {
		rotateY -= {0, kRotateSpeed, 0};
	}
	worldTransform_.rotation_ += rotateY;*/

	//�A�t�B���s��v�Z
	Affin::UpdateRotateY(affinRotate, worldTransform_);
	Affin::UpdateTrans(affinTrans, worldTransform_);
	Affin::UpdateMatrixWorld(affinTrans, affinRotate, worldTransform_);

	//�A�t�B���s��]��
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
