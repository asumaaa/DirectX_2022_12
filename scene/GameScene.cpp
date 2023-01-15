#include "GameScene.h"
#include "FbxLoader.h"
#include "Math2.h"
#include "vector"
#include<fstream>
#include "sstream"
#include "stdio.h"
#include "string.h"

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
	camera_->SetTarget(target);
	camera_->SetEye(eye);

	//メタボール
	//デバイスをセット
	Metaball::SetDevice(dxCommon_->GetDevice());
	Metaball::SetCamera(camera_.get());
	Metaball::CreateGraphicsPipeline();

	Metaball* newMetaball = new Metaball();
	newMetaball->Initialize();
	newMetaball->SetInput(input_);
	newMetaball->SetImageData({ 1.0, 1.0, 1.0, 1 });
	newMetaball->SetPosition({ 0,10,0 });
	newMetaball->SetScale({ 3,3,3 });
	metaball.reset(newMetaball);

	//キューブの設定
	//デバイスをセット
	CubeObject3D::SetDevice(dxCommon_->GetDevice());
	CubeObject3D::SetCamera(camera_.get());
	CubeObject3D::SetInput(input_);
	CubeObject3D::CreateGraphicsPipeline();

	CubeModel* newCubeModel = new CubeModel();
	newCubeModel->CreateBuffers(dxCommon_->GetDevice());
	cubeModel1.reset(newCubeModel);
	cubeModel1->SetImageData({ 0.0f, 0.3f, 0.3f,1.0f });

	CubeModel* newCubeModel2 = new CubeModel();
	newCubeModel2->CreateBuffers(dxCommon_->GetDevice());
	cubeModel2.reset(newCubeModel2);
	cubeModel2->SetImageData({ 0.7f, 0.7f, 0.7f,1.0f });
	
	//ファイル読み込み
	std::stringstream tileList;	//文字列
	std::vector<DirectX::XMFLOAT3>tilePos;
	//ファイルを開く
	std::ifstream file;
	file.open("stage.csv");
	//ファイルの内容をコピー
	tileList << file.rdbuf();
	//ファイルを閉じる
	file.close();

	std::string line;

	while (getline(tileList, line, '{'))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		std::string word1;
		std::string word2;
		std::string word3;
		//カンマ区切りで先頭文字列を取得
		getline(line_stream, word1, ',');
		getline(line_stream, word2, ',');
		getline(line_stream, word3, ',');
		DirectX::XMFLOAT3 pos(atoi(word1.c_str()), atoi(word2.c_str()), atoi(word3.c_str()));
		tilePos.push_back(pos);
	}

	//tileと当たり判定初期化
	for (int i = 0; i < tileVal; i++)
	{
		std::unique_ptr<CubeObject3D>newTile = std::make_unique<CubeObject3D>();
		std::unique_ptr<Collision>newCollision = std::make_unique<Collision>();
		newTile->Initialize();
		if (i <= 1)
		{
			newTile->SetModel(cubeModel2.get());
		}
		else
		{
			newTile->SetModel(cubeModel1.get());
		}
		newTile->SetScale({ 23.0f,0.5f,23.0f });
		newTile->SetPosition({ tilePos[i].x,tilePos[i].y,tilePos[i].z });

		newCollision->SetObject(newTile->GetPosition(), newTile->GetScale());
		tiles.push_back(std::move(newTile));
		collisions.push_back(std::move(newCollision));
	}

	//スプライト初期化
	spriteCommon_ = sprite_->SpriteCommonCreate(dxCommon_->GetDevice(), 1280, 720);
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/moveText.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 1, L"Resources/jumpText.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 2, L"Resources/title2.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 3, L"Resources/pushText.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 4, L"Resources/retryText.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 5, L"Resources/rankC.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 6, L"Resources/rankB.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 7, L"Resources/rankA.png", dxCommon_->GetDevice());
	sprite1.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite1.SetTexNumber(0);
	sprite1.SetPosition(XMFLOAT3(0, 0, 0));
	sprite1.SetScale(XMFLOAT2(380, 50));
	sprite1.SpriteTransferVertexBuffer(sprite1);
	sprite1.SpriteUpdate(sprite1, spriteCommon_);

	sprite2.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite2.SetPosition(XMFLOAT3(0, 50, 0));
	sprite2.SetScale(XMFLOAT2(380, 50));
	sprite2.SetTexNumber(1);
	sprite2.SpriteTransferVertexBuffer(sprite2);
	sprite2.SpriteUpdate(sprite2, spriteCommon_);

	sprite3.SpriteCreate(dxCommon_->GetDevice(), 700, 200);
	sprite3.SetTexNumber(2);
	sprite3.SetPosition(XMFLOAT3(250, 100, 0));
	sprite3.SetScale(XMFLOAT2(700, 200));
	sprite3.SpriteTransferVertexBuffer(sprite3);
	sprite3.SpriteUpdate(sprite3, spriteCommon_);

	sprite4.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite4.SetTexNumber(3);
	sprite4.SetPosition(XMFLOAT3(400, 630, 0));
	sprite4.SetScale(XMFLOAT2(350, 80));
	sprite4.SpriteTransferVertexBuffer(sprite4);
	sprite4.SpriteUpdate(sprite4, spriteCommon_);

	sprite5.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite5.SetTexNumber(4);
	sprite5.SetPosition(XMFLOAT3(100, 630, 0));
	sprite5.SetScale(XMFLOAT2(350, 80));
	sprite5.SpriteTransferVertexBuffer(sprite5);
	sprite5.SpriteUpdate(sprite5, spriteCommon_);

	sprite6.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite6.SetTexNumber(5);
	sprite6.SetPosition(XMFLOAT3(500, 300, 0));
	sprite6.SetScale(XMFLOAT2(350, 80));
	sprite6.SpriteTransferVertexBuffer(sprite6);
	sprite6.SpriteUpdate(sprite6, spriteCommon_);

	sprite7.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite7.SetTexNumber(6);
	sprite7.SetPosition(XMFLOAT3(500, 300, 0));
	sprite7.SetScale(XMFLOAT2(350, 80));
	sprite7.SpriteTransferVertexBuffer(sprite7);
	sprite7.SpriteUpdate(sprite7, spriteCommon_);

	sprite8.SpriteCreate(dxCommon_->GetDevice(), 350, 80);
	sprite8.SetTexNumber(7);
	sprite8.SetPosition(XMFLOAT3(500, 300, 0));
	sprite8.SetScale(XMFLOAT2(350, 80));
	sprite8.SpriteTransferVertexBuffer(sprite8);
	sprite8.SpriteUpdate(sprite8, spriteCommon_);


	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite_->SpriteCreateGraphicsPipeline(dxCommon_->GetDevice());
}


void GameScene::Update()
{

	if (gameState == 0)
	{
		if (input_->PushKey(DIK_SPACE))
		{
			gameState = 1;
		}
	}
	//タイマー更新
	if (gameState == 1)
	{
		GameTimer += 10.0f / 60.0f;
	}

	int i = 0;
	for (std::unique_ptr<Collision>& collision : collisions)
	{
		tileFlag[i] = 0;
		if (collision->Update(metaball->GetPosition(), metaball->GetScale()))
		{
			tileFlag[i] = 1;
		}
		metaball->UpdateCollision(collision.get());
		i++;
	}
	metaball->Update();

	i = 0;
	for (std::unique_ptr<CubeObject3D>& tile : tiles)
	{
		if (preTileFlag[i] == 0 && tileFlag[i] == 1)
		{
			tileCount++;
			tile->SetModel(cubeModel2.get());
			if (i == 60)
			{
				gameState = 2;
			}
		}
		tile->Update();
		i++;
	}

	for (int j = 0; j < tileVal; j++)
	{
		preTileFlag[j] = tileFlag[j];
	}

	if (metaball->GetPosition().y < -10.0f)
	{
		gameState = 2;
	}
	
	/*if (metaball->GetPosition().x <= deadLine)
	{
		gameState = 2;
	}*/

	if (gameState == 2)
	{
		if (input_->PushKey(DIK_SPACE))
		{
			Reset();
		}
	}

	//カメラ
	//タイマーでカメラ移動
	eye.x = -45 + (GameTimer * (PI * 1.0f / 2.0f));
	target.x = (GameTimer * (PI * 1.0f / 2.0f));
	deadLine += (GameTimer * (PI * 1.0f / 2.0f)) - 150;
	camera_->SetTarget(target);
	camera_->SetEye(eye);
	camera_->Update();

	//コントローラー更新
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	metaball->Draw(dxCommon_->GetCommandList());
	for (std::unique_ptr<CubeObject3D>& tile : tiles)
	{
		tile->Draw(dxCommon_->GetCommandList());
	}

	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);
	if (gameState == 0)
	{
		sprite3.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite3.vbView);
		sprite4.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite4.vbView);
	}
	sprite1.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite1.vbView);
	sprite2.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite2.vbView);

	if (gameState == 2)
	{
		if (tileCount < 20)
		{
			sprite6.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite6.vbView);
		}
		else if (tileCount >= 20 && tileCount < 40)
		{
			sprite7.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite7.vbView);
		}
		else
		{
			sprite8.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite8.vbView);
		}
		sprite5.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite5.vbView);
		sprite4.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), sprite4.vbView);
	}
}

void GameScene::Reset()
{
	tileCount = 0;
	GameTimer = 0;
	eye = { -45,45, -45 };
	target = { 0,0, 0 };
	metaball->SetPosition({ 0,0,0 });


	deadLine = 0;

	

	for (int i = 0; i < tileVal; i++)
	{
		tileFlag[i] = 0;
		preTileFlag[i] = 0;

	}
	int o = 0;
	for (std::unique_ptr<CubeObject3D>& tile : tiles)
	{
		if (o > 1)
		{
			tile->SetModel(cubeModel1.get());
		}
		o++;
	}
	gameState = 0;
}

