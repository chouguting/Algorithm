/**
* 3_3_0-1_knapsack_problem
*/
#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int id; //代號
    int weight; //重量
    int value;  //價值
};

class BackPack {
    int capacity; //背包承重
    int totalValue;
    vector<Item> contents;

public:
    BackPack(int capacity) {
        this->capacity = capacity;
    }

    void addItemsAndMaximizeValue(vector<Item> items) {
        contents.clear();
        int **valueLogger = new int *[items.size() + 1]; // 物件編號:0~items.size()-1
        int **itemLogger = new int *[items.size() + 1];
        //** itemLogger[i][capacityLeft] 記錄在capacity為j的情況下 要不要選擇第i個物品
        for (int i = 0; i <= items.size(); i++) {
            valueLogger[i] = new int[capacity + 1];
            itemLogger[i] = new int[capacity + 1];
            for (int j = 0; j <= capacity; j++) {
                itemLogger[i][j] = 0;
            }
        }
        for (int i = 0; i <= capacity; i++)valueLogger[0][i] = 0; //編號0是不存在的物品 價值一定是0
        //** valueLogger[i+1][capacityLeft]
        // 代表在最大承重為j的情況下 放入編號i+1(不包含i+1,所以最後可以超出一格)之前的東西經過挑選 所能得到的最大效益
        // 我們最終的目標就是要找 在items.size()以前的東西(也就是全部放入全部物品 0~items.size()-1) 的最大效益挑選方法(在capacity內)
        for (int i = 0; i < items.size(); i++) {
            for (int j = 0; j <= capacity; j++) {
                if (items[i].weight > j) { //如果這個東西放不下
                    valueLogger[i + 1][j] = valueLogger[i][j]; //總價值和同容量下、和放入上一個物品的狀況一樣
                } else {
                    //在 同容量下上一個狀態 和 新增這個物品帶來的價值 間做比較
                    valueLogger[i + 1][j] = max(valueLogger[i][j - items[i].weight] + items[i].value,
                                                valueLogger[i][j]);
                    //記錄(包包的CAPACITY在一個狀況下) 要放入的東西
                    //如果這次有加入新東西 代表在這個狀態下(這個物件和這個容量) 是要選擇加入這個物品
                    if (valueLogger[i][j - items[i].weight] + items[i].value > valueLogger[i][j]) {
                        itemLogger[i][j] = 1;
                    }
                }
            }
        }
        int capacityLeft = capacity;
        for (int i = items.size(); i >= 0; i--) {
            if (itemLogger[i][capacityLeft] == 1) {
                //實際放入一個物品後 剩下承重會降低
                contents.push_back(items[i]);
                capacityLeft -= items[i].weight;
            }
        }
        totalValue = valueLogger[items.size()][capacity];
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
        collectedItems.push_back({id, weight, value});
    }
    backPack.addItemsAndMaximizeValue(collectedItems);
    backPack.printBackpackContents();
}