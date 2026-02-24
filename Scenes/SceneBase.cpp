//#include "SceneBase.h"
//
//#include "DxLib.h"
//
//SceneBase::SceneBase() : background_image(NULL)
//{
//
//}
//
//SceneBase::~SceneBase()
//{
//	// 終了処理
//	this->Finalize();
//}
//
//void SceneBase::Initialize()
//{
//
//}
//
//eSceneType SceneBase::Update()
//{
//
//	// 範囲for文でobjectsの要素を順番にobjに代入
//	for (GameObject* obj : objects)
//	{
//		// オブジェクトの更新処理
//		obj->Update();
//	}
//
//	for (int i = 0; i < objects.size(); i++)
//	{
//		if (objects[i]->GetDeleteFlag())
//		{
//			// 終了処理
//			objects[i]->Finalize();
//			// 削除
//			objects.erase(objects.begin() + i);
//		}
//	}
//
//	// 現在のシーンを返す
//	return GetNowSceneType();
//}
//
//void SceneBase::Draw() const
//{
//
//	// 範囲for文でobjectsの要素を順番にobjに代入
//	for (GameObject* obj : objects)
//	{
//		// オブジェクトの描画処理
//		obj->Draw(screen_offset);
//	}
//
//}
//
//void SceneBase::Finalize()
//{
//	// objectsの要素が空だったら
//	if (objects.empty())
//	{
//		return;
//	}
//
//	// 範囲for文でobjectsの要素を順番にobjに代入
//	for (GameObject* obj : objects)
//	{
//		// オブジェクトの終了処理
//		obj->Finalize();
//		delete obj;
//	}
//
//	// objectsの要素をすべて削除
//	objects.clear();
//}
//
//void SceneBase::DestroyObject(GameObject* target)
//{
//	// ヌルポチェック
//	if (target == nullptr)
//	{
//		return;
//	}
//
//	// 破棄オブジェクトリスト内にあれば、追加しない
//	for (GameObject* obj : delete_list)
//	{
//		if (obj == target)
//		{
//			return;
//		}
//	}
//
//	// 破棄を行うオブジェクトリストに追加する
//	delete_list.push_back(target);
//}
