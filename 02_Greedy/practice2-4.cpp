#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    while (true) {
        int driverCount, workLimit, overTimeSalary;
        cin >> driverCount >> workLimit >> overTimeSalary;
        getchar();
        if (driverCount == workLimit && workLimit == overTimeSalary && workLimit == 0)break;
        vector<int> morningRoutes, eveningRoutes;
        int routeLength;
        for (int i = 0; i < driverCount; i++) {
            cin >> routeLength;
            morningRoutes.push_back(routeLength);
        }
        for (int i = 0; i < driverCount; i++) {
            cin >> routeLength;
            eveningRoutes.push_back(routeLength);
        }
        sort(morningRoutes.begin(), morningRoutes.end());
        sort(eveningRoutes.begin(), eveningRoutes.end());
        int totalCost = 0;
        for (int i = 0; i < driverCount; i++) {
            if (morningRoutes[i] + eveningRoutes[driverCount - 1 - i] > workLimit) {
                totalCost += overTimeSalary * (morningRoutes[i] + eveningRoutes[driverCount - 1 - i] - workLimit);
            }
        }
        cout << totalCost << endl;
    }
}