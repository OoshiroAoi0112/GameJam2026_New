#pragma once

#include "SceneBase.h"
#include "../Utility/DrawNumber.h"
#include <vector>

class ResultScene : public SceneBase
{

private:
	eSceneType next_scene; // 遷移先のシーン
private:

	//アニメーション用
	const int rank_animation[2] = { 0,1 };
	int animation_count;
	float animation_time;

	int image;
	int rendeer_image;  //トナカイの画像
	int score;

	std::vector<int> Arank_animation;   //Aランクのアニメーション
	std::vector<int> Brank_animation;   //Bランクのアニメーション
	std::vector<int> Crank_animation;   //Cランクのアニメーション
	std::vector<int> score_animation;   //スコアのアニメーション
	std::vector<int> num_image;  //数字用アニメーション
public:

	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	void AnimeCount(float delta_second);

private:
	void ResultBgm();
};

