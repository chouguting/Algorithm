/**
 * 6-1: Longest Increasing Subsequence
 */
#include <iostream>
#include <vector>

using namespace std;

int LTS(vector<int> &theList) {
    vector<int> logger;
    if(theList.size()==0)return 0;
    logger.push_back(theList[0]);
    for (int i = 1; i < theList.size(); i++) {
        int theNum=theList[i];
        if(theNum>logger[logger.size()-1]){
            logger.push_back(theNum);
        }else{
            *lower_bound(logger.begin(), logger.end(),theNum) = theNum; //和下面那個註解做同樣的事
        }
        /*for(int j=0;j<logger.size();j++){
            if(theList[i]<=logger[j]){
                logger[j]=theList[i];
                break;
            }
        }*/
    }
    return logger.size();
}

int main() {
    vector<int> theList;
    int input;
    int length;
    cin >> length;
    for (int i = 0; i < length; i++) {
        cin >> input;
        if (input == -1)break;
        theList.push_back(input);
    }
    cout << LTS(theList) << endl;
}