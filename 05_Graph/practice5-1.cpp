/**
 * 5_1_0/1_knapsack_problem_depth-first_search
 */
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Item {
    int id; //代號
    int weight; //重量
    int value;  //價值
    float unitValue; //單位價值
};


class BackPack {
    int capacity; //背包承重
    int totalValue;
    vector<Item> contents;

    std::vector<Item> mergeWithValue(std::vector<Item> &firstList, std::vector<Item> &secondList) {
        std::vector<Item> tempList;
        int index1 = 0, index2 = 0;
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
        for (int i = 0; i < inputList.size(); i++) {
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

    void addItemsAndMaximizeValue(vector<Item> &items, int currentIndex, int capacityLeft, int currentValue,int currentWeight
                                  ,vector<Item> currentChoosen) {
        //檢查目前存德是不是已經超過容量了

        if (currentWeight > capacity)return;
        //如果現在這點的狀況比目前最好的還要好 就更新數值
        if (currentValue > totalValue) {
            totalValue = currentValue;
            contents.assign(currentChoosen.begin(),currentChoosen.end());
        }
        int capacityCounter = 0;
        float potentialValueCounter = currentValue;
        int offset = 0;
        if (currentIndex >= items.size()) {
            return;
        }

        while (currentIndex + offset < items.size()) {
            capacityCounter += items[currentIndex + offset].weight;
            if (capacityCounter > capacityLeft) {
                int choseUnit = items[currentIndex + offset].weight - (capacityCounter - capacityLeft);
                potentialValueCounter += items[currentIndex + offset].unitValue * choseUnit;
                break;
            }
            potentialValueCounter += items[currentIndex + offset].value;
            offset += 1;
        }
        if (potentialValueCounter <= totalValue)return;

        vector<Item> addThisNodeList(currentChoosen);
        addThisNodeList.push_back(items[currentIndex]);

        //要加這一點
        addItemsAndMaximizeValue(items, currentIndex + 1, capacityLeft - items[currentIndex].weight,
                                 currentValue + items[currentIndex].value,currentWeight+ items[currentIndex].weight, addThisNodeList);
        //不加這一點
        addItemsAndMaximizeValue(items, currentIndex + 1, capacityLeft, currentValue,currentWeight, currentChoosen);

    }

public:
    BackPack(int capacity) {
        this->capacity = capacity;
        totalValue = 0;
    }

    int addItemsAndMaximizeValue(vector<Item> &items) {
        items = mergeSortWithValue(items);
        vector<Item> logger;
        addItemsAndMaximizeValue(items, 0, capacity, 0,0, logger);
    }

    void printBackpackContents() {
        for (int i = 0; i < contents.size(); i++) {
            cout << contents[i].id << " ";
        }
        cout << endl << totalValue << endl;
    }
};

int main() {
    int maxCapacity;
    cin >> maxCapacity;
    BackPack backPack(maxCapacity);
    int id, weight, value;
    vector<Item> collectedItems;
    while (true) {
        cin >> id >> weight >> value;
        if (id == weight && weight == value && id == -1) {
            break;
        }
        collectedItems.push_back({id, weight, value, (float) value / weight});
    }
    backPack.addItemsAndMaximizeValue(collectedItems);
    backPack.printBackpackContents();
}