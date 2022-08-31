#include "RailCamera.h"


void RailCamera::Initialize(WorldTransform worldTransform)
{
	//���[���h���W������
	worldTransform_.translation_ = worldTransform.translation_;
	worldTransform_.rotation_ = worldTransform.rotation_;
	worldTransform_.Initialize();

	//�r���[�v���W�F�N�V����������
	viewprojection_.Initialize();



	//�C���X�^���X�擾
	input_ = Input::GetInstance();

}

void RailCamera::Update()
{

	//�ړ�
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	//���_�̈ړ�����
	const float kEyeSpeed = 0.2f;

	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_Y)) {
		move += {0, kEyeSpeed, 0};
	}
	else if (input_->PushKey(DIK_H)) {
		move -= {0, kEyeSpeed, 0};
	}

	if (input_->PushKey(DIK_G)) {
		move += {-kEyeSpeed, 0, 0};
	}
	else if (input_->PushKey(DIK_J)) {
		move += {kEyeSpeed, 0, 0};
	}

	worldTransform_.translation_ += move;

	//��]
	Vector3 rotateY = { 0.0f,0.0f,0.0f };

	const float kRotateSpeed = 0.01f;
	if (input_->PushKey(DIK_T)) {
		rotateY += {0, kRotateSpeed, 0};
	}
	else if (input_->PushKey(DIK_U)) {
		rotateY -= {0, kRotateSpeed, 0};
	}
	worldTransform_.rotation_ += rotateY;

	//�A�t�B���s��v�Z
	Affin::UpdateRotateY(affinRotate, worldTransform_);
	Affin::UpdateTrans(affinTrans, worldTransform_);
	Affin::UpdateMatrixWorld(affinScale, affinTrans, affinRotate, worldTransform_);

	//�A�t�B���s��]��
	worldTransform_.TransferMatrix();

	viewprojection_.eye = worldTransform_.translation_;
	//���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	Affin::VectorUpdate(forward, worldTransform_);
	//���_����O���ɐi�񂾈ʒu�������X
	viewprojection_.target = viewprojection_.eye + forward;
	//world����x�N�g��
	Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f
	Affin::VectorUpdate(up, worldTransform_);
	//�r���[�v���W�F�N�V�������X�V
	viewprojection_.UpdateMatrix();
	viewprojection_.TransferMatrix();

}

ViewProjection RailCamera::GetViewProjection()
{
	return viewprojection_;
}

WorldTransform* RailCamera::GetWorldTransform()
{
	return &worldTransform_;
}
