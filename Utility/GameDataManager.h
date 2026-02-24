#pragma once
#include <string>

class GameDataManager 
{
private:
    int score = 0;  // スコア

    // コンストラクタをprivateにしてシングルトンにする
    GameDataManager() {}

public:
    // シングルトンインスタンス取得
    static GameDataManager& GetInstance();

    // ゲッター
    int GetScore() const;
    // セッター
    void SetScore(int value);

    // コピー禁止
    GameDataManager(const GameDataManager&) = delete;
    GameDataManager& operator=(const GameDataManager&) = delete;
};
