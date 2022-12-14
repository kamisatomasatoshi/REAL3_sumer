#include "Player.h"
#include "DebugText.h"
#include "Input.h"

void Player::Initialize(Model* model, uint32_t &textureHandle) {

	affinTrans = {
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f,
	    0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
	};


	// nullcheck
	assert(model);

	//引数をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;

	//シングル豚インスタンスを取得する
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	
	// X,Y,Z方向スケーリング設定
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {1.0f, 1.0f, 1.0f};

}

void Player::Update() {

	//視点の移動ベクトル
	{
		Vector3 move = {0.0f, 0.0f, 0.0f};

		//視点の移動速さ
		const float kEyeSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
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

		affinTrans = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
		    0.0f, 0.0f, 1.0f, 0.0f, 
            move.x, move.y, move.z, 1.0f
		};

		worldTransform_.matWorld_ *= affinTrans;

		worldTransform_.TransferMatrix();

		

	}
}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
