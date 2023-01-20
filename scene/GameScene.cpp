#include "GameScene.h"
#include "FbxLoader.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete dxInput;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	HRESULT result;
	this->dxCommon_ = dxCommon;
	this->input_ = input;

	//モデル初期化
	Model* newModel = new Model();
	newModel->Initialize(dxCommon_->GetDevice(), "fighter", "Resources/fighter.png");
	model_.reset(newModel);
	//オブジェクト初期化
	Object3D* newObject = new Object3D();
	newObject->Initialize(dxCommon_->GetDevice(), model_.get());
	newObject->setScale({ 10,10,10 });
	newObject->setPosition({50,0,0});
	object3D1_.reset(newObject);

	//モデル初期化
	Model* newModel2 = new Model();
	newModel2->Initialize(dxCommon_->GetDevice(), "boss", "Resources/boss.png");
	model2_.reset(newModel2);
	//オブジェクト初期化
	Object3D* newObject2 = new Object3D();
	newObject2->Initialize(dxCommon_->GetDevice(), model2_.get());
	newObject2->setScale({ 10,10,10 });
	newObject2->setPosition({ -50,0,0 });
	object3D2_.reset(newObject2);

	//カメラ初期化
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_);
	camera_.reset(newCamera);
	camera_->SetTarget({ 0,0,0 });
	camera_->SetEye({ -10, 15, -150 });
}

void GameScene::Update()
{
	XMMATRIX m1 = camera_->GetMatView();
	XMMATRIX m2 = camera_->GetMatViewProjection();

	object3D1_->Update(m1, m2);
	object3D2_->Update(m1, m2);

	camera_->Update();

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	object3D1_->Draw(dxCommon_->GetCommandList(), model_->vbView, model_->ibView);
	object3D2_->Draw(dxCommon_->GetCommandList(),model2_->vbView, model2_->ibView);
}
