#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc , char* argv[] ){

    int n = argc-1;
    float sum , avg;

    if(argc == 1){
        cout<<"Please input numbers to find average."; 
    }else{

        for(int i =  0; i <= n ; i++){
            sum += atoi(argv[i]);
        }
        avg = sum/n;
        cout<<"---------------------------------"<<endl;
    
        cout<<"Average of " << n << " numbers = "<< avg <<endl;

        cout<<"---------------------------------";

    }

}

