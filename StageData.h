#pragma once

#include "Objects/GameObject.h"
#include "Objects/Block/Block.h"
#include "Scenes/SceneBase.h"
#include <vector>
#include <map>

#include "Utility/Vector2D.h"

/// <summary>
/// 隣接情報のキー
/// </summary>
enum eAdjacentDirection : unsigned char
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};
// ブロック（足場）の情報
struct BlockSpawnData
{
	Vector2D pos;
	BlockType type;
};

class StageData : public GameObject
{
private:
	static StageData* instance;

	Vector2D generate_location;

private:
	std::vector<Vector2D> enemy_spawn_positions;  //エネミー用
	std::vector<Vector2D> item_spwn_positions;//アイテム用
	std::vector<BlockSpawnData> block_spawn_positions;// ブロック用（足場）
	std::vector<Vector2D> snowman_positions;  // 雪だるま用
	std::vector<Vector2D> city_positions;  // 街並み用
	std::vector<Vector2D> tree_positions;  // 枯れ木
	std::vector<Vector2D> house_positions;//ハウス(ゴール)
	std::vector<Vector2D> santa_positions;//サンタ

	int snowman_image;  // 雪だるま
	int city_image;  // 街並み
	int tree_image;  //枯れ木
	int house_image; //ハウス(ゴール)
	int santa_image; //サンタ
public:
	StageData() = default;

	// コピーガード
	StageData(const StageData&) = delete;
	StageData& operator = (const StageData&) = delete;
	// ~コピーガード

public:
	static StageData* GetInstance();

	float s_location;

	~StageData();

public:

// ステージデータを読み込む
	void Load();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	//位置情報取得処理
	float GetLocation() const;
	Vector2D GetVelocity();
	void SetVelocity(float velo);

	//エネミーの出現位置取得
	const std::vector<Vector2D>& GetEnemySpawnPositions() const;
	//アイテムの出現位置取得
	const std::vector<Vector2D>& GetItemSpawnPositions() const;
	//ブロック（足場）の出現位置取得
	const std::vector<BlockSpawnData>& GetBlockSpawnPositions() const;
};

