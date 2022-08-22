#include "PlayerBullet.h"


void PlayerBullet::Initialize(Model* model, const Vector3& position)
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
}

void PlayerBullet::Update()
{

}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}