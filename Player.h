#pragma once
#include "CubeModel.h"
#include "CubeObject3D.h"
#include "DirectXCommon.h"
#include "DXInput.h"
#include "input.h"
#include "Collision.h"

class Player
{
public:
	//シングルトンインスタンス
	Player* GetInstance();
	Player();
	~Player();
	void Initialize(ID3D12Device* device, CubeModel* model, Input* input,DXInput* dxInput);
	void Update();
	void Move();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//当たり判定
	void UpdateCollision(Collision* collision);

	//ゲッター　セッター　
	XMFLOAT3 GetPosition() { return position; };
	XMFLOAT3 GetRotation() { return rotation; };
	XMFLOAT3 GetScale() { return scale; };
	void SetPosition(XMFLOAT3 pos);
	void SetRotation(XMFLOAT3 rot);
	void SetScale(XMFLOAT3 sca);
private:
	ID3D12Device* device;
	CubeModel* model = nullptr;
	std::unique_ptr<CubeObject3D> object3d;
	DXInput* dxInput;
	Input* input;
	//アフィン変換情報
	XMFLOAT3 scale = { 1,1,1 };
	XMFLOAT3 rotation = { 0,0,0 };	//プレイヤー本来の角度
	XMFLOAT3 position = { 0,0,0 };

	//移動用変数
	XMFLOAT3 fallVelocity = { 0,0,0 };
	float fallTimer = 0.0f;

	bool groundFlag = false;
};

