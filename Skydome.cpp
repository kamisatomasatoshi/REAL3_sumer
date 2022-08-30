#include "Skydome.h"


void Skydome::Initialize(Model* model)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	// X,Y,Z�����X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 1.0f, 1.0f, 1.0f };
	worldTransform_.translation_ = { 1.0f, 1.0f, 1.0f };
	worldTransform_.scale_ = { 100.0f, 100.0f, 100.0f };

	Affin::UpdateScale(affinScale, worldTransform_);
	Affin::UpdateMatrixWorld(affinScale, affinTrans, affinRotate, worldTransform_);

	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Skydome::Update()
{
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

