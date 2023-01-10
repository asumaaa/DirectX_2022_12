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

	//�J����������
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_);
	camera_.reset(newCamera);
	camera_->SetTarget({ 0,0,0 });
	camera_->SetEye({ 0, 0, -100 });

	//���^�{�[��
	//�f�o�C�X���Z�b�g
	Metaball::SetDevice(dxCommon_->GetDevice());
	Metaball::SetCamera(camera_.get());
	Metaball::CreateGraphicsPipeline();

	Metaball* newMetaball = new Metaball();
	newMetaball->Initialize();
	newMetaball->SetImageData({ 1.0, 1.0, 1.0, 1 });
	newMetaball->SetPosition({ 0,20,0 });
	newMetaball->SetScale({ 3,3,3 });
	metaball.reset(newMetaball);

	//�L���[�u�̐ݒ�
	//�f�o�C�X���Z�b�g
	CubeObject3D::SetDevice(dxCommon_->GetDevice());
	CubeObject3D::SetCamera(camera_.get());
	CubeObject3D::SetInput(input_);
	CubeObject3D::CreateGraphicsPipeline();

	CubeModel* newCubeModel = new CubeModel();
	newCubeModel->CreateBuffers(dxCommon_->GetDevice());
	cubeModel1.reset(newCubeModel);
	cubeModel1->SetImageData({ 0.0f, 0.3f, 0.3f,1.0f });

	CubeObject3D* newCubeObject = new CubeObject3D();
	newCubeObject->Initialize();
	cubeObject1.reset(newCubeObject);
	cubeObject1->SetModel(cubeModel1.get());

	cubeObject1->SetScale({ 30.0f,1.0f,30.0f });
	cubeObject1->SetPosition({ 0.0f,0.0f,0.0f });

	//�����蔻��̐ݒ�
	Collision* newCollision = new Collision();
	newCollision->SetObject(cubeObject1.get(), metaball.get());
	collision.reset(newCollision);
}

void GameScene::Update()
{
	
	metaball->Move();
	/*metaball->UpdateCollision(collision.get());*/
	metaball->Update();

	cubeObject1->Move();
	cubeObject1->Update();

	camera_->Update();


	//�R���g���[���[�X�V
	dxInput->InputProcess();
}

void GameScene::Draw()
{
	metaball->Draw(dxCommon_->GetCommandList());
	cubeObject1->Draw(dxCommon_->GetCommandList());
}
