#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#include <string>

HelpScene::HelpScene()
{
	next_scene = eSceneType::eHelp;
}

HelpScene::~HelpScene()
{

}

void HelpScene::Initialize()
{
	printf("ヘルプシーン");
}

eSceneType HelpScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputControl* pad_input = InputControl::GetInstance();

	// タイトル画面に遷移する
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		return eSceneType::eTitle;
	}

	return eSceneType::eHelp;
}

// 描画処理
void HelpScene::Draw() const
{
	DrawFormatString(120, 140, GetColor(255, 255, 0), "ヘルプシーン");

}

void HelpScene::Finalize()
{

}

const eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
