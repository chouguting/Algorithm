/**
 * Practice1-1 Merge Sort
 * */
#include <iostream>
#include <vector>

std::vector<int> merge(std::vector<int> firstList, std::vector<int> secondList) {
    std::vector<int> tempList;

    int index1 = 0, index2 = 0;
    while (index1 < firstList.size() && index2 < secondList.size()) {
        if (firstList[index1] < secondList[index2]) {
            tempList.push_back(firstList[index1++]);
        } else if (firstList[index1] > secondList[index2]) {
            tempList.push_back(secondList[index2++]);
        } else {
            tempList.push_back(firstList[index1++]);
            tempList.push_back(secondList[index2++]);
        }
    }

    while (index1 < firstList.size()) {
        tempList.push_back(firstList[index1++]);
    }

    while (index2 < secondList.size()) {
        tempList.push_back(secondList[index2++]);
    }
    return tempList;
}

std::vector<int> mergeSort(std::vector<int> inputList) {
    if (inputList.size() == 1)return inputList;

    std::vector<int> listFirstHalf;
    std::vector<int> listSecondHalf;

    for (int i = 0; i < inputList.size(); i++) {
        if (i < inputList.size() / 2) {
            listFirstHalf.push_back(inputList[i]);
        } else {
            listSecondHalf.push_back(inputList[i]);
        }
    }

    listFirstHalf = mergeSort(listFirstHalf);
    listSecondHalf = mergeSort(listSecondHalf);

    return merge(listFirstHalf, listSecondHalf);
}

int main() {
    std::vector<int> theList;
    int input;
    while (std::cin >> input) {
        theList.push_back(input);
    }
    theList = mergeSort(theList);
    for (int i = 0; i < theList.size(); i++) {
        std::cout << theList[i] << " ";
    }
    std::cout << std::endl;
}