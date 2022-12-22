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
	camera_->SetEye({ 3, 3, -15 });

	//メタボール
	//デバイスをセット
	Metaball::SetDevice(dxCommon_->GetDevice());
	Metaball::SetCamera(camera_.get());
	Metaball::CreateGraphicsPipeline();

	Metaball* newMetaball = new Metaball();
	newMetaball->Initialize();
	metaball.reset(newMetaball);
	metaball->SetImageData({ 0.1, 0.3, 1, 1 });
	metaball->SetPosition({ 0,3,0 });
	metaball->SetScale({ 3,3,3 });

	Metaball* newMetaball2 = new Metaball();
	newMetaball2->Initialize();
	metaball2.reset(newMetaball2);
	metaball2->SetImageData({ 1, 0.3, 1, 1 });
	metaball2->SetPosition({ 3,3,0 });
	metaball2->SetScale({ 3,3,3 });

	//キューブの設定
	//デバイスをセット
	CubeObject3D::SetDevice(dxCommon_->GetDevice());
	CubeObject3D::SetCamera(camera_.get());
	CubeObject3D::CreateGraphicsPipeline();

	CubeModel* newCubeModel = new CubeModel();
	newCubeModel->CreateBuffers(dxCommon_->GetDevice());
	cubeModel1.reset(newCubeModel);
	cubeModel1->SetImageData({ 0.2, 0.2, 0.2,1 });

	CubeObject3D* newCubeObject = new CubeObject3D();
	newCubeObject->Initialize();
	cubeObject1.reset(newCubeObject);
	cubeObject1->SetModel(cubeModel1.get());

	cubeObject1->SetScale({ 10.0f,0.2f,10.0f });
}

void GameScene::Update()
{
	//メタボール更新
	metaball->Update();
	metaball2->Update();

	//キューブモデル更新
	cubeModel1->Update();
	//オブジェクトの更新
	cubeObject1->Update();

	camera_->Update();

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	metaball->Draw(dxCommon_->GetCommandList());
	metaball2->Draw(dxCommon_->GetCommandList());
	cubeObject1->Draw(dxCommon_->GetCommandList());
}
