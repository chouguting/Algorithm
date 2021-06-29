/**
 * 5_1_0/1_knapsack_problem_depth-first_search
 */
#include <iostream>
#include <vector>

using namespace std;

struct Item {
    long id; //代號
    long weight; //重量
    long value;  //價值
    double unitValue; //單位價值
};

long capacity; //背包承重
long optimalValue;
vector<Item> optimalContents;

std::vector<Item> mergeWithValue(std::vector<Item> &firstList, std::vector<Item> &secondList) {
    std::vector<Item> tempList;
    long index1 = 0, index2 = 0;
    while (index1 < firstList.size() && index2 < secondList.size()) {
        if (firstList[index1].unitValue > secondList[index2].unitValue) {
            tempList.push_back(firstList[index1++]);
        } else if (firstList[index1].unitValue < secondList[index2].unitValue) {
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

std::vector<Item> mergeSortWithValue(std::vector<Item> &inputList) {
    if (inputList.size() == 1)return inputList;
    std::vector<Item> listFirstHalf;
    std::vector<Item> listSecondHalf;
    for (long i = 0; i < inputList.size(); i++) {
        if (i < inputList.size() / 2) {
            listFirstHalf.push_back(inputList[i]);
        } else {
            listSecondHalf.push_back(inputList[i]);
        }
    }
    listFirstHalf = mergeSortWithValue(listFirstHalf);
    listSecondHalf = mergeSortWithValue(listSecondHalf);
    return mergeWithValue(listFirstHalf, listSecondHalf);
}

void addItemsAndMaximizeValue(vector<Item> &items, long currentIndex, long capacityLeft, long currentValue,long currentWeight
        ,vector<Item> currentChoosen) {
    //檢查目前存德是不是已經超過容量了
    if (currentWeight > capacity||currentIndex >= items.size())return;
    //如果現在這點的狀況比目前最好的還要好 就更新數值
    if (currentValue > optimalValue) {
        optimalValue = currentValue;
        optimalContents.assign(currentChoosen.begin(), currentChoosen.end());
    }

    long capacityCounter = 0;
    double potentialValueCounter = currentValue;
    long offset = 0;
    while (currentIndex + offset < items.size()) {
        capacityCounter += items[currentIndex + offset].weight;
        if (capacityCounter > capacityLeft) {
            long chosenUnit = items[currentIndex + offset].weight - (capacityCounter - capacityLeft);
            potentialValueCounter += items[currentIndex + offset].unitValue * chosenUnit;
            break;
        }
        potentialValueCounter += items[currentIndex + offset].value;
        offset += 1;
    }
    if (potentialValueCounter <= optimalValue)return;
    vector<Item> addThisNodeList;
    addThisNodeList.assign(currentChoosen.begin(), currentChoosen.end());
    addThisNodeList.push_back(items[currentIndex]);

    //要加這一點
    addItemsAndMaximizeValue(items, currentIndex + 1, capacityLeft - items[currentIndex].weight,
                                 currentValue + items[currentIndex].value,currentWeight+ items[currentIndex].weight, addThisNodeList);
    //不加這一點
    addItemsAndMaximizeValue(items, currentIndex + 1, capacityLeft, currentValue,currentWeight, currentChoosen);
}

int main() {
    cin >> capacity;
    long id, weight, value;
    vector<Item> collectedItems;
    while (true) {
        cin >> id >> weight >> value;
        if (id == weight && weight == value && id == -1) {
            break;
        }
        collectedItems.push_back({id, weight, value, (double) value / weight});
    }
    collectedItems = mergeSortWithValue(collectedItems);
    vector<Item> logger;
    addItemsAndMaximizeValue(collectedItems, 0, capacity, 0,0, logger);
    for (long i = 0; i < optimalContents.size(); i++) {
        cout << optimalContents[i].id << " ";
    }
    cout << endl << optimalValue << endl;
}