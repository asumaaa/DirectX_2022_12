#pragma once
#include "DirectXMath.h"
#include "Input.h"
#include "WinApp.h"

using namespace DirectX;

//class Camera
//{
//public:
//	//シングルトンインスタンス
//	static Camera* GetInstance();
//	//インストラクタ デストラクタ
//	Camera();
//	~Camera();
//	//初期化
//	void Initialize(Input* input, DXInput* dxInput,Player* player);
//	//更新
//	void Update();
//	void Update2();
//	void TitleUpdate();	//タイトルのカメラの処理
//	void MoveToGameUpdate();	//タイトルのカメラの処理
//	void Phase1RecollectionUpdate();	//フェーズ1のゲーム始まる前の処理
//	void GameClearUpdate();	//フェーズ1のゲーム始まる前の処理
//	//プレイヤーの後ろをつける挙動
//	void homind();
//	void TitleHomind();
//	//ゲッターセッター
//	void SetTarget(XMFLOAT3 pos);
//	void SetEye(XMFLOAT3 pos);
//	void SetGameClear();
//	XMFLOAT3 GetEye() { return eye_; };
//	XMFLOAT3 GetTraget() { return target_; };
//	XMFLOAT3 GetUp() { return up_; };
//	XMMATRIX GetMatProjection() { return matProjection_; };
//	XMMATRIX GetMatView() { return matView_; };
//private:
//	//プレイヤー
//	Player* player_;
//	//入力
//	Input* input_;
//	DXInput* dxInput_;
//	//射影変換
//	XMMATRIX matProjection_;
//	//ビュー変換行列
//	XMMATRIX matView_;
//	XMFLOAT3 eye_ = { -10, 10, 30 };
//	XMFLOAT3 target_ = { 0, 0, 0 };
//	XMFLOAT3 up_ = { 0, 1, 0 };
//	//プレイヤーの後ろをつける挙動
//	//プレイヤーとカメラの距離
//	float length_ = 40.0f;
//	float titleLength_ = 30.0f;
//	//入力によって加算させる変数
//	float lengthX_ = 0.0f;
//	float lengthZ_ = 0.0f;
//
//	//シーン用
//	//ゲームに移る時のタイマー
//	float moveToGameTimer_ = 0;
//
//	//フェーズ1のゲーム始まる前のタイマー
//	float phase1RecollectionTimer_ = 0;
//public:
//	void phase1RecollectionTimerReset() { phase1RecollectionTimer_ = 0; };
//};

