#pragma once
#include "Audio.h"
#include "DebugText.h"
#include <DirectXCommon.h>
#include "Input.h"
#include "Math.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "Windows.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>
#include"EnemyBullet.h"
#include"memory"
#include "list"
#include"Player.h"

class Player;

class Enemy {
public:
	void Initialize(Model* model, uint32_t& textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

	void Approach();	//�ڋ�
	void InitApproach();

	void Leave();	//���E
	void InitLeave();

	void Fire();	//�e����

	void BulletClean();

	void SetPlayer(Player* player){
		player_ = player;
		}
	
	enum class Phase {
		Approach,	//�ڋ�
		Leave,	//���E
	};

	//�ʂ̃C���^�[�o��
	static const int kFireInterval = 3000;

	//���[���h���W�擾
	Vector3 GetWorldPosition();
	
private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Matrix4 matTrans;
	Matrix4 matScale;
	Matrix4 matRotate;

	uint32_t textureHandle_ = 0u;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	Matrix4 matVelocity = MathUtility::Matrix4Identity();	//velocity��p�s��	

	Vector3 transPos = { 0, 0, 0 };

	Matrix4 affinTrans = MathUtility::Matrix4Identity();
	Matrix4 affinRotate = MathUtility::Matrix4Identity();
	Matrix4 affinScale = MathUtility::Matrix4Identity();

	//�ړ��̑���
	const float kEnemyCharacterSpeed = 0.2f;

	//x�����Ɉړ�
	Vector3 move = { kEnemyCharacterSpeed, 0, 0 };

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	//�t�F�[�Y�̑���
	const float kEnemyPhaseCharacterSpeed = 0.1f;

	//���˃^�C�}�[
	int32_t bFireTimer = 0;

	//���@
	Player* player_ = nullptr;
	

};