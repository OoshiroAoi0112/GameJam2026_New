#pragma once

#include "SceneBase.h"
#include <vector>

class HelpScene : public SceneBase
{

private:
	eSceneType next_scene; // 遷移先のシーン
public:
	HelpScene();
	virtual ~HelpScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

};

