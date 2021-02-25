/**
 * Practice1-2 Maximum_Subarray
 * */
#include <iostream>
#include <vector>
#include <climits>

int findMaxCrossingSubArray(std::vector<int> leftList, std::vector<int> rightList) {
    int currentSum = 0;
    int leftMaxSum = INT_MIN;
    for (int i = leftList.size() - 1; i >= 0; i--) {
        currentSum += leftList[i];
        if (currentSum > leftMaxSum) {
            leftMaxSum = currentSum;
        }
    }
    currentSum = 0;
    int rightMaxSum = INT_MIN;
    for (int i = 0; i < rightList.size(); i++) {
        currentSum += rightList[i];
        if (currentSum > rightMaxSum) {
            rightMaxSum = currentSum;
        }
    }
    return leftMaxSum + rightMaxSum;
}

int findMaximumSubArraySum(std::vector<int> inputList) {
    if (inputList.size() == 1)return inputList[0];
    std::vector<int> listFirstHalf;
    std::vector<int> listSecondHalf;

    for (int i = 0; i < inputList.size(); i++) {
        if (i < inputList.size() / 2) {
            listFirstHalf.push_back(inputList[i]);
        } else {
            listSecondHalf.push_back(inputList[i]);
        }
    }

    int firstHalfMaxSum = findMaximumSubArraySum(listFirstHalf);
    int secondHalfMaxSum = findMaximumSubArraySum(listSecondHalf);
    int crossMaxSum = findMaxCrossingSubArray(listFirstHalf, listSecondHalf);

    if (firstHalfMaxSum >= secondHalfMaxSum && firstHalfMaxSum >= crossMaxSum) {
        return firstHalfMaxSum;
    } else if (secondHalfMaxSum >= firstHalfMaxSum && secondHalfMaxSum >= crossMaxSum) {
        return secondHalfMaxSum;
    } else {
        return crossMaxSum;
    }
}

int main() {
    int input;
    std::vector<int> theList;
    while (std::cin >> input) {
        theList.push_back(input);
    }
    std::cout << findMaximumSubArraySum(theList)<<std::endl;
}