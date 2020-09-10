//
//  main.cpp
//  NSTU 3
//
//  Created by Daniil G on 28.03.2018.
//  Copyright © 2018 Daniil G. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <algorithm>


using namespace std;

int main() {
    
    vector <int> vec;
    
    int n = 0;
    
    cin >> n;
    
    int c;
    
    for (int i = 0; i < n; i++) {
        cin >> c;
        vec.push_back(c);
    }
    
    /*for (int i = 0; i < n; i++) {
        cout << vec[i] << "\t";
    }*/ //cout << endl;
    
    //sort_heap(vec.begin(), vec.end());
    
    sort(vec.begin(), vec.end(), greater<int>());
    reverse (vec.begin( ), vec.end( ) );
    
    vector <int> repidVector;
    
    /*for (int i = 0; i < n; i++) {
        cout << vec[i] << "\t";
    } cout << endl;
*/
    
    for (int i = 0; i < vec.size(); i++) {
        
        auto pos = binary_search(begin(repidVector), end(repidVector), vec[i]);
        
        if (!pos) {
            
            repidVector.push_back(vec[i]);
        }
        
    }// cout << endl <<   "run" <<endl;
    
    
    /*for (int i = 0; i < repidVector.size(); i++) {
        cout << repidVector[i] << "\t";
    } cout << endl;
    */
    vector<int> endVector(repidVector.size(),0);
    
    for (int i = 0; i <  repidVector.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (repidVector[i] == vec[j]) {
                endVector[i] = endVector[i] + 1;;
            }
        }
    }
    
    sort(endVector.begin(), endVector.end(), greater<int>());
    
    /*for (int i = 0; i < repidVector.size(); i++) {
        cout << endVector[i] << "\t";
    } cout << endl;
    */
    
    
    int sum = 0;
    
    for (int i = endVector.size()-1; i > 0; i--) {
        sum = sum + (endVector[0] - endVector[i]);
    }
    
    cout << sum;
    return 0;
}
