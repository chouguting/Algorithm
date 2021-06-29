/**
* Snowman
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long int length;
    cin >> length;
    vector<long long int> snowmanStrength;
    vector<long long int> temperature;
    vector<long long int> temperatureAccumulate;

    for (long long int i = 0; i < length; i++) {
        long long int strength;
        cin >> strength;
        snowmanStrength.push_back(strength);
    }
    for (long long int i = 0; i < length; i++) {
        long long int temper;
        cin >> temper;
        temperature.push_back(temper);
        if (i == 0) {
            temperatureAccumulate.push_back(temper);
        } else {
            temperatureAccumulate.push_back(temper + temperatureAccumulate[i - 1]);
        }
    }

    for (int i = 0; i < snowmanStrength.size(); i++) {
        if (snowmanStrength[i] > temperatureAccumulate[temperatureAccumulate.size() - 1]) {
            cout << "-1";
        } else {
            auto lower = lower_bound(temperatureAccumulate.begin(), temperatureAccumulate.end(), snowmanStrength[i]);
            cout << lower - temperatureAccumulate.begin() + 1;
        }/*
        for(int j=0;j<temperatureAccumulate.size();j++){
            temperatureAccumulate[j]-=temperature[i];
        }*/
        snowmanStrength[i + 1] += temperatureAccumulate[i];
        cout << " ";
    }
    cout << endl;
}