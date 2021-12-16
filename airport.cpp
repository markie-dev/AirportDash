#include "airport.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
airportTable::airportTable()
{}

// constructor
airportTable::airportTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		airport temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.code = "";		// set data to ""
		temp.city = "";	// set maker to ""
		temp.state = "";    // set model to ""

		airports.push_back(temp);	// push back temp
	}
}

int airportTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (airports[i].data == data)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

void airportTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (airports[i].key == key)	// make sure the bucket is not empty
		{
			airports[i].data = "";
	 	}
	 }
}

int airportTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string code, city, state;

	getline(ss, code, ',');	// parse tuple to get id
	getline(ss, city, ',');
	getline(ss, state);

	int skey = hashStrings(code, city, state);	// hash function returns hash key

    int key = skey;  // combine integer and string hash
	//key = key+2;
	
			airports[key].key = key;	// set combined key
			airports[key].data = tuple;	// set data
			airports[key].code = code;	// set maker
			airports[key].city = city;  // set model
            airports[key].state = state;    // set fspeed

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void airportTable::setData(string code, string city, string state, string data){
	int skey = hashStrings(code, city, state);	// hash function returns hash key
    int key = skey;  // combine integer and string hash
			airports[key].key = key;	// set combined key
			airports[key].data = data;	// set data
			airports[key].code = code;	// set maker
			airports[key].city = city;  // set model
            airports[key].state = state;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}



// addititve string hash function
int airportTable::hashStrings(string code, string city, string state){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < code.size(); i++)
	{
		num += code[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < city.size(); i++)
	{
		num += city[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < state.size(); i++)
	{
		num += state[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

bool airportTable::find(string code, string city, string state){
	bool ans = true;
	int searchKey = hashStrings(code, city, state);

	if (airports[searchKey].code == "") {
		ans = false;
	}

	// cout << "Search KEY: " << searchKey << endl;
	// cout << "KEY: " << flightLegs[3].key << endl;

	return ans;
}

void airportTable::display(){
    cout << "\nFile Name: data/DATA_AirPort.CSV\nInsert Content: ['Code', 'City', 'State']\n";

	// output the table names
	cout << right << setw(5) << "Code"
    << right << setw(15) << "City" 
    << right << setw(10) << "State" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (airports[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << airports[i].code
				<< right << setw(15) << airports[i].city
				<< right << setw(10) << airports[i].state << endl;
	 	}
	 }
}

void airportTable::write(){
	ofstream output;
	output.open("data_out/DATA_AirPort.CSV");

	output << "Code,City,State\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (airports[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << airports[i].code << "," << airports[i].city << "," << airports[i].state << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_AirPort.CSV" << endl; 
}