/**
 * 4_3_The_Hamming_Distance_Problem
 */
#include <iostream>
#include <vector>
using namespace std;

void makeAllSequence(int length,string numberData,int numberOfOneLeft){
    if(numberData.size()==length){
        if(numberOfOneLeft==0)
        cout<<numberData<<endl;
        return;
    }
    string zeroAndSequence=numberData;
    zeroAndSequence+="0";
    makeAllSequence(length,zeroAndSequence,numberOfOneLeft);
    if(numberOfOneLeft>0){
        string oneAndSequence=numberData;
        oneAndSequence+="1";
        makeAllSequence(length,oneAndSequence,numberOfOneLeft-1);
    }
}

void makeAllSequence(int length ,int numberOfOneLeft){
    string  sequenceStr1="0";
    makeAllSequence(length,sequenceStr1,numberOfOneLeft);
    if(numberOfOneLeft>0){
        string  sequenceStr2="1";
        makeAllSequence(length,sequenceStr2,numberOfOneLeft-1);
    }
}

int main(){
    int times;
    cin>>times;
    for(int t=0;t<times;t++){
        if(t!=0) cout<<endl;
        vector<bool> numberData;
        int length,numberOfOnes;
        cin>>length>>numberOfOnes;
        makeAllSequence(length,numberOfOnes);
    }
}