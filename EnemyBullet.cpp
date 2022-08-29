#include "EnemyBullet.h"


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{

	assert(model);

	model_ = model;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("mario.jpg");


	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };

	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };

	Affin::UpdateTrans(matTrans, worldTransform_);
	Affin::UpdateMatrixWorld(matTrans, matRotate, worldTransform_);

	worldTransform_.TransferMatrix();

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void EnemyBullet::Update()
{
	//TimerDeath
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}



	//���W���ړ�������
	worldTransform_.translation_ += velocity_;

	//�A�t�B���s��v�Z
	Affin::UpdateRotateY(matRotate, worldTransform_);
	Affin::UpdateTrans(matTrans, worldTransform_);
	Affin::UpdateMatrixWorld(matTrans, matRotate, worldTransform_);

	worldTransform_.TransferMatrix();

}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}