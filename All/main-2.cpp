//
//  main.cpp
//  FB
//
//  Created by Daniil G on 15/01/2019.
//  Copyright © 2019 Daniil Golubyatnikov. All rights reserved.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define INF 10000

using namespace std;

 struct edge {
    int v, u, cost;
 };

int main(){
    
    typedef vector<vector<int>> MatrixInt;
    
    MatrixInt matrix
    {
        {0,INF,INF,1,6},
        {INF, 0, 1, INF, INF},
        {INF, 1, 0, 2, INF},
        {1, INF, 2, 0, 3},
        {6, INF, INF, 3, 0}
    };

    
    MatrixInt tmp(matrix.size());
    
    for (size_t i = 0; i < matrix.size(); ++i){
        for (size_t j = 0; j < matrix[i].size(); ++j){
            tmp[i].push_back(matrix[i][j]);
        }
    }
    //выводо матрицы
    for (int i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < tmp.size(); j++) {
            if (tmp[i][j] == 10000) {
                cout << "INF" << "\t";
            } else {
                 cout << tmp[i][j] << "\t";
            }
        } cout << endl;
    } cout << endl;
    
    vector<edge> e;
    edge t;
    int m = 0;
    for (size_t i = 0; i < matrix.size()-1; ++i){
        for (size_t j = 0; j < matrix[i].size(); ++j){
            if((matrix[i][j]) > 0 && (matrix[i][j]) != 10000){
                m++;
                t.v= i; t.u = j; t.cost = matrix[i][j];
                e.push_back(t);
                //cout << t.v << " " << t.u << " " << t.cost << endl;
            }
        }
    }
    int s = 0;
    vector<int> d(matrix.size(), INF);
    d[s] = 0;
    
    for (int i = 0; i < matrix.size()-1; i++){
        for (int j = 0; j < m; j++){
           // cout << e[j].v << " " << d[e[j].v] << " " << e[j].cost << " " << d[e[j].u] << " " << e[j].u << endl;
            if (d[e[j].v]+e[j].cost < d[e[j].u]){
                //cout << e[j].v << " " << d[e[j].v] << " " << e[j].cost << " " << d[e[j].u] << " " << e[j].u << endl;
                d[e[j].u]=d[e[j].v]+e[j].cost;
            }
        }
        cout << "Проход номер: " << i+1 << endl;
        for (int i = 0; i < matrix.size(); ++i){
            if (d[i] != INF){
                cout << "Из " << s << " в " << i  << " -> " << d[i] << endl;
            } else {
                cout << "Из " << s << " в " << i << ": NO" << endl;
            }
        } cout << endl;
    }
   
    return 0;
    
}
