/**
 *4_1 搜尋迷宮路徑
 */

#include <iostream>
#include <queue>
#include <stack>
#include <climits>

using namespace std;
struct Location {
    int x; //第幾列 (上下,下方為正)
    int y; //第幾行 (左右,右方為正)
};

class Maze {
    int **mazeData;
    int mazeHeight;
    int mazeWidth;
    Location startLocation;
    Location endLocation;

    //這兩個陣列同時存了移動時各方向該加減的值
    int moveX[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int moveY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    //可農實記錄步數及來的路徑方向的結構
    struct Log {
        int step;
        Location cameFrom;
    };

public:
    Maze() {
        cin >> mazeHeight >> mazeWidth;
        cin >> startLocation.x >> startLocation.y;
        cin >> endLocation.x >> endLocation.y;
        mazeData = new int *[mazeHeight];
        for (int i = 0; i < mazeHeight; i++) {
            mazeData[i] = new int[mazeWidth];
        }
    }

    void inputData() {
        for (int i = 0; i < mazeHeight; i++) {
            string inputStr;
            cin >> inputStr;
            for (int j = 0; j < mazeWidth; j++) {
                mazeData[i][j] = inputStr.at(j) - '0';
            }
        }
    }

    bool isValidLocation(Location location) {
        if (location.x > mazeHeight || location.x <= 0)return false;  //如果座標小於零或是大於寬和高 代表是不合法的地點
        if (location.y > mazeWidth || location.y <= 0)return false;
        if (mazeData[location.x - 1][location.y - 1] == 1)return false; //如果該座標在迷宮DATA中存的是1 代表是牆壁 不能走
        return true;
    }

    bool seekPossibleWay(Location location, queue<Location> &nextData, Log **stepLogger) {
        bool hasFound = false; //附近有沒有還能去的點
        for (int i = 0; i < 8; i++) { //測試8個方位
            if (isValidLocation({location.x + moveX[i], location.y + moveY[i]})  //判斷該方向能不能走
                && stepLogger[location.x + moveX[i] - 1][location.y + moveY[i] - 1].step >    //判斷該方向目前存的步數結果是不是比現在找出來的差
                   stepLogger[location.x - 1][location.y - 1].step + 1) {
                stepLogger[location.x + moveX[i] - 1][location.y + moveY[i] - 1] = {             //如果符合的話更新該方向的數值 變成現在這個點的步數再加一
                        stepLogger[location.x - 1][location.y - 1].step + 1, location};
                nextData.push({location.x + moveX[i], location.y + moveY[i]});     //把能走的點排進Queue (bfs用)
                hasFound = true;
            }
        }
        return hasFound;
    }

    /*
     * 注意: 陣列的Index都會和實際座標差1,
     *      例如(3,4) 會記錄在 loggerTable[3-1][4-1]=loggerTable[2][3]
     */

    void bfs() {
        Log **loggerTable = new Log *[mazeHeight];  //建立一個紀錄表 會記錄到這一點的最佳步數 和上一步從哪裡來
        for (int i = 0; i < mazeHeight; i++) {   //初始化紀錄表
            loggerTable[i] = new Log[mazeWidth];
            for (int j = 0; j < mazeWidth; j++) {
                loggerTable[i][j].step = INT_MAX; //紀錄表的預設值都是無限大
            }
        }
        queue<Location> nextLocations; //因為是BFS 用QUEUE去記錄下一個要走的位置
        Location currentLocation = startLocation;   //紀錄目前的位置
        loggerTable[startLocation.x - 1][startLocation.y - 1].step = 0; //(1,1)是起點 步數一定是0步
        seekPossibleWay(startLocation, nextLocations, loggerTable); //從起點開始找四面八方可以去的點 (找的時候順便會給周圍的點紀錄可以從現在這個點過去)
        while (nextLocations.empty() == false) { //如果還有能走的點 就繼續試
            do {
                currentLocation = nextLocations.front();  //把下一個要處理的點取出
                nextLocations.pop();
            } while (!seekPossibleWay(currentLocation, nextLocations, loggerTable) && !nextLocations.empty()); //如果這個點四周都沒地方可以去了而取還有下一個可處理的點就重取點
        }

        stack<Location> result;  //用STACK存結果 因為結果要從後往前找出 等一下要把它倒轉
        currentLocation = endLocation;  //從尾端開始往回搜尋
        cout << loggerTable[endLocation.x - 1][endLocation.y - 1].step + 1 << endl; //印出最短路徑長度 (要再加一 因為他要的不是步數 而是點數)
        //往前紀錄結果
        result.push(currentLocation);
        while (currentLocation.x != startLocation.x || currentLocation.y != startLocation.y) {
            currentLocation = loggerTable[currentLocation.x - 1][currentLocation.y - 1].cameFrom;
            result.push(currentLocation);
        }
        //Stack取出會反轉存入的順序 直接印出結果
        while (!result.empty()) {
            currentLocation = result.top();
            result.pop();
            cout << "(" << currentLocation.x << "," << currentLocation.y << ")" << endl;
        }
        delete loggerTable;
    }

};

int main() {
    Maze maze;
    maze.inputData();
    maze.bfs();
}