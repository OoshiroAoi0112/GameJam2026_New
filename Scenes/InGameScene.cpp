#include "InGameScene.h"
#include "../StageData.h"
#include "../Utility/InputControl.h"
#include "../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include "../Objects/Item/Item.h"
#include "../Objects/Block/Block.h"
#include "../Utility/GameDataManager.h"
#include "../Utility/DrawNumber.h"
#include "DxLib.h"

#include <string>

bool goal_flag;
bool delay_flag;
bool image_flag;
bool item_spawned;
int speed;
int score_animation[10];
int IngameBgmHandle;

InGameScene::InGameScene()
	: player(nullptr)
	, enemy(nullptr)
	, item(nullptr)
	, background_image(0)
	, next_scene(eSceneType::eInGame)
{
	/*score = LoadGraph
	score_animation = LoadDivGraph("Resource/image/suuji.png", 3, 3, 1, 200, 200, score_animation);*/

	IngameBgmHandle = LoadSoundMem("Resource/sounds/InGame/InGameBGM.mp3");
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	StageData* stage = StageData::GetInstance();
	stage->Load();
	goal_flag = false;
	delay_flag = false;
	image_flag = true;
	item_spawned = false;

	DrawNumber::SetImage(
		ResourceManager::GetInstance()->GetImages("Resource/image/Result/number.png")
	);

	background_image = LoadGraph("Resource/image/sky.png");
	santa_image = LoadGraph("Resource/image/santa_start.png");
	present_image = LoadGraph("Resource/image/present.png");

	stage_data.Load();

	player = CreateObject<Player>(Vector2D(100, 550));

	//エネミーの生成
	for (const Vector2D& pos : stage_data.GetEnemySpawnPositions())
	{
		CreateObject<Enemy>(pos);
	}

	//ブロック（足場）の生成
	for (const BlockSpawnData& data : stage_data.GetBlockSpawnPositions())
	{
		// ブロックの位置とタイプを読み取る
		Block* block = CreateObject<Block>(data.pos);
		block->SetBlockType(data.type);
	}

	screen_offset = Vector2D(0, 0);
}

eSceneType InGameScene::Update(const float& delta_second)
{
	IngameBgm();
	StageData* Stage = StageData::GetInstance();
	Stage->Update(delta_second);

	// 入力情報を取得
	InputControl* pad_input = InputControl::GetInstance();
	
	delay++;
	if (delay >= 1100) {
		delay_flag = true;
	}
	else if (delay >= 980)
	{
		speed = 520;
	}
	else if (delay > 500){
		speed++;
	}
	if (delay_flag == true) {
		delay = 1200;
		//speed = 520;
		image_flag = false;
	}

	 //少し遅らせてアイテムを生成する
	if (delay_flag == true && item_spawned == false)
	{
		for (const Vector2D& pos : stage_data.GetItemSpawnPositions())
		{
			CreateObject<Item>(pos);
		}

		item_spawned = true; // 二重生成防止
	}

	// 画面中央にプレイヤーを置く
	screen_offset.x = 1280.0f / 2.0f - player->GetLocation().x;

	// 左端制限（ステージ開始）
	if (screen_offset.x > 0.0f)
	{
		screen_offset.x = 0.0f;
	}

	// 右端制限（ステージ終端）
	const float STAGE_WIDTH = 181.0f * 32.0f; // csv 横サイズ
	const float SCREEN_WIDTH = 1280.0f;

	float min_offset = SCREEN_WIDTH - STAGE_WIDTH;

	if (screen_offset.x < min_offset)
	{
		screen_offset.x = min_offset;

		goal_flag = true;

		auto& mg = GameDataManager::GetInstance();
		int score = mg.GetScore();

		GameDataManager::GetInstance().SetScore(score);  //スコア値の取得
		return eSceneType::eResult;
	}

	//Draw();

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);;
}

//描画処理
void InGameScene::Draw() const
{
	DrawGraph(0,0,background_image,true);
	__super::Draw();

	// スコアの描画
	auto& mg = GameDataManager::GetInstance();
	int score = mg.GetScore();
	DrawNumber::Draw(200, 0, score, 0.5f);

	StageData* stage = StageData::GetInstance();
	stage->Draw(screen_offset);
	float s_location = stage->GetLocation();

	if (image_flag == true)
	{
		// プレゼントの描画
		if (delay >= 530)DrawRotaGraph(640, 80 + speed, 1.0, 0.0, present_image, TRUE);
		DrawRotaGraph(200 + delay, 100, 1.0, 0.0, santa_image, TRUE);
	}

	__super::Draw();
}

void InGameScene::Finalize()
{
	StopSoundMem(IngameBgmHandle);

	//動的配列が空なら処理を終了する
	if (object_list.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : object_list)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	object_list.clear();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

//カメラ視点の値を取得する
const Vector2D& InGameScene::GetScreenOffset() const
{
	return screen_offset;
}

void InGameScene::IngameBgm()
{
	if (CheckSoundMem(IngameBgmHandle) == 0)
	{
		PlaySoundMem(IngameBgmHandle, DX_PLAYTYPE_LOOP);
		CheckSoundMem(IngameBgmHandle);
	}
}