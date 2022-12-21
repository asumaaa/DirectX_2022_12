//#pragma once
//#include "DirectXCommon.h"
//#include "DirectXMath.h"
//#include "DirectXTex.h"
//
//using namespace DirectX;
//using namespace Microsoft::WRL;
//
//class SphereSprite
//{
//	public:
//		static SphereSprite* GetInstance();
//		void Initialize(const wchar_t* szFile, DirectXCommon* dx, int texNum);
//		void Initialize(DirectXCommon* dx, int texNum);
//		void Draw();
//		void SetImageData(XMFLOAT4 color);
//
//		//ゲッター
//		ID3D12Resource* GetTexBuff() { return texBuff.Get(); }
//		ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }
//	private:
//		//画像
//		TexMetadata metadata;
//		ScratchImage scratchImg;
//		//ミップマップ
//		ScratchImage mipChain;
//		//テクスチャバッファ
//		ComPtr<ID3D12Resource> texBuff;
//		//テクスチャーのGPUのハンドル
//		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
//		//画像用デスクリプタヒープ
//		ComPtr<ID3D12DescriptorHeap> srvHeap;
//		const size_t textureWidth = 256;
//		const size_t textureHeight = 256;
//		const size_t imageDataCount = textureWidth * textureHeight;
//		XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];
//	public:
//		DirectXCommon* dx_;
//};

