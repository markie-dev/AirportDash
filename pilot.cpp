#include "pilot.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
pilotTable::pilotTable()
{}

// constructor
pilotTable::pilotTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		pilot temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.ID = 0;		// set data to ""
		temp.name = "";	// set maker to ""
		temp.datehired = "";    // set model to ""

		pilots.push_back(temp);	// push back temp
	}
}

int pilotTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (pilots[i].data == data)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

void pilotTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (pilots[i].key == key)	// make sure the bucket is not empty
		{
			pilots[i].data = "";
	 	}
	 }
}

int pilotTable::changeNamebyID(int ID, string name){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (pilots[i].ID == ID)	// make sure the bucket is not empty
		{
			pilots[i].name = name;
			key=i;
	 	}
	 }
	return key;
}

int pilotTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string ID, name, datehired;

	getline(ss, ID, ',');int iID = stoi(ID);	// parse tuple to get id
	getline(ss, name, ',');
	getline(ss, datehired);

	int ikey = hashInts(iID);
	int skey = hashStrings(name, datehired);	// hash function returns hash key

    int key = skey + ikey + 1;  // combine integer and string hash
	//key = key+2;

			pilots[key].key = key;	// set combined key
			pilots[key].data = tuple;	// set data
			pilots[key].ID = iID;	// set maker
			pilots[key].name = name;  // set model
            pilots[key].datehired = datehired;    // set fspeed

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void pilotTable::setData(int ID, string name, string datehired, string data){
	int skey = hashStrings(name, datehired);	// hash function returns hash key
    int ikey = hashInts(ID); // hash function for integers
    if (ikey>=16){ikey=3;}
    int key = skey + ikey;  // combine integer and string hash
			pilots[key].key = key;	// set combined key
			pilots[key].data = data;	// set data
			pilots[key].ID = ID;	// set maker
			pilots[key].name = name;  // set model
            pilots[key].datehired = datehired;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

int pilotTable::hashInts(int ID){
	// square speed
	ID = ID * ID;
	string l = to_string(ID);	// convert speed to str
	int length = l.length();	// get length of str
	
	string r;	// create new str to get middle digits
	// get middle digits of str depending on 
	// number of digits
	if (length == 1)
	{
		r = l;
	}
	if (length == 2)
	{
		r = l;
	}
	if (length == 3)
	{
		r = l.substr(1, 1);
	}
	if (length == 4)
	{
		r = l.substr(1, 2);
	}
	if (length == 5)
	{
		r = l.substr(1, 2);
	}
	if (length == 6)
	{
		r = l.substr(2, 3);
	}
	// convert back to int
	int R = stoi(r);

	// perform mod operation to get key
	int key = R % bucket;
    //cout << key << endl;
	return key;		// return key
}

// addititve string hash function
int pilotTable::hashStrings(string name, string datehired){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < name.size(); i++)
	{
		num += name[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < datehired.size(); i++)
	{
		num += datehired[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

void pilotTable::display(){
    cout << "\nFile Name: data/DATA_Pilot.CSV\nInsert Content: ['ID', 'Name', 'DateHired']\n";

	// output the table names
	cout << right << setw(5) << "ID"
    << right << setw(10) << "Name" 
    << right << setw(10) << "DateHired" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (pilots[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << pilots[i].ID
				<< right << setw(10) << pilots[i].name
				<< right << setw(10) << pilots[i].datehired << endl;
	 	}
	 }
}

void pilotTable::selectDisplay(string name){
    cout << "\nSELECT((*.*),Pilot),Jones)\n";

	// output the table names
	cout << right << setw(5) << "ID"
    << right << setw(10) << "Name" 
    << right << setw(10) << "DateHired" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if ((pilots[i].data != "") && (pilots[i].name == name))	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << pilots[i].ID
				<< right << setw(10) << pilots[i].name
				<< right << setw(10) << pilots[i].datehired << endl;
	 	}
	 }
}

void pilotTable::write(){
	ofstream output;
	output.open("data_out/DATA_Pilot.CSV");

	output << "ID,Name,DateHired\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (pilots[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << pilots[i].ID << "," << pilots[i].name << "," << pilots[i].datehired << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_Pilot.CSV" << endl; 
}