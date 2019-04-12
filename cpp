#include <fstream>
#include <iostream>
#include <sstream>

#include "lab11.h"

const int ARR_SIZE = 10;

int ReadDataFile(string file_name, widget arr[]) {
	// open data file
	ifstream data_file;
	string line;
	data_file.open(file_name);
	// loop for max size
	int load_count = 0;
	for (int i = 0; i < ARR_SIZE; ++i) {
		// read line by line
		if (getline(data_file, line)) {	// IF line is there
			// iterate over line, deliminating by [space] char
			stringstream iss(line);
			string value[3];
			int j = 0;
			while (getline(iss, value[j++], ' '))
				;
			// read data into arr index i
			arr[i].name = value[0];	
			arr[i].quantity = stoi(value[1]);	// CONVERT to INT
			arr[i].cost = stof(value[2]);		// CONVERT to FLOAT (DOUBLE)
		}
		else {
			load_count = i;
			break;	// break the loop
		}
	}
	data_file.close();	// close file
	return  load_count;
}

void widgetManager(string input, string output) {
	ifstream cmd_file;
	cmd_file.open(input);
	string line;
	bool readDF = false;
	bool readIND = false;
	widget widget_array[ARR_SIZE];
	string command;
	string data_file_name;
	string strIndex;
	int load_count = 0;

 	while (getline(cmd_file, line)) {
		for (char c : line) {
			if (c == ' ') {
				if (command == "load") {
					output += "Command: " + line + '\n';
					readDF = true;
					command = "";
					continue;
				}
				readIND = true;
				command = "";
				continue;
			}
			if (readDF) {
				data_file_name += c;
			}
			else if (readIND) {
				strIndex += c;
			}
			else {
				command += c;
			}
		}
		if (readDF) {
			load_count = ReadDataFile(data_file_name, widget_array);
			output += "\tLoaded " + std::to_string(load_count) + '\n';
			readDF = false;
		}
		if (readIND) {
			int index = stoi(strIndex);
			strIndex = "";
			if (index < 0 || index > load_count - 1) {
				output += "Command: " + line + "\n\tSorry, bad widget number " + std::to_string(index)+ '\n';
			}
			else {
				output += "Command " + line +  '\n' + widget_array[index].displayWidget();
			}
			readIND = false;
		}
	}
	cout << output;
}

int main() {
	widgetManager("command.txt", "");
}
