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

	InitApproach();

	

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

	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//�e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

//�G�̋���something
void Enemy::Approach() {

	BulletClean();

	//���˃^�C�}�[�̃J�E���g�_�E��
	bFireTimer--;
	//�w�莞�ԂɒB����
	if (bFireTimer <= 0) {
		//�e�𔭎�
		Fire();
		//���˃^�C�}�[������
		bFireTimer = kFireInterval;
	}
	
	/////////////////���e�̔��ˁ�/////////////////
	
	//�ړ��x�N�g��
	worldTransform_.translation_ += Vector3(0, 0, +kEnemyPhaseCharacterSpeed);

	//����̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z > 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::InitApproach()
{
	bFireTimer = kFireInterval;
}

void Enemy::Leave() {
	BulletClean();

	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_ += Vector3(0, 0, -kEnemyPhaseCharacterSpeed);

	//����̈ʒu�ɓ��B�����痣�E
	if(worldTransform_.translation_.z < -30.0f) {
		phase_ = Phase::Approach;
	}
}

void Enemy::Fire() {

	const float kBulletSpeed = 0.02f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	//���x�x�N�g�������@�̌����ɉ�]������
	Affin::VectorUpdate(velocity, worldTransform_);
	
	Vector3 PlayerVec = player_->GetWorldPosition();
	Vector3 EnemyVec = GetWorldPosition();

	Vector3 Vec = Vector3(PlayerVec.x - EnemyVec.x, PlayerVec.y - EnemyVec.y, PlayerVec.z - EnemyVec.z);	//���F�N�g���̈����Z
	//Vector3 normalizeVec = MathUtility::Vector3Normalize(Vec);	//���K��
	//�X�s�[�h�͐��K�������l�̂܂�(1.0f)
	float nomalize = sqrt(Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z) * 100;
	Vec = Vector3(Vec.x / nomalize, Vec.y / nomalize, Vec.z / nomalize);
	


	//�e�𐶐���������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, Vec);

	//�e��o�^
	bullets_.push_back(std::move(newBullet));

}

void Enemy::BulletClean()
{
	//�f�X�t���O���������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
	});
}

Vector3 Enemy::GetWorldPosition()
{
		//���[���h���W������ϐ�
		Vector3 worldPos;

		//���[���h�s��ړ��������擾(���[���h���W)
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];

		return worldPos;
	
}
