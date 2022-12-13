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

	//カメラ初期化
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_);
	camera_.reset(newCamera);
	camera_->SetTarget({ 0,20,0 });
	camera_->SetEye({ 30, 30, -150 });

	//FBX読み込み
	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());
	//モデル名を指定してファイル読み込み
	/*FbxLoader::GetInstance()->LoadModelFromFile("cube");*/
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("cube","Resources/cube/Crate.jpg");

	//デバイスをセット
	FbxObject3D::SetDevice(dxCommon_->GetDevice());
	FbxObject3D::SetCamera(camera_.get());
	FbxObject3D::CreateGraphicsPipeline();

	object1 = new FbxObject3D;
	object1->Initialize();
	object1->SetModel(model1);
}

void GameScene::Update()
{
	object1->Update();

	camera_->Update();
	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	object1->Draw(dxCommon_->GetCommandList());
}
