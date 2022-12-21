//#pragma once
//#pragma once
//
//#include "SphereModel.h"
//#include "Camera.h"
//
//#include "windows.h"
//#include "wrl.h"
//#include "d3d12.h"
//#include "d3dx12.h"
//#include "DirectXMath.h"
//
//using namespace DirectX;
//using namespace Microsoft::WRL;
//
////�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
//struct ConstBufferDataMaterial {
//	XMFLOAT4 color;	//�F(RGBA)
//};
//
////�萔�o�b�t�@�p�f�[�^�\���́i3D�ϊ��s��j
//struct ConstBufferDataTransform
//{
//	XMMATRIX mat;
//};
//
////3D�I�u�W�F�N�g�^
//struct Object3d
//{
//	//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffTransform;
//	//�萔�o�b�t�@�}�b�v
//	ConstBufferDataTransform* constMapTransform;
//	//�A�t�B���ϊ����
//	XMFLOAT3 scale = { 1,1,1 };
//	XMFLOAT3 rotation = { 0,0,0 };
//	XMFLOAT3 position = { 0,0,0 };
//	//���[���h�ϊ��s��
//	XMMATRIX matWorld;
//	//�e�I�u�W�F�N�g�̃|�C���^�[
//	Object3d* parent = nullptr;
//};
//
////3�I�u�W�F�N�g�֘A
////3D�I�u�W�F�N�g������
//void InitializeObject3d(Object3d* object, ComPtr<ID3D12Device> device);
////3D�I�u�W�F�N�g�X�V
//void UpdateObject3d(Object3d* object, XMMATRIX& matView, XMMATRIX& matProjection);
////�I�u�W�F�N�g�`�揈��
//void DrawObject3d(Object3d* object, ComPtr<ID3D12GraphicsCommandList> commandList, D3D12_VERTEX_BUFFER_VIEW& vbView,
//	D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices);