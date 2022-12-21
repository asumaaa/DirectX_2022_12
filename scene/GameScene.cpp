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
	camera_->SetEye({ 0, 0, -30 });

	////球体モデル初期化
	//SphereModel* newSphere = new SphereModel();
	//newSphere->Initialize(size1, dxCommon);
	//sphere_.reset(newSphere);

	//texImg_.resize(texImgCount_);
	//texImg_[0].Initialize(dxCommon, 0);

	//object3ds_.resize(kObjectCount);

	//for (int i = 0; i < object3ds_.size(); i++)
	//{
	//	//初期化
	//	InitializeObject3d(&object3ds_[i], dxCommon->GetDevice());
	//	object3ds_[i].scale = { 1,1.0f,1 };
	//	object3ds_[i].rotation = { 0.0f,0.0f,0.0f };
	//	object3ds_[0].position = { 0.0f,0.0f,0.0f };
	//}

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

	//デバイスをセット
	/*MetaballObject3D::SetDevice(dxCommon_->GetDevice());
	MetaballObject3D::SetCamera(camera_.get());
	MetaballObject3D::CreateGraphicsPipeline();*/

	metaModel1->CreateBuffers(dxCommon_->GetDevice());

	/*metaObject1 = new MetaballObject3D;
	metaObject1->Initialize();
	metaObject1->SetModel(metaModel1);*/
}

void GameScene::Update()
{
	/*XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();*/

	object1->Update();
	/*metaObject1->Update();*/

	camera_->Update();

	/*for (int i = 0; i < object3ds_.size(); i++)
	{
		UpdateObject3d(&object3ds_[i], matView, matProjection);
	}*/

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	/*sphere_->Update();
	texImg_[0].Draw();
	DrawObject3d(&object3ds_[0], dxCommon_->GetCommandList(), sphere_->vbView, sphere_->ibView, sphere_->indices.size());*/

	/*object1->Draw(dxCommon_->GetCommandList());*/
	/*metaObject1->Draw(dxCommon_->GetCommandList());*/
}
