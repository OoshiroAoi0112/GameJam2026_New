#include "GameDataManager.h"
#include <fstream>
#include <vector>
#include <algorithm>

// シングルトンインスタンスの定義
GameDataManager& GameDataManager::GetInstance() {
    static GameDataManager instance;
    return instance;
}

// ゲッター
int GameDataManager::GetScore() const {
    return score;
}

// セッター
void GameDataManager::SetScore(int value) {
    score = value;
}

