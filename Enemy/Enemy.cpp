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
	worldTransform_.translation_ = { 2.0f, 1.0f, -20.0f };

}

void Enemy::Update()
{



	//�A�t�B���s��v�Z
	Affin::UpdateRotateY(affinRotate, worldTransform_);
	Affin::UpdateTrans(affinTrans, worldTransform_);
	Affin::UpdateMatrixWorld(affinTrans, affinRotate, worldTransform_);

	//�A�t�B���s��]��
	worldTransform_.TransferMatrix();

	//�G�̓�����switch�Ő؂�ւ�
	switch (phase_) {
	case Phase::Approach:

	default:
		Approach();
		break;

	case Phase::Leave:
		Leave();
		break;
	}

}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


//�G�̋���something
void Enemy::Approach() {

	//�ړ��x�N�g��
	worldTransform_.translation_ += Vector3(0, 0, +kEnemyPhaseCharacterSpeed);

	//����̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z > 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {

	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_ += Vector3(0, 0, -kEnemyPhaseCharacterSpeed);
}