#pragma once

#include "SceneBase.h"
#include "../StageData.h"
#include <vector>

class InGameScene : public SceneBase
{

private:
	class Player* player;
	class Enemy* enemy;
	class Item* item;

	StageData stage_data;

	int background_image;
	int santa_image;
	int present_image;

	int delay;

private:
	eSceneType next_scene; // 遷移先のシーン
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	const Vector2D& GetScreenOffset() const;

};

