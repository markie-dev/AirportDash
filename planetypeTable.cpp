#include "planetypeTable.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
planeTypeTable::planeTypeTable()
{}

// constructor
planeTypeTable::planeTypeTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		planeType temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";		// set data to ""
		temp.maker = "";	// set maker to ""
		temp.model = "";    // set model to ""
        temp.fspeed = 0;   // set fspeed to 0
        temp.gspeed = 0;    // set gspeed to 0

		planeTypes.push_back(temp);	// push back temp
	}
}

int planeTypeTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string maker, model, fspeed, gspeed;	

	getline(ss, maker, ',');	// parse tuple to get id
	getline(ss, model, ',');
	getline(ss, fspeed, ','); int fpseedI = stoi(fspeed);
	getline(ss, gspeed, ','); int gpseedI = stoi(gspeed);

	int skey = hashStrings(maker, model);	// hash function returns hash key
    int ikey = hashInts(fpseedI) * hashInts(gpseedI); // hash function for integers

	if(ikey>80){ikey=0;}
    int key = skey + ikey;  // combine integer and string hash
	key = key+2;
	
	planeTypes[key].key = key;	// set combined key
	planeTypes[key].data = tuple;	// set data
	planeTypes[key].maker = maker;	// set maker
	planeTypes[key].model = model;  // set model
    planeTypes[key].fspeed = fpseedI;    // set fspeed
    planeTypes[key].gspeed = gpseedI;    // set gspeed

	return key;
}
int planeTypeTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (planeTypes[i].data == data)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

void planeTypeTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (planeTypes[i].key == key)	// make sure the bucket is not empty
		{
			planeTypes[i].data = "";
	 	}
	 }
}

// function to setup the hash table with the 
// initial data from the input file
void planeTypeTable::setData(string maker, string model, int fspeed, int gspeed, string data){
	int skey = hashStrings(maker, model);	// hash function returns hash key
    int ikey = hashInts(fspeed) * hashInts(gspeed); // hash function for integers
	if(ikey>80){ikey=0;}
    int key = skey + ikey;  // combine integer and string hash
	//cout << data << " "  << key << " " << skey << "/" << ikey << endl;

			planeTypes[key].key = key;	// set combined key
			planeTypes[key].data = data;	// set data
			planeTypes[key].maker = maker;	// set maker
			planeTypes[key].model = model;  // set model
            planeTypes[key].fspeed = fspeed;    // set fspeed
            planeTypes[key].gspeed = gspeed;    // set gspeed
			return;	// return if set

		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	//cout << "Error\n";
}



// addititve string hash function
int planeTypeTable::hashStrings(string maker, string model){
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

	int key = num % bucket;	// hash function

	return key;	// return key
}

int planeTypeTable::hashInts(int speed){
	// square speed
	speed = speed * speed;
	string l = to_string(speed);	// convert speed to str
	int length = l.length();	// get length of str
	
	string r;	// create new str to get middle digits
	// get middle digits of str depending on 
	// number of digits
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

	return key;		// return key
}

void planeTypeTable::display(){
    cout << "File Name: data/DATA_PlaneType.CSV\nInsert Content: ['Maker', 'Model', 'FlyingSpeed', 'GroundSpeed']\n";

	// output the table names
	cout << right << setw(10) << "Maker"
    << right << setw(10) << "Model" 
    << right << setw(15) << "FlyingSpeed"
    << right << setw(15) << "GroundSpeed" << endl;
	
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (planeTypes[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(10) << planeTypes[i].maker
				<< right << setw(10) << planeTypes[i].model
				<< right << setw(15) << planeTypes[i].fspeed
				<< right << setw(15) << planeTypes[i].gspeed << endl;
	 	}
	 }
}

void planeTypeTable::write(){
	ofstream output;
	output.open("data_out/DATA_PlaneType.CSV");

	output << "Maker,Model,FlyingSpeed,GroundSpeed\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (planeTypes[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << planeTypes[i].maker << "," << planeTypes[i].model << "," << planeTypes[i].fspeed << "," << planeTypes[i].gspeed << endl;
	 	}
	 }

	cout << "\nWrote table to data_out/DATA_PlaneType.CSV" << endl; 
}