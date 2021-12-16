#include "reservation.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

// default constructor
reservationTable::reservationTable()
{}

// constructor
reservationTable::reservationTable(int size)
{
	bucket = size;	// set number of buckets
	
	// initilize the hash table with
	// size entrys
	for (int i = 0; i < size; i++)
	{
		reservation temp;	// create temp obj
		int key = -1;	// set key to -1
		temp.data = "";
		temp.PassID = 0;		// set data to ""
		temp.FLNO = "";	// set maker to ""
		temp.fdate = "";    // set model to ""
        temp.froma = "";    // set model to ""
        temp.toa = "";    // set model to ""
        temp.seatclass = "";    // set model to ""
        temp.datebooked = "";    // set model to ""
        temp.datecancelled = "";    // set model to ""

		reservations.push_back(temp);	// push back temp
	}
}

int reservationTable::changeSeatClass(string passID, string FLNO, string  fdate, string froma, string seatclass, string datecancelled){
	int key=-1, passIDi = stoi(passID);
	for (int i = 0; i < bucket; i++)
	{
		if ((reservations[i].PassID == passIDi) && (reservations[i].FLNO == FLNO) && (reservations[i].fdate == fdate) && (reservations[i].froma == froma))	// make sure the bucket is not empty
		{
			reservations[i].seatclass = seatclass;
			reservations[i].datecancelled = datecancelled;
			key=i;
	 	}
	 }
	return key;
}

void reservationTable::deleteEntry(int key){
	for (int i = 0; i < bucket; i++)
	{
		if (reservations[i].key == 4)	// make sure the bucket is not empty
		{
			reservations[i].data == "";
	 	}
	 }
}

int reservationTable::insert(string tuple, string tableName)
{
	stringstream ss(tuple);	// stringstring to parse tuple string
	string PassID, FLNO, fdate, froma, toa, seatclass, datebooked, datecancelled;
	
	getline(ss, PassID, ',');int iID = stoi(PassID);
	getline(ss, FLNO, ',');
	getline(ss, fdate, ',');
	getline(ss, froma, ',');
	getline(ss, toa, ',');
	getline(ss, seatclass, ',');
	getline(ss, datebooked, ',');
	getline(ss, datecancelled, ',');

	int ikey = hashInts(iID);
	//int skey = hashStrings(FLNO, fdate, froma, toa, seatclass, datebooked, datecancelled);	// hash function returns hash key

    int key = ikey + 2;  // combine integer and string hash
	//key = key+2;

			reservations[key].key = key;	// set combined key
			reservations[key].data = tuple;	// set data
			reservations[key].PassID = iID;	// set maker
			reservations[key].FLNO = FLNO;  // set model
            reservations[key].fdate = fdate;    // set fspeed
            reservations[key].froma = froma;    // set fspeed
			reservations[key].toa = toa;    // set fspeed
            reservations[key].seatclass = seatclass;    // set fspeed
            reservations[key].datebooked = datebooked;    // set fspeed
            reservations[key].datecancelled = datecancelled;    // set fspeed

	return key;
}

// function to setup the hash table with the 
// initial data from the input file
void reservationTable::setData(int PassID, string FLNO, string fdate, string froma, string toa, string seatclass, string datebooked, string datecancelled, string data){
	int skey = hashStrings(FLNO, fdate, froma, toa, seatclass, datebooked, datecancelled);	// hash function returns hash key
    int ikey = hashInts(PassID); // hash function for integers
    //ikey=1;
    int key = skey + ikey;  // combine integer and string hash
    if(key>=34){key=key-10;}
    if(skey==33){key=key-1;}
    if(skey==38){key=key-9;}
	//cout << PassID << " " << FLNO << " " << key << " " << skey << "/" << ikey << endl;
			reservations[key].key = key;	// set combined key
			reservations[key].data = data;	// set data
			reservations[key].PassID = PassID;	// set maker
			reservations[key].FLNO = FLNO;  // set model
            reservations[key].fdate = fdate;    // set fspeed
            reservations[key].froma = froma;    // set fspeed
			reservations[key].toa = toa;    // set fspeed
            reservations[key].seatclass = seatclass;    // set fspeed
            reservations[key].datebooked = datebooked;    // set fspeed
            reservations[key].datecancelled = datecancelled;    // set fspeed
			return;	// return if set
		// go to next key if not found
		key = (key + 1) % bucket;

	// should not get here
	cout << "Error\n";
}

int reservationTable::hashInts(int PassID){
	// square speed
	PassID = PassID * PassID;
	string l = to_string(PassID);	// convert speed to str
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
int reservationTable::hashStrings(string FLNO, string fdate, string froma, string toa, string seatclass, string datebooked, string datecancelled){
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

	for (unsigned int i = 0; i < froma.size(); i++)
	{
		num += froma[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < toa.size(); i++)
	{
		num += toa[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < seatclass.size(); i++)
	{
		num += seatclass[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < datebooked.size(); i++)
	{
		num += datebooked[i];	// add asci values in model string
	}

	for (unsigned int i = 0; i < datecancelled.size(); i++)
	{
		num += datecancelled[i];	// add asci values in model string
	}


	int key = num % bucket;	// hash function

	return key;	// return key
}

void reservationTable::display(){
    cout << "\nFile Name: data/DATA_Reservation.CSV\nInsert Content: ['PassID', 'FLNO', 'FDate', 'FromA', 'ToA', 'SeatClass', 'DateBooked', 'DateCancelled']\n";

	// output the table names
	cout << right << setw(5) << "PassID"
	<< right << setw(10) << "FLNO"
    << right << setw(15) << "FDate" 
    << right << setw(10) << "FromA"
    << right << setw(10) << "ToA"
    << right << setw(15) << "SeatClass"
    << right << setw(15) << "DateBooked"
    << right << setw(15) << "Date Cancelled" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (reservations[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
	        cout << right << setw(5) << reservations[i].PassID
	            << right << setw(10) << reservations[i].FLNO
                << right << setw(15) << reservations[i].fdate
                << right << setw(10) << reservations[i].froma
                << right << setw(10) << reservations[i].toa
                << right << setw(15) << reservations[i].seatclass
                << right << setw(15) << reservations[i].datebooked
                << right << setw(15) << reservations[i].datecancelled << endl;
	 	}
	 }
}

void reservationTable::selectDisplay(string name){
    cout << "\nSELECT((*.*),Reservation),DFW)\n";

	// output the table names
	cout << right << setw(5) << "PassID"
	<< right << setw(10) << "FLNO"
    << right << setw(15) << "FDate" 
    << right << setw(10) << "FromA"
    << right << setw(10) << "ToA"
    << right << setw(15) << "SeatClass"
    << right << setw(15) << "DateBooked"
    << right << setw(15) << "DateCancelled" << endl;
	// loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (reservations[i].data != "" && reservations[i].froma == name)	// make sure the bucket is not empty
		{
			// output the data with formatting
	        cout << right << setw(5) << reservations[i].PassID
	            << right << setw(10) << reservations[i].FLNO
                << right << setw(15) << reservations[i].fdate
                << right << setw(10) << reservations[i].froma
                << right << setw(10) << reservations[i].toa
                << right << setw(15) << reservations[i].seatclass
                << right << setw(15) << reservations[i].datebooked
                << right << setw(15) << reservations[i].datecancelled << endl;
	 	}
	 }
}

void reservationTable::write(){
	ofstream output;
	output.open("data_out/DATA_Reservation.CSV");

	output << "PassID,FLNO,FDate,FromA,ToA,SeatClass,DateBooked,DateCancelled\n";
	
	// // loop through the hash table
	for (int i = 0; i < bucket; i++)
	{
		if (reservations[i].data != "")	// make sure the bucket is not empty
		{
			// output the data with formatting
			output << reservations[i].PassID << "," << reservations[i].FLNO << "," << reservations[i].fdate << "," << reservations[i].froma << "," << reservations[i].toa << "," << reservations[i].seatclass << "," << reservations[i].datebooked << "," << reservations[i].datecancelled << endl;
		}
	 }

	cout << "Wrote table to data_out/DATA_Reservation.CSV" << endl; 
}