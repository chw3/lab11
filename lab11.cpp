#include <fstream>
#include "lab11.h"


int loadWidgets(ifstream& data, widget* &widgetArray,int& arraySize){
    int count = 0;
    while(!data.fail()){
        if (arraySize == count){
        data >> widgetArray[count].name;
        data >> widgetArray[count].quantity;
        data >> widgetArray[count].cost;
        count++;
		}
    }
    if (count < arraySize){
        count--;
	}
    return count;
}

void widgetManager( string input, string output ){
    ifstream in(input);
    ofstream out(output);
    string command;
    int count = 0;
    widget* widgetArray = new widget[10];
    int arraySize = 10;
    string datafile;
    in >> command;
    if (command == "load"){
        in >> datafile;
        ifstream data(datafile);
        out << "Command: " << command << " " << datafile << endl;
        count = loadWidgets(data, widgetArray, arraySize);
        out << "\tLoaded: " << count << endl;
    }
    while (!in.fail()){
        if (command == "showMeTheWidget"){
            int index;
            in >> index;
            out << "Command: " << command << " " << index << endl;
            if (index > -1 && index < count && !widgetArray[0].name.empty()){
                out << "\tName: " << widgetArray[index].name << endl;
                out << "\tQuantity: " << widgetArray[index].quantity << endl;
                out << "\tCost: $" << widgetArray[index].cost << endl;
            } else {
                out << "\tSorry, bad widget number " << index << endl;
            }
        }
        in >> command;
    }
    delete [] widgetArray;
}