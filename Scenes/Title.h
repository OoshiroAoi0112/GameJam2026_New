#pragma once

#include "SceneBase.h"
#include <vector>

class TitleScene : public SceneBase
{

private:
	eSceneType next_scene; // 遷移先のシーン
	bool on_button;  // ボタンが押されたかどうかのフラグ
	float wait_time; // 待機時間

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

private:
	void Animation();
private:
	void TitleBgm();
};

