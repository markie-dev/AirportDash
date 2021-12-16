#include "flightlegInstance.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
flightleginstanceTable::flightleginstanceTable()
{}

// constructor
flightleginstanceTable::flightleginstanceTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		flightlegInstance temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.seq = "";		// set data to ""
		temp.FLNO = "";	// set maker to ""
		temp.fdate = "";    // set model to ""
        temp.ActDept = "";    // set model to ""
        temp.ActArr = "";    // set model to ""
        temp.pilot = "";    // set model to ""

		flightLegInstances.push_back(temp);	// push back temp
	}
}

int flightleginstanceTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegInstances[i].data == data)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

void flightleginstanceTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegInstances[i].key == key)	// make sure the bucket is not empty
		{
			flightLegInstances[i].data == "";
	 	}
	 }
}


int flightleginstanceTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string FLNO, seq, fdate, actdept, actarr, pilot;	

	getline(ss, seq, ',');	// parse tuple to get id
	getline(ss, FLNO, ',');
	getline(ss, fdate, ',');
	getline(ss, actdept, ',');
	getline(ss, actarr, ',');
	getline(ss, pilot);

	int skey = hashStrings(seq, FLNO, fdate, actdept, actarr, pilot);	// hash function returns hash key

    int key = skey;  // combine integer and string hash
	//key = key+2;
	
	flightLegInstances[key].key = key;	// set combined key
	flightLegInstances[key].data = tuple;	// set data
	flightLegInstances[key].FLNO = FLNO;	// set maker
	flightLegInstances[key].seq = seq;  // set model
	flightLegInstances[key].fdate = fdate;
	flightLegInstances[key].ActDept = actdept;
	flightLegInstances[key].ActArr = actarr;
	flightLegInstances[key].pilot = pilot;

	return key;
}


// function to setup the hash table with the 
// initial data from the input file
void flightleginstanceTable::setData(string seq, string FLNO, string fdate, string ActDept, string ActArr, string pilot, string data){
	int skey = hashStrings(seq, FLNO, fdate, ActDept, ActArr, pilot);	// hash function returns hash key
    int key = skey;  // combine integer and string hash
			flightLegInstances[key].key = key;	// set combined key
			flightLegInstances[key].data = data;	// set data
			flightLegInstances[key].FLNO = FLNO;	// set maker
			flightLegInstances[key].seq = seq;  // set model
            flightLegInstances[key].fdate = fdate;    // set fspeed
            flightLegInstances[key].ActDept = ActDept;
            flightLegInstances[key].ActArr = ActArr;
            flightLegInstances[key].pilot = pilot;
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}



// addititve string hash function
int flightleginstanceTable::hashStrings(string seq, string FLNO, string fdate, string ActDept, string ActArr, string pilot){
	int num = 0; // var to hold additive asci values
	// loop through every char in maker
	for (unsigned int i = 0; i < FLNO.size(); i++)
	{
		num += FLNO[i];	// add asci values in maker string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < seq.size(); i++)
	{
		num += seq[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < fdate.size(); i++)
	{
		num += fdate[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < ActDept.size(); i++)
	{
		num += ActDept[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < ActArr.size(); i++)
	{
		num += ActArr[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < pilot.size(); i++)
	{
		num += pilot[i];	// add asci values in model string
	}


	int key = num % bucket;	// hash function

	return key;	// return key
}

bool flightleginstanceTable::find(string seq, string FLNO, string fdate, string ActDept, string ActArr, string pilot){
	bool ans = true;
	int searchKey = hashStrings(seq, FLNO, fdate, ActDept, ActArr, pilot);

	if (flightLegInstances[searchKey].FLNO == "") {
		ans = false;
	}

	// cout << "Search KEY: " << searchKey << endl;
	// cout << "KEY: " << flightLegs[3].key << endl;

	return ans;
}

void flightleginstanceTable::display(){
    cout << "\nFile Name: data/DATA_FlightLegInstance.CSV\nInsert Content: ['Seq', 'FLNO', 'Fdate', 'ActDept', 'ActArr', 'Pilot']\n";

	// output the table names
	cout << right << setw(5) << "Seq"
    << right << setw(5) << "FLNO" 
    << right << setw(10) << "Fdate"
    << right << setw(16) << "ActDept"
    << right << setw(16) << "ActArr"
    << right << setw(10) << "Pilot" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegInstances[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << flightLegInstances[i].seq
				<< right << setw(5) << flightLegInstances[i].FLNO
				<< right << setw(10) << flightLegInstances[i].fdate
                << right << setw(16) << flightLegInstances[i].ActDept
                << right << setw(16) << flightLegInstances[i].ActArr
                << right << setw(10) << flightLegInstances[i].pilot << endl;
	 	}
	 }
}

void flightleginstanceTable::write(){
	ofstream output;
	output.open("data_out/DATA_FlightLegInstance.CSV");

	output << "Seq,FLNO,Fdate,ActDept,ActArr,Pilot\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegInstances[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << flightLegInstances[i].seq<< "," <<flightLegInstances[i].FLNO<< "," <<flightLegInstances[i].fdate<< "," <<flightLegInstances[i].ActDept<< "," <<flightLegInstances[i].ActArr<< "," <<flightLegInstances[i].pilot << endl;
	 	}
	 }

	cout << "Wrote table to data_out/DATA_FlightLegInstance.CSV" << endl; 
}