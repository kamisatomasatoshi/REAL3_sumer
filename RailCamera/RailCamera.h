#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include <assert.h>
#include"Affin.h"
#include "Input.h"
#include "DebugText.h"
class RailCamera {
public:
	//������
	void Initialize(WorldTransform worldTransform);

	//�X�V
	void Update();

	//�r���[�v���W�F�N�V�����擾
	ViewProjection GetViewProjection();

	//���[���h�g�����X�t�H�[���擾�p
	WorldTransform* GetWorldTransform();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//�r���[�v���W�F�N�V����
	ViewProjection viewprojection_;

	//�C���v�b�g
	Input* input_ = nullptr;

	//debugtext
	DebugText* debugText_ = nullptr;

	Matrix4 affinTrans = MathUtility::Matrix4Identity();
	Matrix4 affinRotate = MathUtility::Matrix4Identity();
	Matrix4 affinScale = MathUtility::Matrix4Identity();

};

