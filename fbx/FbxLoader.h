#pragma once

#include "fbxsdk.h"
#include "FbxModel.h"
#include "string"

#include <d3d12.h>
#include <d3dx12.h>

class FbxLoader
{
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

public:
	//初期化	
	void Initialize(ID3D12Device* device);
	//後始末
	void Finalize();

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

private:
	//デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポーター
	FbxImporter* fbxImporter = nullptr;

private:
	using string = std::string;	//stdを省略

	//定数
public:
	//モデル格納ルートパス
	static const string baseDirectory;
	//FBXファイルの読み込み
	void LoadModelFromFile(const string modelName);
	//ノード構成を解析
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent = nullptr);
};