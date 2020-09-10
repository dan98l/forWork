//
//  main.cpp
//  fordB
//
//  Created by Daniil G on 12/01/2019.
//  Copyright © 2019 Daniil Golubyatnikov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct backPackItem {
    int cost;
    int mass;
};

int main () {
    
    int M = 0, k = 0; // M - max вместимость рюкзака (масса);  k - кол-во доступных элементов;
    
    vector <backPackItem> item;
    ifstream fin("/Users/daniil/Desktop/input.txt");
    
    fin >> M >> k; // считываем М - max вместимость рюкзака и кол-во предметов;
    
    for (int i = 0; i < k; i++){ // считываем построчно и заполняем вектор item;
        backPackItem newItem;
        fin >> newItem.mass;
        fin >> newItem.cost;
        item.push_back(newItem);
    }
    
    //сортируем элементы по стоимости
    for(int i = k - 1; i >= 0; i--){
        int maxIndex = 0;
        
        for(int j = 0; j <= i; j++){
           // cout << item[j].cost << "\t" << item[maxIndex].cost << endl;
            if(item[j].cost > item[maxIndex].cost){
                maxIndex = j;
            }
        }
        if(maxIndex != i){
            backPackItem temp = item[maxIndex];
            item[maxIndex] = item[i];
            item[i] = temp;
        }
    }
    
    vector<int> f;
    
    for (int i = 0; i < M; i++) {
        if (i < item[0].mass) {
            f.push_back(0);
        } else break;
    }
    
    vector<int> tempF;
    
    for (size_t i = f.size(); i <= M; i++) {
        for (int kk = 0; kk < k; kk++) {
            int temp = i - item[kk].mass;
            if (temp < 0) tempF.push_back(-1);
            else tempF.push_back(f[i - item[kk].mass] + item[kk].cost);
        }
        sort(tempF.begin(), tempF.end(), greater<int>());
       // cout << tempF[0] << endl;
        f.push_back(tempF[0]);
        tempF.clear();
    }
    
    // наполняем рюкзак
    vector<int> backpack;
    
    vector<backPackItem> stoumosti;
    
    int lessW = f[f.size()-1];
    cout << "В рюкзаке лежат предметы: " << endl;
    
    bool flag = false;
    
    for (int i = 0; i < item.size(); i++) {
        int a = lessW, b = item[i].cost;
        while( a > 0 && (a-=b) );
        if( a == 0 ){
            flag = true;
            for (int j = 0; j < lessW; j++) {
                lessW -= item[i].cost;
                stoumosti.push_back(item[i]);
                //cout << "Вес: " << item[i].mass << "\t" << " Стоимость: "  << item[i].cost << endl;
                //stoumosti[i] = stoumosti[i] + 1;
            }
        }
    }
    
    if (!flag) {
        while (lessW != 0) {
            for (int j = item.size()-1; j >= 0; j--){
                if (lessW - item[j].cost >= 0) {
                    backpack.push_back(item[j].cost);
                    lessW -= item[j].cost;
                     stoumosti.push_back(item[j]);
                    //cout << "Вес: " << item[j].mass << "\t" << " Стоимость: "  << item[j].cost << endl;
                }
            }
        }
       
    }
    
    cout << "Общая стоимость: " << f[f.size()-1] << endl;
    
    //sort(stoumosti.mass.begin(), stoumosti.mass.end());
    
    vector<int> TTemp(k,0);
    int rt = 0;
    
    for (int i  = 0; i < item.size(); i++) {
        for (int j = 0; j < stoumosti.size(); j++) {
            //cout << item[i].mass << " " << stoumosti[j].mass << endl;
            if (item[i].mass == stoumosti[j].mass ){
                TTemp[i] =  TTemp[i] + 1;
            }
        }
    }
    
//    for (int i  = 0; i < TTemp.size(); i++) {
//        cout << TTemp[i] << "\t";
//    } cout << endl;
    
    for (int i  = 0; i < item.size(); i++) {
        cout << "Берётся - " << TTemp[i] << " раз. " << "Вес: " << item[i].mass << "\t" << " Стоимость: "  << item[i].cost << endl;
    }
 
    return 0;
}
