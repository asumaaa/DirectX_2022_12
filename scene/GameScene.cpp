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
	camera_->SetEye({ 5, 2, -15 });

	//メタボール
	//デバイスをセット
	Metaball::SetDevice(dxCommon_->GetDevice());
	Metaball::SetCamera(camera_.get());
	Metaball::CreateGraphicsPipeline();

	/*Metaball* newMetaball = new Metaball();
	newMetaball->Initialize();
	metaball.reset(newMetaball);
	metaball->SetImageData({ 0.1, 0.3, 1, 1 });
	metaball->SetPosition({ 0,0,0 });
	metaball->SetScale({ 3,3,3 });*/

	for (int i = 0; i < metaballVal; i++)
	{
		std::unique_ptr<Metaball>newMetaball = std::make_unique<Metaball>();
		newMetaball->Initialize();
		if (i == 0)
		{
			newMetaball->SetImageData({ 0.1, 0.3, 1, 1 });
			newMetaball->SetPosition({ 0,0,0 });
			newMetaball->SetScale({ 3,3,3 });
		}
		if (i == 1)
		{
			newMetaball->SetImageData({ 0.1, 0.3, 1, 1 });
			newMetaball->SetPosition({ -5,0,0 });
			newMetaball->SetScale({ 3,3,3 });
		}
		if (i == 2)
		{
			newMetaball->SetImageData({ 0.1, 0.3, 1, 1 });
			newMetaball->SetPosition({ 5,0,0 });
			newMetaball->SetScale({ 3,3,3 });
		}
		metaballs.push_back(std::move(newMetaball));
	}

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

	CubeObject3D* newCubeObject = new CubeObject3D();
	newCubeObject->Initialize();
	cubeObject1.reset(newCubeObject);
	cubeObject1->SetModel(cubeModel1.get());

	cubeObject1->SetScale({ 0.5f,0.5f,0.5f });
	cubeObject1->SetPosition({ 10.0f,0.0f,0.0f });
}

void GameScene::Update()
{
	for (std::unique_ptr<Metaball>& metaball : metaballs)
	{
		metaball->UpdateGravity(cubeObject1->GetPosition());
		metaball->UpdateVertex();
		metaball->Update();
	}

	cubeObject1->Update();

	camera_->Update();


	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	for (std::unique_ptr<Metaball>& metaball : metaballs)
	{
		metaball->Draw(dxCommon_->GetCommandList());
	}
	cubeObject1->Draw(dxCommon_->GetCommandList());
}
