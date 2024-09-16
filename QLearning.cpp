#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class QLearning
{
public:
  std::vector<std::vector<double>> qTable;
  double learningRate;
  double discountFactor;
  double epsilon;

  QLearning(int stateSize, int actionSize, double alpha, double gamma, double epsilon)
      : qTable(stateSize, std::vector<double>(actionSize, 0.0)),
        learningRate(alpha), discountFactor(gamma), epsilon(epsilon) {}

  // 行動名を取得する関数
  std::string getActionName(int action)
  {
    switch (action)
    {
    case 0:
      return "左";
    case 1:
      return "右";
    case 2:
      return "上";
    case 3:
      return "下";
    case 4:
      return "左上";
    case 5:
      return "右上";
    case 6:
      return "左下";
    case 7:
      return "右下";
    default:
      return "不明";
    }
  }

  // Q値に基づいて行動の優先順位を表示する関数
  void displayQTableWithActions(const std::vector<std::vector<double>> &qTable)
  {
    for (int state = 0; state < qTable.size(); ++state)
    {
      // Q値をコピーして並び替えのためにペア（Q値, 行動番号）を作成
      std::vector<std::pair<double, int>> actions;
      for (int action = 0; action < qTable[state].size(); ++action)
      {
        actions.emplace_back(qTable[state][action], action);
      }

      // Q値に基づいて降順にソート（大きい順）
      std::sort(actions.begin(), actions.end(), std::greater<>());

      // Qテーブルの値を表示
      for (const auto &qValue : qTable[state])
      {
        std::cout << qValue << ",";
      }

      // 行動の優先順位を表示
      std::cout << "\t"; // Q値との間にタブを追加して見やすくする
      for (const auto &[qValue, action] : actions)
      {
        std::cout << getActionName(action) << ":" << qValue << ",";
      }

      std::cout << std::endl; // 次の状態に移る
    }
  }

  int chooseAction(int state)
  {
    // ε-グリーディー法で行動選択
    if ((rand() / double(RAND_MAX)) < epsilon)
    {
      return rand() % 8; // ランダムな行動
    }
    else
    {
      // Q値が最大の行動を選択
      return std::distance(qTable[state].begin(),
                           std::max_element(qTable[state].begin(), qTable[state].end()));
    }
  }

  void update(int state, int action, int reward, int nextState)
  {
    double maxNextQ = *std::max_element(qTable[nextState].begin(), qTable[nextState].end());
    qTable[state][action] = qTable[state][action] + learningRate *
                                                        (reward + discountFactor * maxNextQ - qTable[state][action]);
  }

  void printQTable()
  {
    displayQTableWithActions(qTable);
  }
};
