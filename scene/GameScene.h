#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "object3D.h"
#include "list"
#include "memory"
#include "Texture.h"
#include "Model.h"
#include "Object3D.h"
#include "Sound.h"
#include "Camera.h"
#include "DXInput.h"
#include "Sprite.h"
#include "FbxObject3D.h"
#include "FbxModel.h"
#include "SphereObject3D.h"
#include "SphereModel.h"
#include "SphereSprite.h"

class GameScene
{
	//�����o�֐�
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Initialize();
	void Update();
	void Draw();

	//�����o�ϐ�
private: 
	//�f�o�C�X��input
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//�R���g���[��
	DXInput* dxInput = new DXInput();
	//�J����
	std::unique_ptr<Camera> camera_;

	//fbx
	FbxModel* model1 = nullptr;
	FbxObject3D* object1 = nullptr;

	size_t texImgCount_ = 1;	//�e�N�X�`���̐�
	std::vector<SphereSprite> texImg_;	//�e�N�X�`��

	//���̂̃��f��
	XMFLOAT3 size1 = { 5.0f,5.0f,5.0f };
	std::unique_ptr<SphereModel> sphere_;

	//3D�I�u�W�F�N�g
	size_t kObjectCount = 2;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> object3ds_;	//�I�u�W�F�N�g
};
