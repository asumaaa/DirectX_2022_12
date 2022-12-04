#include "GameScene.h"

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
}

void GameScene::Update()
{
	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
}
