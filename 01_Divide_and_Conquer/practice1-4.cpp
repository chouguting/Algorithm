/**
 * Practice1-4 The_Stern-Brocot_Number_System
 * */
#include <iostream>
struct Fraction{
    double numerator; //分子
    double denominator; //分母
};

void findFraction(Fraction target,Fraction left,Fraction current,Fraction right){
    if(target.numerator/target.denominator>current.numerator/current.denominator){
        std::cout<<"R";
        findFraction(target,current,{current.numerator+right.numerator,current.denominator+right.denominator},right);
    } else if(target.numerator/target.denominator<current.numerator/current.denominator){
        std::cout<<"L";
        findFraction(target,left,{current.numerator+left.numerator,current.denominator+left.denominator},current);
    } else{
        return;
    }
}

int main(){
    double numerator,denominator;
    while (true){
        std::cin>>numerator>>denominator;
        if(numerator==denominator&&numerator==1){
            break;
        }
        findFraction({numerator,denominator},
                     {0,1},
                     {1,1},
                     {1,0});
        std::cout<<std::endl;
    }
}