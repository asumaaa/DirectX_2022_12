#include "Player.h"

#define PI 3.14159265359
#define G 6.674	//���L���͒萔
#define GAcceleration 9.80665 * 1/20	//�d�͉����x

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
    //�X�y�[�X�L�[�ŃW�����v
    if (input->PushKey(DIK_SPACE) && groundFlag == true)
    {
        //�ڒn�t���O��false��
        fallTimer = -1;
        groundFlag = false;
    }

    //�n�ʂɐڂ��Ă��Ȃ��ꍇ�̗�������
    if (groundFlag == false)
    {
        //60�t���[���Ń^�C�}�[��1�i�߂�
        fallTimer += 2.5f / 60.0f;
        //�����x�N�g���v�Z
        float v = GAcceleration * fallTimer;
        fallVelocity.y = -(GAcceleration * fallTimer);
        //���W�ɉ��Z
        position.x += fallVelocity.x;
        position.y += fallVelocity.y;
        position.z += fallVelocity.z;
    }
}

void Player::UpdateCollision(Collision* collision)
{
    if (collision->Update(position, scale) == 1)
    {
        //�ڒn�t���O�𗧂Ă�
        groundFlag = true;
        //���R����T�̒l�����Z�b�g
        fallTimer = 0;
        //�����x�N�g�������Z�b�g
        fallVelocity.y = 0;
    }

    //�߂荞�܂Ȃ��Ȃ�܂ŉ��Z
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
