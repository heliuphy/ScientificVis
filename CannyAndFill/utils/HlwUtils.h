//
// Created by 何柳 on 2020/3/15.
//

#ifndef MYPROJ_HLWUTILS_H
#define MYPROJ_HLWUTILS_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template <class T>
void printArray(T* array, int size, string arrayName) {
    cout << arrayName << " : " << endl;
    for (int i = 0; i< size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

#endif //MYPROJ_HLWUTILS_H
