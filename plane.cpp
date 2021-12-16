#include "plane.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
planeTable::planeTable()
{}

// constructor
planeTable::planeTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		plane temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.ID = 0;		// set data to ""
		temp.maker = "";	// set maker to ""
		temp.model = "";    // set model to ""
        temp.lastmaint = "";    // set model to ""
        temp.lastmainta = "";    // set model to ""

		planes.push_back(temp);	// push back temp
	}
}

int planeTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (planes[i].data == data)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

void planeTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (planes[i].key == key)	// make sure the bucket is not empty
		{
			planes[i].data == "";
	 	}
	 }
}

int planeTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string ID, maker, model, lastmaint, lastmaina;

	getline(ss, ID, ',');int iID = stoi(ID);
	getline(ss, maker, ',');
	getline(ss, model, ',');
	getline(ss, lastmaint, ',');
	getline(ss, lastmaina);

	int ikey = hashInts(iID);
	int skey = hashStrings(maker, model, lastmaint, lastmaina);	// hash function returns hash key

    int key = skey + ikey + 2;  // combine integer and string hash
	//key = key+2;

			planes[key].key = key;	// set combined key
			planes[key].data = tuple;	// set data
			planes[key].ID = iID;	// set maker
			planes[key].maker = maker;  // set model
            planes[key].model = model;    // set fspeed
            planes[key].lastmaint = lastmaint;    // set fspeed
			planes[key].lastmainta = lastmaina;    // set fspeed

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void planeTable::setData(int ID, string maker, string model, string lastmaint, string lastmainta, string data){
	int skey = hashStrings(maker, model, lastmaint, lastmainta);	// hash function returns hash key
    int ikey = hashInts(ID); // hash function for integers
    ikey=1;
    int key = skey + ikey;  // combine integer and string hash
    //if(key>=34){key=key-20;}
    //if(key==24){key=key-ikey;}
	//cout << maker << " " << model << " " << key << " " << skey << "/" << ikey << endl;
			planes[key].key = key;	// set combined key
			planes[key].data = data;	// set data
			planes[key].ID = ID;	// set maker
			planes[key].maker = maker;  // set model
            planes[key].model = model;    // set fspeed
            planes[key].lastmaint = lastmaint;    // set fspeed
			planes[key].lastmainta = lastmainta;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

int planeTable::hashInts(int ID){
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
int planeTable::hashStrings(string maker, string model, string lastmaint, string lastmainta){
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

	for (unsigned int i = 0; i < lastmaint.size(); i++)
	{
		num += lastmaint[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < lastmainta.size(); i++)
	{
		num += lastmainta[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

void planeTable::display(){
    cout << "\nFile Name: data/DATA_Plane.CSV\nInsert Content: ['ID', 'Maker', 'Model', 'LastMaint', 'LastMaintA']\n";

	// output the table names
	cout << right << setw(5) << "ID"
	<< right << setw(10) << "Maker"
    << right << setw(10) << "Model" 
    << right << setw(15) << "LastMaint"
    << right << setw(15) << "LastMaintA" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (planes[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << planes[i].ID
				<< right << setw(10) << planes[i].maker
				<< right << setw(10) << planes[i].model
				<< right << setw(15) << planes[i].lastmaint
                << right << setw(15) << planes[i].lastmainta << endl;
	 	}
	 }
}

void planeTable::write(){
	ofstream output;
	output.open("data_out/DATA_Plane.CSV");

	output << "ID,Maker,Model,LastMaint,LastMaintA\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (planes[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << planes[i].ID << "," << planes[i].maker << "," << planes[i].model << "," << planes[i].lastmaint << "," << planes[i].lastmainta << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_Plane.CSV" << endl; 
}