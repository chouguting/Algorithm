/**
 * Practice1-3 Dropping_Balls
 * */
#include <iostream>
int nodeToLeave(int currentPlace,int depthLeft,int ballCount){
    if(depthLeft==1) return currentPlace;
    if(ballCount%2==1){
        return nodeToLeave(currentPlace*2,depthLeft-1,ballCount/2+1);
    }else{
        return nodeToLeave(currentPlace*2+1,depthLeft-1,ballCount/2);
    }
}

 int main(){
     int times;
     std::cin>>times;
     for(int t=0;t<times;t++){
        int depth,ballsCount;
        std::cin>>depth>>ballsCount;
        std::cout<<nodeToLeave(1,depth,ballsCount);
        std::cout<<std::endl;
     }
     std::cin>>times;
 }