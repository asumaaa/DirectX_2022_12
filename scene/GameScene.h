#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "object3D.h"
#include "list"
#include "memory"
#include "Texture.h"
#include "Model.h"
#include "Object3D.h"
#include "Sound.h"
#include "Camera.h"
#include "DXInput.h"
#include "Sprite.h"
#include "FbxObject3D.h"
#include "FbxModel.h"
#include "Metaball.h"
#include "CubeModel.h"
#include "CubeObject3D.h"
#include "WaterSurface.h"
#include "Collision.h"

class GameScene
{
	//メンバ関数
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Initialize();
	void Update();
	void Draw();
	void Reset();

	//メンバ変数
private: 
	//デバイスとinput
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//コントローラ
	DXInput* dxInput = new DXInput();
	//カメラ
	std::unique_ptr<Camera> camera_;

	size_t metaballVal = 1;
	std::unique_ptr<Metaball>metaball;

	//キューブ
	std::unique_ptr<CubeModel> cubeModel1;
	std::unique_ptr<CubeModel> cubeModel2;

	//ステージに使うタイル
	std::list<std::unique_ptr<CubeObject3D>> tiles;
	size_t tileVal = 61;

	//当たり判定
	std::list<std::unique_ptr<Collision>> collisions;

	//スクロールのベクトル
	DirectX::XMFLOAT3 scrollVector = {0,0,0};
	//カメラの位置
	DirectX::XMFLOAT3 eye = { -45,45, -45 };
	DirectX::XMFLOAT3 target = { 0,0, 0 };

	//ゲームのタイマー
	float GameTimer = 0;
	float PI = 3.14159265359f;

	int tileFlag[61];
	int preTileFlag[61];

	//スプライト
	//スプライト共通データ生成
	SpriteCommon spriteCommon_;
	Sprite* sprite_ = new Sprite;
	Sprite sprite1;	//title.png
	Sprite sprite2;	//title.png
	Sprite sprite3;	//title.png
	Sprite sprite4;	//title.png
	Sprite sprite5;	//title.png
	Sprite sprite6;	//title.png
	Sprite sprite7;	//title.png
	Sprite sprite8;	//title.png

	//0title 1game 2retory
	int gameState = 0;

	int tileCount = 0;

	float deadLine = 0;
};
