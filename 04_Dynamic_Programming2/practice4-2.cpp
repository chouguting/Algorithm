#include <iostream>
#include <vector>
#include <algorithm>
#include "string.h"

using namespace std;

class Graph {
private:
    vector<int> adjacencyList[301];
    int graphSize = 0; //最大Node編號
public:
    Graph(int nodeCount) {
        graphSize = nodeCount;
    }

    void addEdge(int vertex1, int vertex2) {
        //創造相鄰串列
        adjacencyList[vertex1].push_back(vertex2);
        adjacencyList[vertex2].push_back(vertex1);
        if (vertex1 > graphSize || vertex2 > graphSize) {
            graphSize = max(vertex1, vertex2);
        }
    }

    void seeker(int currentNode, int *currentTable, int *tempMaxResult, int &tempMaxBlackNodeCount) {
        int currentBlackResult[301];
        int currentWhiteResult[301];
        //試試將這一點設為黑色
        memcpy(currentBlackResult, currentTable, sizeof(currentBlackResult));
        currentBlackResult[currentNode] = 1;
        //試試將這一點設為白色
        memcpy(currentWhiteResult, currentTable, sizeof(currentWhiteResult));
        currentWhiteResult[currentNode] = 0;
        //如果這一點是黑色 就將鄰居(還沒上色的) 設為白色
        int paintCount = 0;
        for (int i = 0; i < adjacencyList[currentNode].size(); i++) {
            if (currentBlackResult[adjacencyList[currentNode][i]] == -1) {
                currentBlackResult[adjacencyList[currentNode][i]] = 0;
                paintCount += 1;
            }
        }

        //如果這點是黑色 且還沒結束
        if (paintCount + currentNode < graphSize) {
            int nextNode = 1;
            //計算下一個要處理的點
            while (nextNode <= graphSize) {
                nextNode++;
                if (currentBlackResult[nextNode] == -1)break;
            }
            seeker(nextNode, currentBlackResult, tempMaxResult, tempMaxBlackNodeCount);
        } else {  //如果這點是黑色 且已經結束
            int blackNodeCount = 0;
            //計算現在這個結果中有幾個黑點
            for (int i = 0; i <= graphSize; i++) {
                if (currentBlackResult[i] == 1)blackNodeCount += 1;
            }
            //如果現在這個結果的黑點數量 比之前最好的還要多 就更新資料
            if (blackNodeCount > tempMaxBlackNodeCount) {
                tempMaxBlackNodeCount = blackNodeCount;
                memcpy(tempMaxResult, currentBlackResult, sizeof(currentBlackResult));
            }
        }

        //如果這點是白色 且還沒結束
        if (currentNode < graphSize) {
            int nextNode = 1;
            //計算下一個要處理的點
            while (nextNode <= graphSize) {
                nextNode++;
                if (currentWhiteResult[nextNode] == -1)break;
            }
            seeker(nextNode, currentWhiteResult, tempMaxResult, tempMaxBlackNodeCount);
        } else { //如果這點是白色 且已經結束
            int blackNodeCount = 0;
            //計算現在這個結果中有幾個黑點
            for (int i = 0; i <= graphSize; i++) {
                if (currentWhiteResult[i] == 1)blackNodeCount += 1;
            }
            //如果現在這個結果的黑點數量 比之前最好的還要多 就更新資料
            if (blackNodeCount > tempMaxBlackNodeCount) {
                tempMaxBlackNodeCount = blackNodeCount;
                memcpy(tempMaxResult, currentWhiteResult, sizeof(currentWhiteResult));
            }
        }

    }

    void printOptimalGraphColoring() {
        int tempMaxResult[301];   //用來存 發現到的最好結果
        int currentResult[301];   //用來存 目前找到的結果
        memset(currentResult, -1, sizeof(currentResult)); //全部先設為負一
        memset(tempMaxResult, -1, sizeof(tempMaxResult)); //全部先設為負一
        int tempMaxBlackNodeCount = 0;    //存 發現到的最好結果的黑點數
        //從1號開始找結果
        seeker(1, currentResult, tempMaxResult, tempMaxBlackNodeCount);
        cout << tempMaxBlackNodeCount << endl;
        bool isFirst = true;
        for (int i = 1; i <= graphSize; i++) {
            if (tempMaxResult[i] == 1) {
                if (isFirst) {
                    isFirst = false;
                } else {
                    cout << " ";
                }
                cout << i;
            }
        }
        cout << endl;
    }
};

int main() {
    int times;
    cin >> times;
    for (int t = 0; t < times; t++) {
        int nodeCount, edgeCount;
        cin >> nodeCount >> edgeCount;
        Graph graph(nodeCount);
        for (int i = 0; i < edgeCount; i++) {
            int vertex1, vertex2;
            cin >> vertex1 >> vertex2;
            graph.addEdge(vertex1, vertex2);
        }
        graph.printOptimalGraphColoring();
    }
}