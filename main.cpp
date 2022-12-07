#include "main.h"
#include "FPS.h"
#include "DXInput.h"
#include "fbxSDK.h"
#include "list"
#include "memory"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ生成
	WinApp* win = nullptr;
	win = WinApp::GetInstance();
	win->CreateWindow_(L"DirectX");

	Masage* masage;	//メッセージ
	masage = Masage::GetInstance();

	//DirectX初期化処理
	DirectXCommon* dx = nullptr;
	dx = DirectXCommon::GetInstance();
	dx->Initialize(win);

	//キーボード
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(win);

	//ゲームシーン
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Initialize(dx, input);

	//FPSを固定
	FPS* fps = nullptr;
	fps = new FPS;
	fps->SetFrameRate(60.0f);
	fps->FpsControlBegin();;

	//FbxManager* fbx_manager = FbxManager::Create();
	//FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "ImportTest");
	//FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "SceneTest");
	//fbx_importer->Initialize("Box.fbx");
	//FbxNode* root_node = fbx_scene->GetRootNode();

	//for (int i = 0; i < root_node->GetNodeAttributeCount(); i++)
	//{
	//	FbxNodeAttribute* attribute = root_node->GetNodeAttributeByIndex(i);

	//	FbxNodeAttribute::EType type = attribute->GetAttributeType();

	//	printf("attribute type => %d\n", type);
	//}

	//for (int i = 0; i < root_node->GetChildCount(); i++)
	//{
	//	FbxNode* child = root_node->GetChild(i);
	//}

	//FbxGeometryConverter converter(fbx_manager);


	//// ポリゴンを三角形にする
	//converter.Triangulate(fbx_scene, true);

	//// メッシュNodeを探す
	//CollectMeshNode(fbx_scene->GetRootNode(), mesh_node_list);

	//void ObjFile::CollectMeshNode(FbxNode * node, std::map<std::string, FbxNode*>&list)
	//{
	//	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	//	{
	//		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);

	//		// Attributeがメッシュなら追加
	//		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
	//		{
	//			list[node->GetName()] = node;
	//			break;
	//		}
	//	}

	//	for (int i = 0; i < node->GetChildCount(); i++)
	//	{
	//		CollectMeshNode(node->GetChild(i), list);
	//	}
	//}


#pragma endregion

	//ゲームループ
	while (true)
	{
		//Xボタンで終了メッセ時が来たらゲームループを抜ける 
		if (masage->Update() == 1)break;

#pragma region DirectX毎フレーム処理

		//キーボード更新
		input->Update();

		gameScene->Update();

		dx->PreDraw();
		// 4. 描画コマンド
		gameScene->Draw();

		dx->PostDraw();

#pragma endregion
	}

	//FPS固定を解除
	dx->EndImgui();

	delete fps;
	delete gameScene;
	/*delete dx;*/

	masage->ExitGameloop();

	//ウィンドウクラスを登録解除
	win->deleteWindow();

	return 0;
}