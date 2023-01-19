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
#include "Player.h"
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

	//メンバ変数
private: 
	//デバイスとinput
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//コントローラ
	DXInput* dxInput = new DXInput();
	//カメラ
	std::unique_ptr<Camera> camera_;

	std::unique_ptr<WaterSurface> waterSurface;

	//キューブ
	std::unique_ptr<CubeModel> cubeModel1;

	//プレイヤー
	std::unique_ptr<Player> player;

	//当たり判定
	std::list<std::unique_ptr<Collision>> collisions;
};
