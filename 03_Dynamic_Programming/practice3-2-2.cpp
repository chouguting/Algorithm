#include<iostream>
#include<vector>

using namespace std;

class LCS {
private:
    int** valueMatrix;
public:
    LCS(string str1, string str2) {
        int height = str1.length();
        int width = str2.length();
        valueMatrix = new int *[height + 1];
        for (int i = 0; i <= height; i++) {
            valueMatrix[i] = new int[width + 1];
            valueMatrix[i][0] = 0;
        }
        for (int i = 0; i <= width; i++) {
            valueMatrix[0][i] = 0;
        }
        for (int i = 1; i <= height; i++) {
            for (int j = 1; j <= width; j++) {
                if (str1.at(i - 1) == str2.at(j - 1)) {
                    valueMatrix[i][j] = valueMatrix[i - 1][j - 1]+1;
                } else if (valueMatrix[i - 1][j] >= valueMatrix[i][j - 1]) {
                    valueMatrix[i][j] = valueMatrix[i - 1][j];
                } else {
                    valueMatrix[i][j] = valueMatrix[i][j - 1];
                }
            }
        }
    }
    void printLCS(int &counter, int i, int j) {
        counter=valueMatrix[i][j];
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
