//#include "Pera.h"
//
////ペラポリゴン生成
//
//void Pera::Initialize(ComPtr<ID3D12Device> device, DirectXCommon* dx) {
//
//	this->dx = dx;
//
//	HRESULT result;
//
//	// リソース設定
//	CD3DX12_HEAP_PROPERTIES peraHeapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//
//	CD3DX12_RESOURCE_DESC peraResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(pv));
//
//	result = device->CreateCommittedResource(
//		&peraHeapProps,
//		D3D12_HEAP_FLAG_NONE,
//		&peraResourceDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(_peraVB.ReleaseAndGetAddressOf()));
//
//	PeraVertex* mappedPera = nullptr;
//	_peraVB->Map(0, nullptr, (void**)&mappedPera);
//	std::copy(std::begin(pv), std::end(pv), mappedPera);
//	_peraVB->Unmap(0, nullptr);
//
//	// 頂点バッファビューの作成
//	_peraVBV.BufferLocation = _peraVB->GetGPUVirtualAddress();
//	_peraVBV.SizeInBytes = sizeof(pv);
//	_peraVBV.StrideInBytes = sizeof(PeraVertex);
//
//
//	// ヒーププロパティ
//	CD3DX12_HEAP_PROPERTIES heapPropsConstantBuffer = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	// リソース設定
//	CD3DX12_RESOURCE_DESC resourceDescConstantBuffer =
//		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);
//
//	// 定数バッファの生成
//	result = device->CreateCommittedResource(
//		&heapPropsConstantBuffer, // ヒープ設定
//		D3D12_HEAP_FLAG_NONE,
//		&resourceDescConstantBuffer, // リソース設定
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&constBuff));
//	assert(SUCCEEDED(result));
//
//	// 定数バッファにデータ転送
//	ConstBufferData* constMap = nullptr;
//	result = constBuff->Map(0, nullptr, (void**)&constMap); // マッピング
//	constMap->mode = mode;
//	constMap->time = time;
//	constBuff->Unmap(0, nullptr);
//
//	//ペラポリゴンパイプラインとルートシグネチャ
//
//	D3D12_INPUT_ELEMENT_DESC layout[2] = {
//		{
//			"POSITION",
//			0,
//			DXGI_FORMAT_R32G32B32_FLOAT,
//			0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
//			0
//		},
//		{
//			"TEXCOORD",
//			0,
//			DXGI_FORMAT_R32G32_FLOAT,
//			0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
//			0
//		},
//	};
//
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsDesc = {};
//	gpsDesc.InputLayout.NumElements = _countof(layout);
//	gpsDesc.InputLayout.pInputElementDescs = layout;
//
//
//	ComPtr<ID3DBlob> vs;
//	ComPtr<ID3DBlob> ps;
//	ComPtr<ID3DBlob> errBlob;	//エラーオブジェクト
//
//	result = D3DCompileFromFile(
//		L"peraVertex.hlsl",	//シェーダファイル名
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//インクルード可能にする
//		"main",		//エントリーポイント名
//		"vs_5_0",	//シェーダモデル指定
//		0,
//		0,
//		vs.ReleaseAndGetAddressOf(),
//		errBlob.ReleaseAndGetAddressOf()
//	);
//
//	//エラーなら
//	if (FAILED(result))
//	{
//		//errorBlobからエラーの内容をstring型にコピー
//		std::string error;
//		error.resize(errBlob->GetBufferSize());
//
//		std::copy_n(
//			(char*)errBlob->GetBufferPointer(),
//			errBlob->GetBufferSize(),
//			error.begin()
//		);
//		error += "\n";
//		//エラー内容を出力ウィンドウに表示
//		OutputDebugStringA(error.c_str());
//		assert(0);
//	}
//
//	result = D3DCompileFromFile(
//		L"peraPixel.hlsl",	//シェーダファイル名
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//インクルード可能にする
//		"main",		//エントリーポイント名
//		"ps_5_0",	//シェーダモデル指定
//		0,
//		0,
//		ps.ReleaseAndGetAddressOf(),
//		errBlob.ReleaseAndGetAddressOf()
//	);
//
//	//エラーなら
//	if (FAILED(result))
//	{
//		//errorBlobからエラーの内容をstring型にコピー
//		std::string error;
//		error.resize(errBlob->GetBufferSize());
//
//		std::copy_n(
//			(char*)errBlob->GetBufferPointer(),
//			errBlob->GetBufferSize(),
//			error.begin()
//		);
//		error += "\n";
//		//エラー内容を出力ウィンドウに表示
//		OutputDebugStringA(error.c_str());
//		assert(0);
//	}
//
//	gpsDesc.VS = CD3DX12_SHADER_BYTECODE(vs.Get());
//	gpsDesc.PS = CD3DX12_SHADER_BYTECODE(ps.Get());
//
//	gpsDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//	gpsDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//	gpsDesc.NumRenderTargets = 1;
//	gpsDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//	gpsDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//	gpsDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
//	gpsDesc.SampleDesc.Count = 1;
//	gpsDesc.SampleDesc.Quality = 0;
//	gpsDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
//
//	{
//		//D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
//		//rsDesc.NumParameters = 0;
//		//rsDesc.NumStaticSamplers = 0;
//		//rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//
//		//D3D12_DESCRIPTOR_RANGE range = {};
//
//		//range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//		//range.BaseShaderRegister = 0;
//		//range.NumDescriptors = 1;
//
//		//D3D12_ROOT_PARAMETER rp = {};
//		//rp.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
//		//rp.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//		//rp.DescriptorTable.pDescriptorRanges = &range;
//		//rp.DescriptorTable.NumDescriptorRanges = 1;
//
//		//D3D12_STATIC_SAMPLER_DESC sampler = CD3DX12_STATIC_SAMPLER_DESC(0);
//
//		//rsDesc.NumParameters = 1;
//		//rsDesc.pParameters = &rp;
//		//rsDesc.NumStaticSamplers = 1;
//		//rsDesc.pStaticSamplers = &sampler;
//
//		CD3DX12_DESCRIPTOR_RANGE descriptorRange{};
//		descriptorRange.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
//
//		CD3DX12_ROOT_PARAMETER rootParams[2];
//		rootParams[0].InitAsConstantBufferView(0);
//		rootParams[1].InitAsDescriptorTable(1, &descriptorRange, D3D12_SHADER_VISIBILITY_ALL);
//
//		// テクスチャサンプラーの設定
//		D3D12_STATIC_SAMPLER_DESC samplerDesc{};
//		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //横繰り返し（タイリング）
//		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //縦繰り返し（タイリング）
//		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //奥行繰り返し（タイリング）
//		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;  //ボーダーの時は黒
//		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;                   //全てリニア補間
//		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;                                 //ミップマップ最大値
//		samplerDesc.MinLOD = 0.0f;                                              //ミップマップ最小値
//		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
//		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;           //ピクセルシェーダからのみ使用可能
//
//		// ルートシグネチャの設定
//		D3D12_ROOT_SIGNATURE_DESC rsDesc{};
//		rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//		rsDesc.pParameters = rootParams; //ルートパラメータの先頭アドレス
//		rsDesc.NumParameters = _countof(rootParams);        //ルートパラメータ数
//
//		rsDesc.pStaticSamplers = &samplerDesc;
//		rsDesc.NumStaticSamplers = 1;
//
//
//		ComPtr<ID3DBlob> rsBlob;
//		auto result = D3D12SerializeRootSignature(
//			&rsDesc,
//			D3D_ROOT_SIGNATURE_VERSION_1,
//			rsBlob.ReleaseAndGetAddressOf(),
//			errBlob.ReleaseAndGetAddressOf()
//		);
//
//		result = device->CreateRootSignature(
//			0,
//			rsBlob->GetBufferPointer(),
//			rsBlob->GetBufferSize(),
//			IID_PPV_ARGS(_peraRS.ReleaseAndGetAddressOf())
//		);
//
//		gpsDesc.pRootSignature = _peraRS.Get();
//		result = device->CreateGraphicsPipelineState(
//			&gpsDesc,
//			IID_PPV_ARGS(_peraPipeline.ReleaseAndGetAddressOf())
//		);
//	}
//
//}
//
//void Pera::Update()
//{
//	if (mode == 0) {
//		time = 0;
//	}
//	if (mode == 1) {
//		time += 0.001;
//
//		if (time >= 1) {
//			mode = 0;
//		}
//
//	}
//
//	// 定数バッファにデータ転送
//	ConstBufferData* constMap = nullptr;
//	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap); // マッピング
//	constMap->mode = mode;
//	constMap->time = time;
//	constBuff->Unmap(0, nullptr);
//
//}
//
//void Pera::Draw() {
//
//	this->commandList = dx->GetCommandList();
//
//
//	commandList->SetGraphicsRootSignature(_peraRS.Get());
//	commandList->SetPipelineState(_peraPipeline.Get());
//
//	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	commandList->IASetVertexBuffers(0, 1, &_peraVBV);
//
//	// 定数バッファ(CBV)の設定コマンド
//	commandList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
//
//
//	this->_peraSRVHeap = dx->GetPeraSRVHeap();
//
//	commandList->SetDescriptorHeaps(1, _peraSRVHeap.GetAddressOf());
//
//	auto handle = _peraSRVHeap->GetGPUDescriptorHandleForHeapStart();
//
//	commandList->SetGraphicsRootDescriptorTable(1, handle);
//
//	// 描画コマンド
//	commandList->DrawInstanced(4, 1, 0, 0);
//
//}
//
