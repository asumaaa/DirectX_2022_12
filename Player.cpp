#include "Player.h"

#define PI 3.14159265359
#define G 6.674	//万有引力定数
#define GAcceleration 9.80665 * 1/20	//重力加速度

Player* Player::GetInstance()
{
    static Player instance;
    return &instance;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(ID3D12Device* device, CubeModel* model, Input* input,DXInput* dxInput)
{
    this->device = device;
    this->model = model;
    this->input = input;
    this->dxInput = dxInput;

    CubeObject3D* newCubeObject = new CubeObject3D();
    newCubeObject->Initialize();
    object3d.reset(newCubeObject);
    object3d->SetModel(this->model);
}

void Player::Update()
{
    Move();

    object3d->SetScale(scale);
    object3d->SetRotation(rotation);
    object3d->SetPosition(position);
    object3d->Update();
}

void Player::Move()
{
    //スペースキーでジャンプ
    if (input->PushKey(DIK_SPACE) && groundFlag == true)
    {
        //接地フラグをfalseに
        fallTimer = -1;
        groundFlag = false;
    }

    //地面に接していない場合の落下処理
    if (groundFlag == false)
    {
        //60フレームでタイマーを1進める
        fallTimer += 2.5f / 60.0f;
        //落下ベクトル計算
        float v = GAcceleration * fallTimer;
        fallVelocity.y = -(GAcceleration * fallTimer);
        //座標に加算
        position.x += fallVelocity.x;
        position.y += fallVelocity.y;
        position.z += fallVelocity.z;
    }
}

void Player::UpdateCollision(Collision* collision)
{
    if (collision->Update(position, scale) == 1)
    {
        //接地フラグを立てる
        groundFlag = true;
        //自由落下Tの値をリセット
        fallTimer = 0;
        //落下ベクトルをリセット
        fallVelocity.y = 0;
    }

    //めり込まなくなりまで加算
    while (collision->Update(position, scale) == 1)
    {
        position.y += 0.02f;
        if (collision->Update(position, scale) == 0)
        {
            break;
        }
    }

    /*position.y -= 0.2f;
    if (collision->Update(position, scale) == 0)
    {
        groundFlag = false;
    }
    position.y += 0.1f;*/
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
    object3d->Draw(cmdList);
}

void Player::SetPosition(XMFLOAT3 pos)
{
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
}

void Player::SetRotation(XMFLOAT3 rot)
{
    rotation.x = rot.x;
    rotation.y = rot.y;
    rotation.z = rot.z;
}

void Player::SetScale(XMFLOAT3 sca)
{
    scale.x = sca.x;
    scale.y = sca.y;
    scale.z = sca.z;
}
