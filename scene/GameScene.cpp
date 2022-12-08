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

	//FBX�ǂݍ���
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//���f�������w�肵�ăt�@�C���ǂݍ���
	FbxLoader::GetInstance()->LoadModelFromFile("cube");
}

void GameScene::Update()
{
	//�R���g���[���[�X�V
	dxInput->InputProcess();
}

void GameScene::Draw()
{
}
