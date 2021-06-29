/**
* Minimum Size Subarray Sum
*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

//暴利法
int optimalSumLengthBruteForce(int target, vector<int> numList) {
    int windowSize = 1;
    while (windowSize <= numList.size()) {
        for (int i = 0; i < numList.size() - windowSize; i++) {
            int sum = 0;
            for (int j = 0; j < windowSize; j++) {
                sum += numList[i + j];
            }
            if (sum >= target) {
                return windowSize;
            }
        }
        windowSize++;
    }
    return 0;
}

int optimalSumLength(int target, vector<int> numList) {
    int length = INT_MAX;
    int lowerBound = 0;
    int upperBound = 0;
    int sum = 0;
    bool hasFound = false;
    while (upperBound < numList.size()) {
        sum += numList[upperBound];
        while (lowerBound <= upperBound && sum >= target) {
            sum -= numList[lowerBound];
            length = min(length, upperBound - lowerBound + 1);
            hasFound = true;
            lowerBound += 1;
        }
        upperBound += 1;
    }
    if (!hasFound)return 0;
    return length;
}

int main() {
    vector<int> numList;
    int length;
    int target;
    cin >> length;
    cin >> target;
    for (int i = 0; i < length; i++) {
        int input;
        cin >> input;
        numList.push_back(input);
    }
    cout << optimalSumLength(target, numList) << endl;
}