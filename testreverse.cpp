#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <stack>
#include <algorithm>

using namespace std;


int main(){
    vector<int> numbers {0,1,2,3,4,5,6,7,8};

    cout << "before" << endl;
    for(int i = 0; i < numbers.size(); i++){
        cout << numbers[i]  << endl;
    }

    reverse(numbers.begin() + 1, numbers.begin() + 4);
    
    cout << "after" << endl;

    for(int i = 0; i < numbers.size(); i++){
        cout << numbers[i]  << endl;
    }


    return 0;
}