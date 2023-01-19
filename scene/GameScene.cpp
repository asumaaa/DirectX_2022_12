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
	camera_->SetEye({ 0, 15, -40 });

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


	CubeModel* newCubeModel2 = new CubeModel();
	newCubeModel2->CreateBuffers(dxCommon_->GetDevice());
	cubeModel2.reset(newCubeModel2);
	cubeModel2->SetImageData({ 0.8f, 0.1f, 0.1f,0.7f });

	//プレイヤーの初期化
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon_->GetDevice(), cubeModel1.get(), input,dxInput);
	player.reset(newPlayer);
	//行列設定
	player->SetScale({ 1.0f,1.0f,1.0f });
	player->SetRotation({ 0.0f,0.0f,0.0f });
	player->SetPosition({ 0.0f,4.0f,0.0f });

	CubeObject3D* newCubeObject = new CubeObject3D();
	newCubeObject->Initialize();
	cubeObject1.reset(newCubeObject);
	cubeObject1->SetModel(cubeModel2.get());

	cubeObject1->SetScale({ 30.0f,0.5f,30.0f });
	cubeObject1->SetPosition({ 0.0f,0.0f,0.0f });
	cubeObject1->SetPosition({ 0.0f,0.0f,0.0f });

	//当たり判定
	for (int i = 0; i < 1; i++)
	{
		std::unique_ptr<Collision>newCollision = std::make_unique<Collision>();
		newCollision->SetObject(cubeObject1->GetPosition(), cubeObject1->GetScale());
		collisions.push_back(std::move(newCollision));
	}
}

void GameScene::Update()
{
	waterSurface->Update();

	for (std::unique_ptr<Collision>& collision : collisions)
	{
		player->UpdateCollision(collision.get());
	}
	player->Update();

	camera_->Update();

	cubeObject1->Update();

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	/*waterSurface->Draw(dxCommon_->GetCommandList());*/
	cubeObject1->Draw(dxCommon_->GetCommandList());
	player->Draw(dxCommon_->GetCommandList());
}
