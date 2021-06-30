#include <vector>
#include <iostream>
using namespace std;
void printSnowmanLife(vector<long long int> snowman, vector<long long int> temp, vector<long long int> tempAcc){
    for (int i = 0; i < snowman.size(); i++) {
        if (snowman[i] > tempAcc[tempAcc.size() - 1]) {
            cout << "-1 ";
        } else {
            auto lower = lower_bound(tempAcc.begin(), tempAcc.end(), snowman[i]);
            cout << lower - tempAcc.begin() + 1<<" ";
        }
        snowman[i + 1] =snowman[i + 1] + tempAcc[i];
    }
}

int main() {
    long long int l;
    long long int s;
    long long int t;
    cin >> l;

    vector<long long int> snowman;
    vector<long long int> temp;
    vector<long long int> tempAcc;

    for (long long int i = 0; i < l; i++) {
        cin >> s;
        snowman.push_back(s);
    }
    for (long long int i = 0; i < l; i++) {
        cin >> t;
        temp.push_back(t);
        if (i == 0) {
            tempAcc.push_back(t);
        } else {
            tempAcc.push_back(tempAcc[i - 1]+t);
        }
    }
    printSnowmanLife(snowman, temp, tempAcc);
    cout << endl;
}