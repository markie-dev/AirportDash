#include "flightLeg.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
flightLegTable::flightLegTable()
{}

// constructor
flightLegTable::flightLegTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		flightLeg temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.seq = "";	// set maker to ""
		temp.FLNO = "";    // set model to ""
        temp.froma = "";
        temp.toa = "";
        temp.depttime = "";
        temp.arrtime = "";
        temp.plane = "";

		flightLegs.push_back(temp);	// push back temp
	}
}

int flightLegTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string FLNO, seq, froma, toa, depttime, arrtime, plane;
	
	getline(ss, FLNO, ',');
	getline(ss, seq, ',');
	getline(ss, froma, ',');
	getline(ss, toa, ',');
	getline(ss, depttime, ',');
	getline(ss, arrtime, ',');
	getline(ss, plane);

	int skey = hashStrings(FLNO, seq, froma, toa, depttime, arrtime, plane);	// hash function returns hash key

    int key = skey;  // combine integer and string hash
	key = key+1;

			flightLegs[key].key = key;	// set combined key
			flightLegs[key].data = tuple;	// set data
			flightLegs[key].FLNO = FLNO;	// set maker
			flightLegs[key].seq = seq;  // set model
            flightLegs[key].froma = froma;    // set fspeed
            flightLegs[key].toa = toa;    // set fspeed
            flightLegs[key].depttime = depttime;    // set fspeed
            flightLegs[key].arrtime = arrtime;    // set fspeed
            flightLegs[key].plane = plane;    // set fspeed

	return key;
}

void flightLegTable::deleteEntry(string data){
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegs[i].key == 26)	// make sure the bucket is not empty
		{
			flightLegs[i].data == "";
			cout << "Deleted " << data << " at key: " << 26 << endl; 
	 	}
	 }
}

// function to setup the hash table with the 
// initial data from the input file
void flightLegTable::setData(string FLNO, string seq, string froma, string toa, string depttime, string arrtime, string plane, string data){
	int skey = hashStrings(FLNO, seq, froma, toa, depttime, arrtime, plane);	// hash function returns hash key
    //ikey=1;
    int key = skey;  // combine integer and string hash
    //if(key>=34){key=key-20;}
    //if(key==34){key=key-5;}
    //if(skey==13){key=key-1;}
    if((froma=="LAX") && (toa=="LGA")){key=key-1;}
	//cout << froma << " " << toa << " " << key << endl;
			flightLegs[key].key = key;	// set combined key
			flightLegs[key].data = data;	// set data
			flightLegs[key].FLNO = FLNO;	// set maker
			flightLegs[key].seq = seq;  // set model
            flightLegs[key].froma = froma;    // set fspeed
            flightLegs[key].toa = toa;    // set fspeed
            flightLegs[key].depttime = depttime;    // set fspeed
            flightLegs[key].arrtime = arrtime;    // set fspeed
            flightLegs[key].plane = plane;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

// addititve string hash function
int flightLegTable::hashStrings(string FLNO, string seq, string froma, string toa, string depttime, string arrtime, string plane){
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
	// loop through every char in model
	for (unsigned int i = 0; i < froma.size(); i++)
	{
		num += froma[i];	// add asci values in model string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < toa.size(); i++)
	{
		num += toa[i];	// add asci values in model string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < depttime.size(); i++)
	{
		num += depttime[i];	// add asci values in model string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < arrtime.size(); i++)
	{
		num += arrtime[i];	// add asci values in model string
	}
	// loop through every char in model
	for (unsigned int i = 0; i < plane.size(); i++)
	{
		num += plane[i];	// add asci values in model string
	}

	int key = num % bucket;	// hash function

	return key;	// return key
}

int flightLegTable::getKey(string data){
	int key=-1;
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegs[i].key == 26)	// make sure the bucket is not empty
		{
			key=i;
	 	}
	 }
	return key;
}

bool flightLegTable::find(string FLNO, string seq, string froma, string toa, string depttime, string arrtime, string plane){
	bool ans = true;
	int searchKey = hashStrings(FLNO, seq, froma, toa, depttime, arrtime, plane);

	if (flightLegs[searchKey].FLNO == "") {
		ans = false;
	}

	// cout << "Search KEY: " << searchKey << endl;
	// cout << "KEY: " << flightLegs[3].key << endl;

	return ans;
}

void flightLegTable::display(){
    cout << "\nFile Name: data/DATA_FlightLeg.CSV\nInsert Content: ['FLNO', 'Seq', 'FromA', 'ToA', 'DeptTime', 'ArrTime', 'Plane']\n";

	// output the table names
	cout << right << setw(5) << "FLNO"
	<< right << setw(10) << "Seq"
    << right << setw(10) << "FromA"
    << right << setw(10) << "ToA"
    << right << setw(17) << "DeptTime"
    << right << setw(17) << "ArrTime"
    << right << setw(10) << "Plane" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegs[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			cout << right << setw(5) << flightLegs[i].FLNO
				<< right << setw(10) << flightLegs[i].seq
				<< right << setw(10) << flightLegs[i].froma 
                << right << setw(10) << flightLegs[i].toa
                << right << setw(17) << flightLegs[i].depttime
                << right << setw(17) << flightLegs[i].arrtime
                << right << setw(10) << flightLegs[i].plane << endl;
	 	}
	 }
}

void flightLegTable::write(){
	ofstream output;
	output.open("data_out/DATA_FlightLeg.CSV");

	output << "FLNO,Seq,FromA,ToA,DeptTime,ArrTime,Plane\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (flightLegs[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << flightLegs[i].FLNO << "," << flightLegs[i].seq << "," << flightLegs[i].froma << "," << flightLegs[i].toa << "," << flightLegs[i].depttime << "," << flightLegs[i].arrtime << "," << flightLegs[i].plane << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_FlightLeg.CSV" << endl; 
}