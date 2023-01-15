#pragma once
#include "vector"
#include "DirectXMath.h"
#include "DirectXCommon.h"
#include "DirectXTex.h"
#include "windows.h"
#include "wrl.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "Camera.h"
#include "Collision.h"
#include "input.h"

const int fine = 16;	//���ׂ̂̍���	�ϐ��錾�p
const int fine2 = fine * fine * 2;	//�`��Ɏg�����_�̐�
const int fine3 = fine * fine * 3;	//�C���f�b�N�X�̐�
const int fine4 = fine * fine + fine;	//���_�̐�

class Metaball
{
private:	//�G�C���A�X
//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
	using TexMetadata = DirectX::TexMetadata;
	using ScracthImage = DirectX::ScratchImage;
	//std::���ȗ�
	using string = std::string;
	template<class T>using vector = std::vector<T>;

public://�T�u�N���X
//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
public:	//�ÓI�����o�֐�
//�Z�b�^�[
	static void SetDevice(ID3D12Device* device) { Metaball::device = device; }
	static void SetCamera(Camera* camera) { Metaball::camera = camera; }
	static void SetInput(Input* input) { Metaball::input = input; }
	//�O���t�B�b�N�X�p�C�v���C���̐���
	static void CreateGraphicsPipeline();

private://�ÓI�����o�ϐ�
	static ID3D12Device* device;
	static Camera* camera;
	static Input* input;

public:
	//������
	void Initialize();
	//�X�V
	void Update();
	//�o�b�t�@����
	void CreateBuffers();
	//���_����
	void CreateVertex();
	//�F�ݒ�
	void SetImageData(XMFLOAT4 color);
	//�����蔻��
	void UpdateCollision(Collision* collision);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);

	//���f����ό`������Ƃ��Ă�
	void UpdateVertex();
	//���_������(���̂ɖ߂�)
	void InitializeVertex();
	//��̓_�ɑ΂��ă��f���ό`
	void UpdateGravity(XMFLOAT3 gravityPoint);

	//�ړ�
	void Move();

	//�Z�b�^�[
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetScale(XMFLOAT3 sca) { scale.x = sca.x/2; scale.y = sca.y / 2;scale.z = sca.z / 2;}
	void SetRotation(XMFLOAT3 rot) { rotation = rot; }

	//�Q�b�^�[
	XMFLOAT3 GetPosition() { return position; }
	XMFLOAT3 GetRotation() { return rotation; }
	XMFLOAT3 GetScale() { return scale; }

public:
	//���_�f�[�^�z��
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos;	//���W
		XMFLOAT3 normal;	//�@���x�N�g��
		XMFLOAT3 uv;	//uv���W
		VertexPosNormalUv* parent = nullptr;	//uv���W
	};
	//���_�f�[�^�z��
	vector<VertexPosNormalUv>vertices;
	vector<VertexPosNormalUv>vertices2;
	//���_�C���f�b�N�X�z��
	vector<unsigned short>indices;
private:
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource>indexBuff;
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource>texBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//�A���r�G���g�W��
	XMFLOAT3 ambient = { 1,1,1 };
	//�f�B�t���[�Y�W��
	XMFLOAT3 diffuse = { 1,1,1 };
	//�e�N�X�`�����^�f�[�^
	TexMetadata metadata = {};
	//�X�N���b�`�C���[�W
	ScracthImage scratchImg = {};
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource>constBuffTransform;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature>rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState>pipelinestate;
	//�摜�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	const size_t textureWidth = 256;
	const size_t textureHeight = 256;
	const size_t imageDataCount = textureWidth * textureHeight;
	XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];
	//�e�N�X�`���[��GPU�̃n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
private:
	//���_�����p�ϐ�
	vector<VertexPosNormalUv> v;
	vector<VertexPosNormalUv> v2;
	vector<VertexPosNormalUv> v3;
	const float fineSize = fine;	//���ׂ̂̍���
	float angleX, angleY;
	float oneAngle = (2 * 3.14159265359) / fineSize;

	//�ό`�s��
	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z�����̃��[�J���s��
	XMFLOAT3 rotation = { 0,0,0 };
	//���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	//���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	/*MetaballModel* model = nullptr;*/

	//�ړ��p�ϐ�
	XMFLOAT3 fallVelocity = { 0,0,0 };
	float fallTimer = 0.0f;

	bool groundFlag = false;
};
