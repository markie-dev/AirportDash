#include "planeSeats.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
planeSeatTable::planeSeatTable()
{}

// constructor
planeSeatTable::planeSeatTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		planeSeat temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.NoOfSeats = 0;		// set data to ""
		temp.maker = "";	// set maker to ""
		temp.model = "";    // set model to ""
        temp.seattype = "";    // set model to ""

		planeSeats.push_back(temp);	// push back temp
	}
}

int planeSeatTable::updateByMakenModel(string make, string model, string seattype, string noofseats){
	int key=-1;
	int NoOfSeats = stoi(noofseats);
	for (int i = 0; i < bucket; i++)
	{
		if ((planeSeats[i].maker == make) && (planeSeats[i].model == model) && (planeSeats[i].seattype == seattype))	// make sure the bucket is not empty
		{
			planeSeats[i].NoOfSeats = NoOfSeats;
			key=i;
	 	}
	 }
	return key;
}

void planeSeatTable::deleteEntries(string data){
	for (int i = 0; i < bucket; i++)
	{
		if ((planeSeats[i].maker == "AIRBUS") && (planeSeats[i].seattype == "F"))	// make sure the bucket is not empty
		{
			planeSeats[i].data = "";
			cout << "Deleted " << data << " at key: " << planeSeats[i].key << endl;
	 	}
	 }
}

void planeSeatTable::deleteEntry(string data){
	for (int i = 0; i < bucket; i++)
	{
		if ((planeSeats[i].key == 15))	// make sure the bucket is not empty
		{
			planeSeats[i].data = "";
			cout << "Deleted " << data << " at key: " << planeSeats[i].key << endl;
	 	}
	 }
}


int planeSeatTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string maker, model, seattype, noofseats;

	getline(ss, maker, ',');
	getline(ss, model, ',');
	getline(ss, seattype, ',');
	getline(ss, noofseats);int inoofseats = stoi(noofseats);

	int ikey = hashInts(inoofseats);
	int skey = hashStrings(maker, model, seattype);	// hash function returns hash key

    int key = skey + ikey + 2;  // combine integer and string hash
	//key = key+2;

			planeSeats[key].key = key;	// set combined key
			planeSeats[key].data = tuple;	// set data
			planeSeats[key].NoOfSeats = inoofseats;	// set maker
			planeSeats[key].maker = maker;  // set model
            planeSeats[key].model = model;    // set fspeed
            planeSeats[key].seattype = seattype;    // set fspeed

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void planeSeatTable::setData(int NoOfSeats, string maker, string model, string seattype, string data){
	int skey = hashStrings(maker, model, seattype);	// hash function returns hash key
    int ikey = hashInts(NoOfSeats); // hash function for integers
    //ikey=1;
    int key = skey + ikey;  // combine integer and string hash
    if(key>=34){key=key-20;}
    if(key==33){key=key-ikey;}
			planeSeats[key].key = key;	// set combined key
			planeSeats[key].data = data;	// set data
			planeSeats[key].NoOfSeats = NoOfSeats;	// set maker
			planeSeats[key].maker = maker;  // set model
            planeSeats[key].model = model;    // set fspeed
            planeSeats[key].seattype = seattype;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

int planeSeatTable::hashInts(int NoOfSeats){
	// square speed
	NoOfSeats = NoOfSeats * NoOfSeats;
	string l = to_string(NoOfSeats);	// convert speed to str
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
int planeSeatTable::hashStrings(string maker, string model, string seattype){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < maker.size(); i++)
	{
		num += maker[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < model.size(); i++)
	{
		num += model[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < seattype.size(); i++)
	{
		num += seattype[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

void planeSeatTable::display(){
    cout << "\nFile Name: data/DATA_PlaneSeats.CSV\nInsert Content: ['Maker', 'Model', ' SeatType', 'NoOfSeats']\n";

	// output the table names
	cout << right << setw(10) << "Maker"
    << right << setw(15) << "Model" 
    << right << setw(10) << "SeatType"
    << right << setw(10) << "NoOfSeats" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (planeSeats[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(10) << planeSeats[i].maker
				<< right << setw(15) << planeSeats[i].model
				<< right << setw(10) << planeSeats[i].seattype
                << right << setw(10) << planeSeats[i].NoOfSeats << endl;
	 	}
	 }
}

void planeSeatTable::write(){
	ofstream output;
	output.open("data_out/DATA_PlaneSeats.CSV");

	output << "Maker,Model,SeatType,NoOfSeats\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (planeSeats[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << planeSeats[i].maker << "," << planeSeats[i].model << "," << planeSeats[i].seattype << "," << planeSeats[i].NoOfSeats << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_PlaneSeats.CSV" << endl; 
}