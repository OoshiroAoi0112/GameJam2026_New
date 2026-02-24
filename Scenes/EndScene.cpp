#include "EndScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#include <string>

int EndScene_image1;
int EndScene_image2;
int EndScene_image3;
int SantaClaus_image;
float x = 0;
float y_Text1 = 150;
float y_Text2 = 150;
float y_Text3 = 150;
float stop_y = 240;
float speed = 0.25f;
float alpha = 0;
int timer = 0;
int t;

EndScene::EndScene()
{
	next_scene = eSceneType::eEnd;

	// 画像の読み込み
	EndScene_image1 = LoadGraph("Resource/image/EndScene/thank you.png");
	EndScene_image2 = LoadGraph("Resource/image/EndScene/for.png");
	EndScene_image3 = LoadGraph("Resource/image/EndScene/playing.png");
	SantaClaus_image = LoadGraph("Resource/image/EndScene/Santa Claus.png");
}

EndScene::~EndScene()
{

}

void EndScene::Initialize()
{
	printf("エンドシーン");
}

eSceneType EndScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputControl* pad_input = InputControl::GetInstance();

	// タイトル画面に遷移する
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		return eSceneType::eTitle;
	}

	return eSceneType::eEnd;

}

// 描画処理
void EndScene::Draw() const
{
	// 毎フレーム 1 ずつ増える
	timer++;

	//サンタの画像の座標を更新（右へ移動）
	x = x + 0.5;
	DrawGraph(x, -40, SantaClaus_image, TRUE);

	//画像を徐々に濃くする処理
	if (alpha < 255) {
		alpha += 0.1; // 徐々に濃くする
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	// --- 座標更新の処理&画像の描画するタイミング ---
		// もし y_Text が stop_y より小さければ、下に動かす
	if (timer > 0 && y_Text1 < stop_y)
	{
		y_Text1 += speed ;
	}

	if (timer > 400 && y_Text2 < stop_y) //約6.6秒後：400フレーム経過後）
	{
		y_Text2 += speed;
	}

	if (timer > 700 && y_Text3 < stop_y) //約11.6秒後：700フレーム経過後）
	{
		y_Text3 += speed;
	}


	//Thank you for Plauingの描画
	DrawGraph(0, y_Text1, EndScene_image1, TRUE);

	DrawGraph(580, y_Text2, EndScene_image2, TRUE);

	DrawGraph(800, y_Text3, EndScene_image3, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// 設定をリセット（重要！）
}

void EndScene::Finalize()
{

}

const eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}