#include <iostream>

using namespace std;

#ifndef LAB11_LAB11_H
#define LAB11_LAB11_H

struct widget {
    string name;
    int quantity;
    double cost;
} ;
#endif //LAB11_LAB11_H

void widgetManager( string input, string output );
int loadWidgets(ifstream& data,widget* &widgetArray,int& arraySize);

