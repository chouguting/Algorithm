/**
 * 3_1_Rod_cutting
 */
#include<iostream>

using namespace std;

int bottomUpCutRod(int *thePriceList, int length) {
    int* resultList=new int[length+1];
    resultList[0] = 0;
    for (int i = 1; i <= length; i++) {
        int currentPrice = -1;
        for (int j = 1; j <= i; j++) {
            currentPrice = max(currentPrice, thePriceList[j] + resultList[i - j]);
        }
        resultList[i] = currentPrice;
    }
    return resultList[length];
}

int main() {
    int length;
    cin >> length;
    int *thePriceList = new int[length + 1];
    for (int i = 0; i <= length; i++)thePriceList[i] = 0;
    int inputLength, inputPrice;
    while (true) {
        cin >> inputLength >> inputPrice;
        if (inputLength == 0 && inputPrice == 0)break;
        if (inputLength <= length) {
            thePriceList[inputLength] = inputPrice;
        }
    }
    int result = bottomUpCutRod(thePriceList, length);
    cout << result << endl;
    return 0;
}