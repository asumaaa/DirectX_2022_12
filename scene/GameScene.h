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
//#include "SphereObject3D.h"
//#include "SphereModel.h"
//#include "SphereSprite.h"
//#include "MetaballModel.h"
//#include "MetaballObject3D.h"
#include "Metaball.h"
#include "CubeModel.h"
#include "CubeObject3D.h"

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

	////fbx
	//FbxModel* model1 = nullptr;
	//FbxObject3D* object1 = nullptr;

	//メタボール
	//std::unique_ptr<MetaballModel> metaModel1;
	//std::unique_ptr<MetaballObject3D> metaObject1;

	std::unique_ptr<Metaball> metaball;
	std::unique_ptr<Metaball> metaball2;

	//キューブ
	std::unique_ptr<CubeModel> cubeModel1;
	std::unique_ptr<CubeObject3D> cubeObject1;
};
