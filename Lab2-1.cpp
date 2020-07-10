//============================================================================
// Name        : Lab2-2.cpp
// Author      : Derek Bomboy
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm>
#include <iostream> 
#include <time.h>
#include <vector>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations

double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() { amount = 0.0; } }; 
//============================================================================ // Static methods used for testing //============================================================================ 
/**
 * Display the bid information
 * @param bid struct containing the bid info
 **/

void displayBid(Bid bid) {
    cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */

  Bid getBid(){
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {	    
    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);
    Bid tempBid;
    vector <Bid> bidCol(file.rowCount());
	// loop to read rows of a CSV file
    for (int i = 0; i < file.rowCount(); i++) {
      csv::Row row= file.getRow(i); 
        for(unsigned int j = 0; j < file.columnCount(); j++){
          if(j == 0){tempBid.title = row[j];}
          else if(j==4){tempBid.amount = strToDouble(row[j], '$');}
          else if(j==8){tempBid.fund = row[j];}
          if(j==file.columnCount()-1){
            bidCol.at(i) = tempBid;
          }
        }
    }
    cout << file.rowCount() << " bids read"<< endl;
    return bidCol;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    vector <Bid> savedBids(0);

    clock_t begin_time;
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        	cout << "Not currently implemented." << endl;

            break;
        case 2:
            begin_time = clock();
            savedBids = loadBids(csvPath);

            cout << "time: " << float(clock()-begin_time)/CLOCKS_PER_SEC * 1000 << " milliseconds" << endl;
            cout << "time: " << float(clock()-begin_time)/CLOCKS_PER_SEC << " seconds" << endl;
            break;
        case 3:
           for (int i = 0; i < savedBids.size(); ++i) {
              displayBid(savedBids.at(i));
           }
            cout << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
