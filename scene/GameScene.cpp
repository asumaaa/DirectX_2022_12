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

	//FBX読み込み
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//モデル名を指定してファイル読み込み
	FbxLoader::GetInstance()->LoadModelFromFile("cube");
}

void GameScene::Update()
{
	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
}
