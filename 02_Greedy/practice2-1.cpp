#include <iostream>
#include <vector>

struct Activity {
    int index;
    int startTime;
    int endTime;
};

std::vector<Activity> greedyActivitySelector(std::vector<Activity> activityList) {
    std::vector<Activity> result;
    result.push_back(activityList[0]);
    Activity lastAttendedActivity = activityList[0];
    for (int i = 1; i < activityList.size(); i++) {
        if (activityList[i].startTime >= lastAttendedActivity.endTime) {
            result.push_back(activityList[i]);
            lastAttendedActivity = activityList[i];
        }
    }
    return result;
}

int main() {
    std::vector<Activity> activityList;
    int inputIndex, inputStart, inputEnd;
    while (std::cin >> inputIndex >> inputStart >> inputEnd) {
        activityList.push_back({inputIndex, inputStart, inputEnd});
    }
    std::vector<Activity> attendedActivityList = greedyActivitySelector(activityList);
    for (int i = 0; i < attendedActivityList.size(); i++) {
        std::cout << attendedActivityList[i].index;
        std::cout << " ";
    }
    std::cout << std::endl;
}