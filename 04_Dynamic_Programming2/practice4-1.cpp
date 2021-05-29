#include <iostream>
#include <queue>
#include <stack>
#include <climits>

using namespace std;
struct Location {
    int x; //第幾列
    int y; //第幾行
};

class Maze {
    int **mazeData;
    int mazeHeight;
    int mazeWidth;
    Location startLocation;
    Location endLocation;

    int moveX[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int moveY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

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
        if (location.x > mazeHeight || location.x <= 0)return false;
        if (location.y > mazeWidth || location.y <= 0)return false;
        if (mazeData[location.x - 1][location.y - 1] == 1)return false;
        return true;
    }

    bool seekPossibleWay(Location location, queue<Location> &nextData, Log **stepLogger) {
        bool hasFound = false;
        for (int i = 0; i < 8; i++) {
            if (isValidLocation({location.x + moveX[i], location.y + moveY[i]})
                && stepLogger[location.x + moveX[i] - 1][location.y + moveY[i] - 1].step >
                   stepLogger[location.x - 1][location.y - 1].step + 1) {
                stepLogger[location.x + moveX[i] - 1][location.y + moveY[i] - 1] = {
                        stepLogger[location.x - 1][location.y - 1].step + 1, location};
                nextData.push({location.x + moveX[i], location.y + moveY[i]});
                hasFound = true;
            }
        }
        return hasFound;
    }

    void bfs() {
        Log **loggerTable = new Log *[mazeHeight];
        for (int i = 0; i < mazeHeight; i++) {
            loggerTable[i] = new Log[mazeWidth];
            for (int j = 0; j < mazeWidth; j++) {
                loggerTable[i][j].step = INT_MAX;
            }
        }
        queue<Location> nextLocations;
        Location currentLocation = startLocation;
        loggerTable[startLocation.x - 1][startLocation.y - 1].step = 0;
        seekPossibleWay(startLocation, nextLocations, loggerTable);
        while (nextLocations.empty() == false) {
            do {
                currentLocation = nextLocations.front();
                nextLocations.pop();
            } while (!seekPossibleWay(currentLocation, nextLocations, loggerTable) && !nextLocations.empty());
        }

        stack<Location> result;
        currentLocation = endLocation;
        cout << loggerTable[endLocation.x - 1][endLocation.y - 1].step + 1 << endl;
        result.push(currentLocation);
        while (currentLocation.x != startLocation.x || currentLocation.y != startLocation.y) {
            currentLocation = loggerTable[currentLocation.x - 1][currentLocation.y - 1].cameFrom;
            result.push(currentLocation);
        }

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