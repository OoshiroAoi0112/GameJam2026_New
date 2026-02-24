#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#include <string>

int cursor_number = 0;
int title_image;
int start_image;
int shuryo_image;
int help_image;
int cursor_image;
int start1_image;
int shuryo1_image;
int help1_image;
int TitleBgmHandle;
int CursorBgmHandle;

TitleScene::TitleScene()
{
	next_scene = eSceneType::eTitle;
	on_button = false;
	wait_time = 0.0f;
	// 画像の読み込み
	title_image = LoadGraph("Resource/image/Title/title.png");
	start_image = LoadGraph("Resource/image/Title/startmae.png");
	shuryo_image = LoadGraph("Resource/image/Title/shuryoumae.png");
	help_image = LoadGraph("Resource/image/Title/helpmae.png");

	cursor_image = LoadGraph("Resource/image/Title/yajirusi.png");

	start1_image = LoadGraph("Resource/image/Title/startgo.png");
	shuryo1_image = LoadGraph("Resource/image/Title/shuryougo.png");
	help1_image = LoadGraph("Resource/image/Title/helpato.png");

	// BGMの読み込み
	TitleBgmHandle = LoadSoundMem("Resource/sounds/Title/titleBGM.mp3");
	// カーソル音の読み込み
	CursorBgmHandle = LoadSoundMem("Resource/sounds/cursor.mp3");
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	printf("タイトルシーンです");
	on_button = false;
}

eSceneType TitleScene::Update(const float& delta_second)
{
	TitleBgm();
	// 入力情報を取得
	InputControl* pad_input = InputControl::GetInstance();

	// カーソルの移動
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		cursor_number--;
		if (cursor_number < 0)
		{
			cursor_number = 2;
		}
		// カーソル移動音を再生する処理
		PlaySoundMem(CursorBgmHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(250, CursorBgmHandle);  // 音量調整
		CheckSoundMem(CursorBgmHandle);
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		cursor_number++;
		if (cursor_number > 2)
		{
			cursor_number = 0;
		}
		// カーソル移動音を再生する処理
		PlaySoundMem(CursorBgmHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(300, CursorBgmHandle);  // 音量調整
		CheckSoundMem(CursorBgmHandle);
	}

	// 決定する
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		on_button = true;
		Animation();
	}

	// ボタンが押された場合、遷移先のシーンを返す
	if (on_button == true)
	{
		// アニメーションの待機時間を加算する
		wait_time += delta_second;
		if (wait_time >= 1.0f) // アニメーションの待機時間が1秒以上になったら
		{
			// 待機時間をリセットする
			wait_time = 0.0f;
			on_button = false;
			// 遷移先のシーンを返す
			switch (cursor_number)
			{
			case 0:
				return eSceneType::eInGame;
			/*case 1:
				return eSceneType::eHelp;*/
			case 2:
				return eSceneType::eEnd;
			}
		}
	}
	// 現在のシーンを返す
	return eSceneType::eTitle;
}

//描画処理
void TitleScene::Draw() const
{
	DrawGraph(0, 0, title_image, TRUE);
	int cursor = cursor_number * 100; // カーソルの位置を計算
	DrawGraph(0, 300 + cursor, cursor_image, TRUE); // カーソルを描画
	
	DrawGraph(90, 240, start_image, TRUE);
	DrawGraph(115, 350, help_image, TRUE);
	DrawGraph(90, 330, shuryo_image, TRUE);
}

void TitleScene::Finalize()
{
	// タイトルのBGMを停止する処理
	StopSoundMem(TitleBgmHandle);
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

// アニメーション処理
void TitleScene::Animation()
{
	switch (cursor_number)
	{
		case 0:
			if (on_button == true)
			{
				start_image = start1_image;
				break;
			}
		case 1:
			if (on_button == true)
			{
				help_image = help1_image;
				break;
			}
		case 2:
			if (on_button == true)
			{
				shuryo_image = shuryo1_image;
				break;
			}
	default:
		break;
	}
}

void TitleScene::TitleBgm()
{
	// タイトルのBGMを再生する処理
	if(CheckSoundMem(TitleBgmHandle) == 0)
	{
		PlaySoundMem(TitleBgmHandle, DX_PLAYTYPE_LOOP, TRUE);
		CheckSoundMem(TitleBgmHandle);
	}
}
