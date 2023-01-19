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
	camera_->SetTarget({ 0,0,0 });
	camera_->SetEye({ 0, 10, -20 });

	//水面
	WaterSurface::SetDevice(dxCommon_->GetDevice());
	WaterSurface::SetCamera(camera_.get());
	WaterSurface::CreateGraphicsPipeline();
	WaterSurface* newWaterSurface = new WaterSurface();
	newWaterSurface->Initialize();
	newWaterSurface->SetImageData({ 0.1, 0.3, 1, 1 });
	newWaterSurface->SetPosition({ 0,0,0 });
	newWaterSurface->SetScale({ 15,15,15 });
	waterSurface.reset(newWaterSurface);

	//キューブの設定
	//デバイスをセット
	CubeObject3D::SetDevice(dxCommon_->GetDevice());
	CubeObject3D::SetCamera(camera_.get());
	CubeObject3D::SetInput(input_);
	CubeObject3D::CreateGraphicsPipeline();

	CubeModel* newCubeModel = new CubeModel();
	newCubeModel->CreateBuffers(dxCommon_->GetDevice());
	cubeModel1.reset(newCubeModel);
	cubeModel1->SetImageData({ 1.0f, 1.0f, 1.0f,1.0f });

	//プレイヤーの初期化
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon_->GetDevice(), cubeModel1.get(), input,dxInput);
	player.reset(newPlayer);
	//行列設定
	player->SetScale({ 1.0f,1.0f,1.0f });
	player->SetRotation({ 0.0f,0.0f,0.0f });
	player->SetPosition({ 0.0f,0.0f,0.0f });
}

void GameScene::Update()
{
	waterSurface->Update();

	player->Update();

	camera_->Update();

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	waterSurface->Draw(dxCommon_->GetCommandList());
	player->Draw(dxCommon_->GetCommandList());
}
