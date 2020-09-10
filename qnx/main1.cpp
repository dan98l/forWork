#include <iostream>
#include <zconf.h>

using namespace std;

int main() {
    srand(time(NULL));
    int arr[5000];
    int j = 0;
    cout << fork();
    while (1) {
        cin >> j;
        if (j > 0) {
            arr[j] = rand() % 5000 + 100;
        } else {
            exit(-3);
        }
    }
}