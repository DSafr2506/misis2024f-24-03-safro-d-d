#include<iostream>
int main(){
    int b;
    std::cin>>b;
    for (int i=0;i<b;i++){
        int g,h,j;
        std::cin>>g>>h>>j;
        std::cout<<(((abs(g-h)+2*j-1)/(2*j)))<<std::endl;
    }
}
