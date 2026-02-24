#include "InGameScene.h"
#include "../StageData.h"
#include "../Utility/InputControl.h"
#include "../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include "../Objects/Item/Item.h"
#include "../Objects/Block/Block.h"
#include "../Utility/GameDataManager.h"
#include "DxLib.h"

#include <string>

bool goal_flag;
bool delay_flag;
bool image_flag;
bool item_spawned;
int speed;
int score;
int score_animation[10];

InGameScene::InGameScene()
	: player(nullptr)
	, enemy(nullptr)
	, item(nullptr)
	, background_image(0)
	, next_scene(eSceneType::eInGame)
{
	/*score = LoadGraph
	score_animation = LoadDivGraph("Resource/image/suuji.png", 3, 3, 1, 200, 200, score_animation);*/
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

	background_image = LoadGraph("Resource/image/sky.png");
	santa_image = LoadGraph("Resource/image/santa_start.png");
	present_image = LoadGraph("Resource/image/present.png");

	player = CreateObject<Player>(Vector2D(100, 100));
	score = 3500;
	stage_data.Load();

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

	// 少し遅らせてアイテムを生成する
	if (delay_flag == true && item_spawned == false)
	{
		for (const Vector2D& pos : stage_data.GetItemSpawnPositions())
		{
			CreateObject<Item>(pos);
		}

		item_spawned = true; // 二重生成防止
	}

	player->SetScroll(screen_offset.x);
	__super::Update(delta_second);

	float velocity = player->GetVelocity().x * delta_second;

	// スクロール条件
	if (player->GetLocation().x >= 1280 / 2 ||
		player->GetLocation().x <= 30)
	{
		// プレイヤーの加速度分スクロールする
		screen_offset.x -= velocity;
	}
	else
	{
		// スクロールできなくさせる
		velocity = 0;
	}

	// 左端制限
	if (screen_offset.x > 0)
	{
		screen_offset.x = 0;
		velocity = 0;
	}

	// 右端制限
	if (screen_offset.x < -4540)
	{
		screen_offset.x = -4540;
		velocity = 0;
	}

	// 最後に一度だけ設定
	Stage->SetVelocity(velocity);

	//// リザルト画面に遷移する
	if (screen_offset.x <= -4540 && player->GetLocation().x >850)
	{
		goal_flag = true;

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
	

	StageData* stage = StageData::GetInstance();
	stage->Draw(screen_offset);
	float s_location = stage->GetLocation();

	if (image_flag == true)
	{
		// プレゼントの描画
		if (delay >= 530)DrawRotaGraph(640, 80 + speed, 1.0, 0.0, present_image, TRUE);
		DrawRotaGraph(200 + delay, 100, 1.0, 0.0, santa_image, TRUE);
	}
	
	//デバッグ用
	//DrawFormatString(10, 50, GetColor(255, 255, 255),
	//	"offset.x = %.2f", screen_offset.x);

	//DrawFormatString(0, 0, GetColor(255, 255, 255),
	//	"PlayerLocationX: %.2f", player->GetLocation().x);

	//DrawFormatString(0, 20, GetColor(255, 255, 255),
	//	"PlayerVelocityX: %.2f", player->GetVelocity().x);

	//DrawFormatString(0, 40, GetColor(255, 255, 255),
	//	"PlayerLocationY: %.2f", player->GetLocation().y);
	auto& mg = GameDataManager::GetInstance();
	int score = mg.GetScore();
	DrawFormatString(1100, 440, GetColor(255, 255, 255),
		"score: %d", score);

	__super::Draw();
}

void InGameScene::Finalize()
{

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