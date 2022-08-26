﻿#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0; //テクスチャハンドル
	uint32_t textureHandle2_ = 0;
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;
	//自キャラ
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	//スプライト
	Sprite* sprite_ = nullptr;
	Model* model_ = nullptr;
	Model* enemyModel_ = nullptr;

	//ワールドトランスフォーム初期化
	WorldTransform worldTransform_;
	WorldTransform enemyWorldTransform_;

	//ビュープロジェクション初期化
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	///
};
