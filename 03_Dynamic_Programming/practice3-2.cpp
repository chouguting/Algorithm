#include<iostream>
#include<vector>

using namespace std;

class LCS {
private:
    struct element {
        int value;
        int nextX;
        int nextY;
    };
    element** valueMatrix;
public:
    LCS(string str1, string str2) {
        int height = str1.length();
        int width = str2.length();
        valueMatrix = new element *[height + 1];
        for (int i = 0; i <= height; i++) {
            valueMatrix[i] = new element[width + 1];
            valueMatrix[i][0] = {0, i, 0};
        }
        for (int i = 0; i <= width; i++) {
            valueMatrix[0][i] = {0, 0, i};
        }
        for (int i = 1; i <= height; i++) {
            for (int j = 1; j <= width; j++) {
                if (str1.at(i - 1) == str2.at(j - 1)) {
                    valueMatrix[i][j] = {valueMatrix[i - 1][j - 1].value + 1, i - 1, j - 1};
                } else if (valueMatrix[i - 1][j].value >= valueMatrix[i][j - 1].value) {
                    valueMatrix[i][j] = {valueMatrix[i - 1][j].value, i - 1, j};
                } else {
                    valueMatrix[i][j] = {valueMatrix[i][j - 1].value, i, j - 1};
                }
            }
        }
    }

    void printLCS(int &counter, int i, int j) {
        if (i == 0 || j == 0)return;
        if (valueMatrix[i][j].nextX == i - 1 && valueMatrix[i][j].nextY == j - 1) {
            printLCS(counter, i - 1, j - 1);
            counter += 1;
        } else if (valueMatrix[i][j].nextX == i - 1) {
            printLCS(counter, i - 1, j);
        } else {
            printLCS(counter, i, j - 1);
        }
    }
};

int main() {
    string str1, str2;
    cin >> str1;
    cin >> str2;
    LCS lcs(str1, str2);
    int counter = 0;
    lcs.printLCS(counter, str1.length(), str2.length());
    cout << counter << endl;
    return 0;
}
