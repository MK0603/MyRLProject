#include <iostream>
#include "GridWorld.cpp" // GridWorldクラスのインクルード
#include "QLearning.cpp" // QLearningクラスのインクルード

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <windows.h> // Windows環境でのUTF-8設定用

int main()
{
    // コンソールの出力をUTF-8に設定（Windows限定）
    SetConsoleOutputCP(CP_UTF8);

    srand(static_cast<unsigned>(time(0))); // 乱数の初期化

    // 環境とQ-learningアルゴリズムの初期化
    GridWorld env;
    QLearning agent(gridSize * gridSize, 8, 0.1, 0.9, 0.1);

    // 学習プロセス
    const int totalEpisodes = 200000;
    const int maxStepsPerEpisode = 200000;

    for (int episode = 0; episode < totalEpisodes; episode++)
    {
        env.reset();
        int state = env.state;

        for (int step = 0; step < maxStepsPerEpisode; step++)
        {
            // 行動選択
            int action = agent.chooseAction(state);
            // std::cout << "Episode: " << episode << ", Step: " << step << ", State: " << state
            //           << ", Action: " << action << std::endl;
            // 行動実行
            auto [nextState, reward, done] = env.step(action);

            // デバッグ出力: 状態、行動、報酬を表示
            // if (0 != reward)
            // {
            //     std::cout << "Episode: " << episode << ", Step: " << step << ", State: " << state
            //               << ", Action: " << action << ", Reward: " << reward << std::endl;
            // }

            // Qテーブルの更新
            agent.update(state, action, reward, nextState);

            // 状態を次の状態に更新
            state = nextState;

            if (done)
                break; // ゴールに到達したらエピソード終了
        }
    }

    // 学習後のQテーブルを表示
    agent.printQTable();

    return 0;
}
