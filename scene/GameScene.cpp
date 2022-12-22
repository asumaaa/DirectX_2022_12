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

	////FBX読み込み
	//FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());
	////モデル名を指定してファイル読み込み
	//model1 = FbxLoader::GetInstance()->LoadModelFromFile("cube","Resources/cube/Crate.jpg");

	////デバイスをセット
	//FbxObject3D::SetDevice(dxCommon_->GetDevice());
	//FbxObject3D::SetCamera(camera_.get());
	//FbxObject3D::CreateGraphicsPipeline();

	//object1 = new FbxObject3D;
	//object1->Initialize();
	//object1->SetModel(model1);

	//メタボールの設定
	//デバイスをセット
	MetaballObject3D::SetDevice(dxCommon_->GetDevice());
	MetaballObject3D::SetCamera(camera_.get());
	MetaballObject3D::CreateGraphicsPipeline();

	MetaballModel* newMetaModel = new MetaballModel();
	newMetaModel->CreateBuffers(dxCommon_->GetDevice());
	metaModel1.reset(newMetaModel);
	metaModel1->SetImageData({ 0.1, 0.3, 1, 1 });

	MetaballObject3D* newMetaObject = new MetaballObject3D();
	newMetaObject->Initialize();
	metaObject1.reset(newMetaObject);
	metaObject1->SetModel(metaModel1.get());

	metaObject1->SetPosition({ 0,3,0 });
	metaObject1->SetScale({ 3,3,3 });

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
	/*object1->Update();*/

	//モデルの更新
	metaModel1->Update();
	cubeModel1->Update();
	//オブジェクトの更新
	metaObject1->Update();
	cubeObject1->Update();

	camera_->Update();

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	metaObject1->Draw(dxCommon_->GetCommandList());
	cubeObject1->Draw(dxCommon_->GetCommandList());
}
