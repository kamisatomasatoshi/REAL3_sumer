#pragma once
#include "Audio.h"
#include "DebugText.h"
#include "DirectXCommon.h"
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

class Player {

  public:
	void Initialize(Model* model, uint32_t& textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection);

  private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Vector3 transPos = {0, 0, 0};

	Matrix4 affinTrans;
};
