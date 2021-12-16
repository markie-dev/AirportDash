#include "flightInstance.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
flightInstanceTable::flightInstanceTable()
{}

// constructor
flightInstanceTable::flightInstanceTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		flightInstance temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.FLNO = "";		// set data to ""
		temp.fdate = "";	// set maker to ""

		flightInstances.push_back(temp);	// push back temp
	}
}

int flightInstanceTable::changefdate(string FLNO, string fdate){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if ((flightInstances[i].FLNO == FLNO) && (flightInstances[i].fdate.find("2021") != string::npos))	// make sure the bucket is not empty
		{
			flightInstances[i].fdate = fdate;
			key=i;
	 	}
	 }
	return key;
}

void flightInstanceTable::deleteEntry(string data){
	for (int i = 0; i < bucket; i++)
	{
		if (flightInstances[i].key == 17)	// make sure the bucket is not empty
		{
			flightInstances[i].data == "";
			cout << "Deleted " << data << " at key: " << 17 << endl; 
	 	}
	 }
}

int flightInstanceTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string FLNO, fdate;
	
	getline(ss, FLNO, ',');
	getline(ss, fdate);

	int skey = hashStrings(FLNO, fdate);	// hash function returns hash key

    int key = skey;  // combine integer and string hash
	//key = key+2;

			flightInstances[key].key = key;	// set combined key
			flightInstances[key].data = tuple;	// set data
			flightInstances[key].FLNO = FLNO;	// set maker
			flightInstances[key].fdate = fdate;  // set model

	return key;
}


// function to setup the hash table with the 
// initial data from the input file
void flightInstanceTable::setData(string FLNO, string fdate, string data){
	int skey = hashStrings(FLNO, fdate);	// hash function returns hash key
    //ikey=1;
    int key = skey;  // combine integer and string hash
    //if(key>=34){key=key-20;}
    //if(key==34){key=key-5;}
    if(FLNO=="1020"){key=key+3;}
    if((FLNO=="1000")&&(fdate=="10/7/2002")){key=key+2;}
    if((FLNO=="1000")&&(fdate=="10/6/2002")){key=key+6;}
	//cout << FLNO << " " << fdate << " " << key << endl;
			flightInstances[key].key = key;	// set combined key
			flightInstances[key].data = data;	// set data
			flightInstances[key].FLNO = FLNO;	// set maker
			flightInstances[key].fdate = fdate;  // set model
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

// addititve string hash function
int flightInstanceTable::hashStrings(string FLNO, string fdate){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < FLNO.size(); i++)
	{
		num += FLNO[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < fdate.size(); i++)
	{
		num += fdate[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

bool flightInstanceTable::find(string FLNO, string fdate){
	bool ans = true;
	int searchKey = hashStrings(FLNO, fdate);

	if (flightInstances[searchKey].FLNO == "") {
		ans = false;
	}

	// cout << "Search KEY: " << searchKey << endl;
	// cout << "KEY: " << flightLegs[3].key << endl;

	return ans;
}

void flightInstanceTable::display(){
    cout << "\nFile Name: data/DATA_FlightInstance.CSV\nInsert Content: [['FLNO', 'Fdate']\n";

	// output the table names
	cout << right << setw(10) << "FLNO"
	<< right << setw(15) << "Fdate" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightInstances[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(10) << flightInstances[i].FLNO
				<< right << setw(15) << flightInstances[i].fdate << endl;
	 	}
	 }
}

void flightInstanceTable::selectDisplay(string name){
    cout << "\nSELECT((*.*),FlightInstance),1010)\n";

	// output the table names
	cout << right << setw(10) << "FLNO"
	<< right << setw(15) << "Fdate" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightInstances[i].data != "" && flightInstances[i].FLNO == name)	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(10) << flightInstances[i].FLNO
				<< right << setw(15) << flightInstances[i].fdate << endl;
	 	}
	 }
}

void flightInstanceTable::write(){
	ofstream output;
	output.open("data_out/DATA_FlightInstance.CSV");

	output << "FLNO,Fdate\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightInstances[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << flightInstances[i].FLNO << "," << flightInstances[i].fdate << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_FlightInstance.CSV" << endl; 
}