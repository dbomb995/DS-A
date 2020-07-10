//============================================================================
// Name        : Lab1-3.cpp
// Author      : Derek Bomboy
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 1-3 Up to Speed in C++
//============================================================================

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

	struct bidInfo {
		string title;
		string fund;
		string vehicleID;
		double amount;
};

void displayBid(bidInfo bidInfoDisplay) {
    cout << "Title:" << bidInfoDisplay.title << endl;
    cout << "Fund: " << bidInfoDisplay.fund << endl;
    cout << "Vehicle: " << bidInfoDisplay.vehicleID << endl;
    cout << "Bid Amount: " << bidInfoDisplay.amount << endl;

    return;
}

/*
 * Simple C function to convert a string to a double
 * after stripping out unwanted chars
 */

double strToDoubles(string str, char ch){
	string temp;
	string numbers = "0123456789";
	for(unsigned int i = 0; i < str.length(); i++){
		if(str[i] == '.' && i == str.length() - 3){break;}
		else if (numbers.find(str[i]) == string::npos){continue;}
		else {temp = temp + str[i];}
	}
	return atof(temp.c_str());
}

/*
 * Prompt user for bid information
 * @return data structure containing the bid info
 */

bidInfo getBid() {
    bidInfo bidInfo1;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, bidInfo1.title);

    cout << "Enter fund: ";
    cin >> bidInfo1.fund;

    cout << "Enter vehicle: ";
    cin.ignore();
    getline(cin, bidInfo1.vehicleID);

    cout << "Enter amount: ";
    string strAmount;
    getline(cin, strAmount);
    bidInfo1.amount = strToDoubles(strAmount, '$');

    return bidInfo1;
}


//The one and only main() method

int main() {

	bidInfo bidInfo1;

    // loop to display menu until exit chosen
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter Bid" << endl;
        cout << "  2. Display Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
           case 1:
            	bidInfo1 = getBid();
                break;
            case 2:
                displayBid(bidInfo1);
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
