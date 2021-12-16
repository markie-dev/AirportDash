#include "flightTable.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
flightTable::flightTable()
{}

// constructor
flightTable::flightTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		flight temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.FLNO = "";		// set data to ""
		temp.meal = "";	// set maker to ""
		temp.smoking = "";    // set model to ""

		flights.push_back(temp);	// push back temp
	}
}

int flightTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (flights[i].data == data)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

void flightTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (flights[i].key == key)	// make sure the bucket is not empty
		{
			flights[i].data == "";
	 	}
	 }
}

int flightTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string FLNO, meal, smoking;	

	getline(ss, FLNO, ',');	// parse tuple to get id
	getline(ss, meal, ',');
	getline(ss, smoking);

	int skey = hashStrings(FLNO, meal, smoking);	// hash function returns hash key

    int key = skey;  // combine integer and string hash
	//key = key+2;
	
	flights[key].key = key;	// set combined key
	flights[key].data = tuple;	// set data
	flights[key].FLNO = FLNO;	// set maker
	flights[key].meal = meal;  // set model
	flights[key].smoking = smoking;

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void flightTable::setData(string FLNO, string meal, string smoking, string data){
	int skey = hashStrings(FLNO, meal, smoking);	// hash function returns hash key
    int key = skey;  // combine integer and string hash
			flights[key].key = key;	// set combined key
			flights[key].data = data;	// set data
			flights[key].FLNO = FLNO;	// set maker
			flights[key].meal = meal;  // set model
            flights[key].smoking = smoking;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}



// addititve string hash function
int flightTable::hashStrings(string FLNO, string meal, string smoking){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < FLNO.size(); i++)
	{
		num += FLNO[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < meal.size(); i++)
	{
		num += meal[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < smoking.size(); i++)
	{
		num += smoking[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}


bool flightTable::find(string FLNO, string meal, string smoking){
	bool ans = true;
	int searchKey = hashStrings(FLNO, meal, smoking);

	if (flights[searchKey].FLNO == "") {
		ans = false;
	}

	// cout << "Search KEY: " << searchKey << endl;
	// cout << "KEY: " << flightLegs[3].key << endl;

	return ans;
}

void flightTable::display(){
    cout << "\nFile Name: data/DATA_Flight.CSV\nInsert Content: ['FLNO', 'Meal', 'Smoking']\n";

	// output the table names
	cout << right << setw(10) << "FLNO"
    << right << setw(10) << "Meal" 
    << right << setw(15) << "Smoking" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flights[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(10) << flights[i].FLNO
				<< right << setw(10) << flights[i].meal
				<< right << setw(15) << flights[i].smoking << endl;
	 	}
	 }
}

void flightTable::write(){
	ofstream output;
	output.open("data_out/DATA_Flight.CSV");

	output << "FLNO,Meal,Smoking\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flights[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << flights[i].FLNO << "," << flights[i].meal << "," << flights[i].smoking << endl;
	 	}
	 }

	cout << "Wrote table to data_out/DATA_Flight.CSV" << endl; 
}