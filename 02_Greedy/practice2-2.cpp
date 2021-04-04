/**
 * Practice2-2 Fractional_knapsack_problem
*/

#include <iostream>
#include <vector>


struct Item {
    int value;
    int weight;
};

int compareItem(const void *one, const void *two) {
    Item a = *((Item *) one);
    Item b = *((Item *) two);
    if ((double) a.value / a.weight < (double) b.value / b.weight)
        return 1;
    if ((double) a.value / a.weight == (double) b.value / b.weight)
        return 0;
    return -1;
}

std::vector<Item> sortByValuePerWeight(std::vector<Item> itemList) {
    qsort(&itemList[0], itemList.size(), sizeof(Item), compareItem);
    return itemList;
}

int main() {
    int maxCapacity;
    std::cin >> maxCapacity;

    std::vector<Item> itemList;
    int inputValue, inputWeight;
    while (std::cin >> inputValue >> inputWeight) {
        itemList.push_back({inputValue, inputWeight});
    }

    itemList = sortByValuePerWeight(itemList);

    int capacityLeft = maxCapacity;
    int itemListIndex = 0;
    double soldValue = 0;

    while (capacityLeft > 0) {
        if (itemList[itemListIndex].weight <= capacityLeft) {
            soldValue += itemList[itemListIndex].value;
            capacityLeft -= itemList[itemListIndex].weight;
            itemListIndex++;
        } else {
            soldValue +=
                    (double) itemList[itemListIndex].value * ((double) capacityLeft / itemList[itemListIndex].weight);
            break;
        }
    }
    printf("%.6lf\n", soldValue);
}