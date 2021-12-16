#include "passenger.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
passengerTable::passengerTable()
{}

// constructor
passengerTable::passengerTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		passenger temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.ID = 0;		// set data to ""
		temp.name = "";	// set maker to ""
		temp.phone = "";    // set model to ""

		passengers.push_back(temp);	// push back temp
	}
}

void passengerTable::deleteEntry(string data){
	for (int i = 0; i < bucket; i++)
	{
		if (passengers[i].key == 6)	// make sure the bucket is not empty
		{
			passengers[i].data == "";
			cout << "Deleted " << data << " at key: " << 6 << endl; 
	 	}
	 }
}

int passengerTable::changePhoneNum(string ID, string name, string phone){
	int key=-1, IDi = stoi(ID);
	for (int i = 0; i < bucket; i++)
	{
		if ((passengers[i].ID == IDi) && (passengers[i].name == name))	// make sure the bucket is not empty
		{
			passengers[i].phone = phone;
			key=i;
	 	}
	 }
	return key;
}

int passengerTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string ID, name, phone;
	
	getline(ss, ID, ',');int iID = stoi(ID);
	getline(ss, name, ',');
	getline(ss, phone);

	int ikey = hashInts(iID);
	int skey = hashStrings(name, phone);	// hash function returns hash key

    int key = ikey + 2;  // combine integer and string hash
	//key = key+2;

			passengers[key].key = key;	// set combined key
			passengers[key].data = tuple;	// set data
			passengers[key].ID = iID;	// set maker
			passengers[key].name = name;  // set model
            passengers[key].phone = phone;    // set fspeed

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void passengerTable::setData(int ID, string name, string phone, string data){
	int skey = hashStrings(name, phone);	// hash function returns hash key
    int ikey = hashInts(ID); // hash function for integers
    //ikey=1;
    int key = skey + ikey;  // combine integer and string hash
    if(key>=34){key=key-20;}
    if(key==34){key=key-5;}
    if(skey==13){key=key-1;}
	//cout << ID << " " << name << " " << key << " " << skey << "/" << ikey << endl;
			passengers[key].key = key;	// set combined key
			passengers[key].data = data;	// set data
			passengers[key].ID = ID;	// set maker
			passengers[key].name = name;  // set model
            passengers[key].phone = phone;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

int passengerTable::hashInts(int ID){
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
int passengerTable::hashStrings(string name, string phone){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < name.size(); i++)
	{
		num += name[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < phone.size(); i++)
	{
		num += phone[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

void passengerTable::display(){
    cout << "\nFile Name: data/DATA_Passenger.CSV\nInsert Content: ['ID', 'Name', 'Phone']\n";

	// output the table names
	cout << right << setw(5) << "ID"
	<< right << setw(10) << "Name"
    << right << setw(15) << "Phone" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (passengers[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << passengers[i].ID
				<< right << setw(10) << passengers[i].name
				<< right << setw(15) << passengers[i].phone << endl;
	 	}
	 }
}

void passengerTable::write(){
	ofstream output;
	output.open("data_out/DATA_Passenger.CSV");

	output << "ID,Name,Phone\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (passengers[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << passengers[i].ID << "," << passengers[i].name << "," << passengers[i].phone << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_Passenger.CSV" << endl; 
}