#include "ResultScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/GameDataManager.h"
#include "../Utility/DrawNumber.h"

#include <string>

int Result_image;
int Result_score;
//int score = 1500;
int ResultBgmHandle;
int ResultBgmHandle1;
bool flag;
float time;
bool isBgmPlayed = false;
int i=0;
int santa1_image;
int santa2_image;
int santa3_image;
ResultScene::ResultScene() : score_animation(), image()
{
	next_scene = eSceneType::eResult;
	ResourceManager* rm = ResourceManager::GetInstance();
	// 画像の読み込み
	Result_image = LoadGraph("Resource/image/Result/result.png");
	rendeer_image = LoadGraph("Resource/image/Result/rendeer.png");
	santa1_image = LoadGraph("Resource/image/Result/santa1.png");
	santa2_image = LoadGraph("Resource/image/Result/santa2.png");
	santa3_image = LoadGraph("Resource/image/Result/santa3.png");
	Arank_animation = rm->GetImages("Resource/image/Result/player_a_anim.png", 2, 2, 1, 250, 411);  // Aランク用アニメーション
	Brank_animation = rm->GetImages("Resource/image/Result/player_b_anim.png", 2, 2, 1, 250, 397);  // Bランク用アニメーション
	Crank_animation = rm->GetImages("Resource/image/Result/player_c_anim.png", 2, 2, 1, 250, 406);  // Cランク用アニメーション
	score_animation = rm->GetImages("Resource/image/Result/Score.png", 3, 3, 1, 200, 200);

	Result_score = score_animation[0];



	// BGMの読み込み
	ResultBgmHandle = LoadSoundMem("Resource/sounds/Result/resultBGM1.mp3");

	ResultBgmHandle1 = LoadSoundMem("Resource/sounds/Result/drum roll.mp3");
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	printf("リザルト画面");
	flag = FALSE;
	time = 0.0;

	// インゲームからスコアを取得
	score = GameDataManager::GetInstance().GetScore();

	DrawNumber::SetImage(
		ResourceManager::GetInstance()->GetImages("Resource/image/Result/number.png")
	);
}

eSceneType ResultScene::Update(const float& delta_second)
{
	time += delta_second;
	ResultBgm();

	// 入力情報を取得
	InputControl* pad_input = InputControl::GetInstance();

	// エンドシーンに遷移する
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		return eSceneType::eTitle;
	}

	else if (time > 3.0)
	{
		flag = TRUE;
		// アニメーション制御
		AnimeCount(delta_second);
	}

	else
	{
		
	}

	return eSceneType::eResult;
}

// 描画処理
void ResultScene::Draw() const
{
	DrawGraph(0, 0, Result_image, TRUE);
	

	// プレイヤー描画
	DrawRotaGraph(640, 570, 0.8, 0, image, TRUE, 0);

	//スコアの評価の判定
	if (flag == TRUE)
	{
		DrawRotaGraph(300, 590, 1.1, 0, rendeer_image, TRUE, 0);  // トナカイの描画
		DrawRotaGraph(330, 590, 1.1, 0, rendeer_image, TRUE, 1);  // トナカイの描画
		if (score > 3000)
		{
			Result_score = score_animation[0];
			DrawGraph(760, 220, Result_score, TRUE);
			DrawRotaGraph(315, 590, 0.1, 0, santa1_image, TRUE, 0);
		}
		else if (score > 1000)
		{
			Result_score = score_animation[1];
			DrawGraph(760, 220, Result_score, TRUE);
			DrawRotaGraph(315, 590, 0.1, 0, santa2_image, TRUE, 0);
		}
		else
		{
			Result_score = score_animation[2];
			DrawGraph(760, 220, Result_score, TRUE);
			DrawRotaGraph(315, 590, 0.1, 0, santa3_image, TRUE, 0);
		}
		
		
	}
	else
	{
		Result_score = score_animation[(int)(rand() * (3 - 1 + 1.0) / (1.0 + RAND_MAX))];
		DrawGraph(760, 220, Result_score, TRUE);
	}
	// スコアの描画
	DrawNumber::Draw(680, 280, score, 1.0f);
}

void ResultScene::Finalize()
{
	// リザルトのBGMを停止する処理
	StopSoundMem(ResultBgmHandle);
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

void ResultScene::AnimeCount(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= 0.5f)
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// Aランク
		if (score > 3000)
		{
			// 画像の設定
			image = Arank_animation[rank_animation[animation_count]];
		}
		// Bランク
		else if (score > 1000)
		{
			// 画像の設定
			image = Brank_animation[rank_animation[animation_count]];
		}
		// Cランク
		else
		{
			// 画像の設定
			image = Crank_animation[rank_animation[animation_count]];
		}
	}
}

void ResultScene::ResultBgm()
{
	// リザルトのBGMを再生する処理
	if (CheckSoundMem(ResultBgmHandle) == 0)
	{
		PlaySoundMem(ResultBgmHandle, DX_PLAYTYPE_LOOP, TRUE);
		ChangeVolumeSoundMem(250, ResultBgmHandle);  // 音量調整
		CheckSoundMem(ResultBgmHandle); 
	}

	// ドラムロールのBGMが一回流れたら停止する処理
	if (isBgmPlayed == false)
	{
		PlaySoundMem(ResultBgmHandle1, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(250, ResultBgmHandle1);  // 音量調整
		isBgmPlayed = true;
	}
}
