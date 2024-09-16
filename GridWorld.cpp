#include <tuple>
#include <algorithm>

const int gridSize = 5;                        // グリッドのサイズ
const int goalState = gridSize * gridSize - 1; // 最後のセルがゴール

class GridWorld
{
public:
  int state;

  GridWorld()
  {
    reset();
  }

  // 環境をリセットして初期状態に戻す
  void reset()
  {
    state = 0; // スタート地点 (0,0)
  }

  // 行動：0=左、1=右、2=上、3=下、4=左上、5=右上、6=左下、7=右下
  std::tuple<int, int, bool> step(int action)
  {
    int reward = -0.01; // 中間報酬として負の値を設定
    bool done = false;

    // グリッド内の位置を計算
    int row = state / gridSize;
    int col = state % gridSize;

    switch (action)
    {
    case 0:
      if (col > 0)
        col--;
      break; // 左へ
    case 1:
      if (col < gridSize - 1)
        col++;
      break; // 右へ
    case 2:
      if (row > 0)
        row--;
      break; // 上へ
    case 3:
      if (row < gridSize - 1)
        row++;
      break; // 下へ
    case 4:
      if (row > 0 && col > 0)
      {
        row--;
        col--;
      }
      break; // 左上
    case 5:
      if (row > 0 && col < gridSize - 1)
      {
        row--;
        col++;
      }
      break; // 右上
    case 6:
      if (row < gridSize - 1 && col > 0)
      {
        row++;
        col--;
      }
      break; // 左下
    case 7:
      if (row < gridSize - 1 && col < gridSize - 1)
      {
        row++;
        col++;
      }
      break; // 右下
    }

    state = row * gridSize + col;

    // ゴールに近づいたら少額の報酬を与える
    if (state == goalState)
    {
      reward = 1.0; // ゴールに到達したら報酬を1に設定
      done = true;
    }
    else
    {
      // ゴールに近づくたびに報酬を増やす (ゴールが (4,4) の場合)
      int goalRow = goalState / gridSize;
      int goalCol = goalState % gridSize;
      int distanceToGoal = std::abs(goalRow - row) + std::abs(goalCol - col);
      reward += (1.0 / (distanceToGoal + 1)); // 距離に応じて報酬を増やす
    }

    return std::make_tuple(state, reward, done);
  }
};
