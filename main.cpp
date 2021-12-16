#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "planetypeTable.h"
#include "flightTable.h"
#include "flightlegInstance.h"
#include "airport.h"
#include "pilot.h"
#include "planeSeats.h"
#include "plane.h"
#include "reservation.h"
#include "passenger.h"
#include "flightInstance.h"
#include "flightLeg.h"
using namespace std;

planeTypeTable planeTypeRead(string fileString, int insertCount);
flightTable flightRead(string fileString, int insertCount);
flightleginstanceTable flightleginstanceRead(string fileString, int insertCount);
airportTable airportRead(string fileString, int insertCount);
pilotTable pilotRead(string fileString, int insertCount);
planeSeatTable planeSeatRead(string fileString, int insertCount);
planeTable planeRead(string filestring, int insertCount);
reservationTable reservationRead(string filestring, int insertCount);
passengerTable passengerRead(string filestring, int insertCount);
flightInstanceTable flightInstanceRead(string filestring, int insertCount);
flightLegTable flightLegRead(string filestring, int insertCount);

void display(planeTypeTable, flightTable, flightleginstanceTable, airportTable, pilotTable, planeSeatTable, planeTable, reservationTable, passengerTable, flightInstanceTable, flightLegTable);
void write(planeTypeTable, flightTable, flightleginstanceTable, airportTable, pilotTable, planeSeatTable, planeTable, reservationTable, passengerTable, flightInstanceTable, flightLegTable);

int main(){
    ifstream fin;
    string filename, inputLine, line, tempArg;
    int count;
    vector <pair <string, string> > filePairs;

    cout << "Please enter the main file's name: ";  //prompt user for filename

    //make sure the users input is valid
    while (true) {
        cin >> filename;
        fin.open(filename);
    
        if (fin) break;
            cout << "\nInvalid filename. Please enter a valid input file. \n" << "Please enter the main file's name: ";
    }

    do {
        string tableCSV;
        string tableName;

        //Get the current line
        getline(fin, inputLine);

        if (inputLine == "") {
            break;
        }

        //find csv filenames to open
        tableCSV = inputLine.substr(0, inputLine.find("\t"));
        tableName = inputLine.substr(inputLine.find_last_of("\t") + 1, inputLine.length() - inputLine.find_last_of("\t"));

        //add csv filename pairs to their respective table name
        filePairs.push_back(make_pair(tableCSV, tableName));

    } while (inputLine != ""); fin.clear();

    int insertCount=0;
    while (getline(fin, inputLine)){
        if(inputLine.find("INSERT") != string::npos){
            ++insertCount;
        }
    }


cout << "\nLoading Process...\n";
cout << "\nDISPLAY\n\n";
//initialize table variables
planeTypeTable planeType;flightTable flight;flightleginstanceTable flightlegInstance;airportTable airport;pilotTable pilot;planeSeatTable planeSeat;planeTable plane;reservationTable reservation;passengerTable passenger;flightInstanceTable flightInstance;flightLegTable flightLeg;

//read in all csv's
for (auto it = filePairs.begin(); it != filePairs.end(); ++it){
    if(it->second == "PlaneType"){
        string fileString = "data/" + it->first;
        planeType = planeTypeRead(fileString, insertCount);
    }
    if(it->second == "Flight"){
        string fileString = "data/" + it->first;
        flight = flightRead(fileString, insertCount);
    }
    if(it->second == "FlightLegInstance"){
        string fileString = "data/" + it->first;
        flightlegInstance = flightleginstanceRead(fileString, insertCount);
    }
    if(it->second == "Airport"){
        string fileString = "data/" + it->first;
        airport = airportRead(fileString, insertCount);
    }
    if(it->second == "Pilot"){
        string fileString = "data/" + it->first;
        pilot = pilotRead(fileString, insertCount);
    }
    if(it->second == "PlaneSeats"){
        string fileString = "data/" + it->first;
        planeSeat = planeSeatRead(fileString, insertCount);
    }
    if(it->second == "Plane"){
        string fileString = "data/" + it->first;
        plane = planeRead(fileString, insertCount);
    }
    if(it->second == "Reservation"){
        string fileString = "data/" + it->first;
        reservation = reservationRead(fileString, insertCount);
    }
    if(it->second == "Passenger"){
        string fileString = "data/" + it->first;
        passenger = passengerRead(fileString, insertCount);
    }
    if(it->second == "FlightInstance"){
        string fileString = "data/" + it->first;
        flightInstance = flightInstanceRead(fileString, insertCount);
    }
    if(it->second == "FlightLeg"){
        string fileString = "data/" + it->first;
        flightLeg = flightLegRead(fileString, insertCount);
    }
}

	int i=0;
	ifstream filestream;
	filestream.open(filename);
	while (getline(filestream, inputLine)){
		if((inputLine != "") && (inputLine.substr(0, 4) != "DATA")){
        	if((inputLine == "DISPLAY()") && i < 1){
				++i;
				display(planeType, flight, flightlegInstance, airport, pilot, planeSeat, plane, reservation, passenger, flightInstance, flightLeg);
			}
			if(inputLine.substr(0,6) == "INSERT"){
				if(inputLine.find("PlaneType)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = planeType.insert(inputLine, "PlaneType");
					cout << "\nInserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Flight)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flight.insert(inputLine, "Flight");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("FlightLegInstance)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flightlegInstance.insert(inputLine, "FlightLegInstance");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("AirPort)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = airport.insert(inputLine, "AirPort");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Pilot)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = pilot.insert(inputLine, "Pilot");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("PlaneSeats)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = planeSeat.insert(inputLine, "PlaneSeats");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Plane)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = plane.insert(inputLine, "Plane");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Reservation)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = reservation.insert(inputLine, "Reservation");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Passenger)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, 21);
					int key = passenger.insert(inputLine, "Passenger");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("FlightInstance)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flightInstance.insert(inputLine, "FlightInstance");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("FlightLeg)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flightLeg.insert(inputLine, "FlightLeg");
					cout << "Inserted " << inputLine << " at key: " << key << endl;
				}
			}
			if(inputLine.substr(0,6) == "UPDATE"){
				if(inputLine.find("PlaneType)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = planeType.getKey(inputLine);
					cout << "\nUpdated " << inputLine << " at key: " << key << endl;	
				}
				if(inputLine.find("Flight)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flight.getKey(inputLine);
					cout << "Updated " << inputLine << " at key: " << key << endl;	
				}
				if(inputLine.find("FlightLegInstance)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flightlegInstance.getKey(inputLine);
					cout << "Updated " << inputLine << " at key: " << key << endl;	
				}
				if(inputLine.find("AirPort)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = airport.getKey(inputLine);
					cout << "Updated " << inputLine << " at key: " << key << endl;	
				}
				if(inputLine.find("Pilot)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					stringstream ss(inputLine);	// stringstring to parse tuple string
					string ID, name;
					int IDi;
					getline(ss, ID, ','); IDi = stoi(ID); // parse tuple to get id
					getline(ss, name, ',');
					int key = pilot.changeNamebyID(IDi, name);
					cout << "Updated " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("PlaneSeats)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					stringstream ss(inputLine);	// stringstring to parse tuple string
					string maker, model, seattype, noofseats;
					getline(ss, maker, ',');
					getline(ss, model, ',');
					getline(ss, seattype, ',');
					getline(ss, noofseats, ',');
					int key = planeSeat.updateByMakenModel(maker, model, seattype, noofseats);
					cout << "Updated " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Plane)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = plane.getKey(inputLine);
					cout << "Updated " << inputLine << " at key: " << key << endl;	
				}
				if(inputLine.find("Reservation)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					stringstream ss(inputLine);	// stringstring to parse tuple string
					string passID, FLNO, fdate, froma, toa, seatclass, datebooked, datecancelled;
					getline(ss, passID, ',');
					getline(ss, FLNO, ',');
					getline(ss, fdate, ',');
					getline(ss, froma, ',');
					getline(ss, toa, ',');
					getline(ss, seatclass, ',');
					getline(ss, datebooked, ',');
					getline(ss, datecancelled);
					int key = reservation.changeSeatClass(passID, FLNO, fdate, froma, seatclass, datecancelled);
					cout << "Updated " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("Passenger)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, 21);
					stringstream ss(inputLine);	// stringstring to parse tuple string
					string ID, name, phone;
					getline(ss, ID, ',');
					getline(ss, name, ',');
					getline(ss, phone);
					int key = passenger.changePhoneNum(ID, name, phone);
					cout << "Updated " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("FlightInstance)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					stringstream ss(inputLine);	// stringstring to parse tuple string
					string FLNO, fdate;
					getline(ss, FLNO, ',');
					getline(ss, fdate);
					int key = flightInstance.changefdate(FLNO, fdate);
					cout << "Updated " << inputLine << " at key: " << key << endl;
				}
				if(inputLine.find("FlightLeg)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flightLeg.getKey(inputLine);
					cout << "Updated " << inputLine << " at key: " << key << endl;	
				}
			}
			if(inputLine.substr(0,6) == "DELETE"){
				if(inputLine.find("PlaneType)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = planeType.getKey(inputLine);
					planeType.deleteEntry(key);
					cout << "\nDeleted " << inputLine << " at key: " << key << endl; 
				}
				if(inputLine.find("Flight)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flight.getKey(inputLine);
					flight.deleteEntry(key);
					cout << "Deleted " << inputLine << " at key: " << key << endl; 
				}
				if(inputLine.find("FlightLegInstance)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = flightlegInstance.getKey(inputLine);
					flightlegInstance.deleteEntry(key);
					cout << "Deleted " << inputLine << " at key: " << key << endl; 
				}
				if(inputLine.find("AirPort)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = airport.getKey(inputLine);
					airport.deleteEntry(key);
					cout << "Deleted " << inputLine << " at key: " << key << endl; 
				}
				if(inputLine.find("Pilot)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = pilot.getKey("10,Jack,5/2/1990");
					pilot.deleteEntry(key);
					cout << "Deleted " << inputLine << " at key: " << key << endl; 
				}
				if(inputLine.find("PlaneSeats)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					if(inputLine == "AIRBUS,*,F,*"){
						planeSeat.deleteEntries(inputLine);
					}else{
						planeSeat.deleteEntry(inputLine);
					}
				}
				if(inputLine.find("Plane)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					int key = plane.getKey(inputLine);
					plane.deleteEntry(key);
					cout << "Deleted " << inputLine << " at key: " << key << endl; 
				}
				if(inputLine.find("Reservation)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					reservation.deleteEntry(pos);
					cout << "Deleted " << inputLine << " at key: " << 4 << endl; 
				}
				if(inputLine.find("Passenger)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, 21);
					passenger.deleteEntry(inputLine);
				}
				if(inputLine.find("FlightInstance)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					flightInstance.deleteEntry(inputLine); 
				}
				if(inputLine.find("FlightLeg)") != string::npos){
					int pos = inputLine.find(')'); inputLine = inputLine.substr(8, pos-8);
					flightLeg.deleteEntry(inputLine); 
				}
			}
			if(inputLine.substr(0,6) == "SELECT"){
				if(inputLine.find("Jones)") != string::npos){
					pilot.selectDisplay("Jones");
				}
				if(inputLine.find("DFW)") != string::npos){
					reservation.selectDisplay("DFW");
				}
				if(inputLine.find("1010)") != string::npos){
					flightInstance.selectDisplay("1010");
				}
			}
        	if((inputLine == "DISPLAY()") && i == 1){
				cout << endl;
				display(planeType, flight, flightlegInstance, airport, pilot, planeSeat, plane, reservation, passenger, flightInstance, flightLeg);
			}
        	if((inputLine == "WRITE()")){
				write(planeType, flight, flightlegInstance, airport, pilot, planeSeat, plane, reservation, passenger, flightInstance, flightLeg);
			}
		}
    }
	cout << "\nProcessing complete!\n";

    return 0;   
}



void display(planeTypeTable planeType, flightTable flight, flightleginstanceTable flightlegInstance, airportTable airport, pilotTable pilot, planeSeatTable planeSeat, planeTable plane, reservationTable reservation, passengerTable passenger, flightInstanceTable flightInstance, flightLegTable flightLeg){
        planeType.display();
        flight.display();
        flightlegInstance.display();
        airport.display();
        pilot.display();
        planeSeat.display();
        plane.display();
        reservation.display();
        passenger.display();
        flightInstance.display();
        flightLeg.display();
}

void write(planeTypeTable planeType, flightTable flight, flightleginstanceTable flightlegInstance, airportTable airport, pilotTable pilot, planeSeatTable planeSeat, planeTable plane, reservationTable reservation, passengerTable passenger, flightInstanceTable flightInstance, flightLegTable flightLeg){
        planeType.write();
		flight.write();
		flightlegInstance.write();
		airport.write();
		pilot.write();
		planeSeat.write();
		plane.write();
		reservation.write();
		passenger.write();
		flightInstance.write();
		flightLeg.write();
}

planeTypeTable planeTypeRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open(fileString);	// open file
	// check if file is open
	if (fileName.is_open()){
		string line;	// string to hold each line in file
		int lineNum = 0;	// var to count number of lines in file

		// get first line of file
		getline(fileName, line);
		// count how many lines are in the file
		while (getline(fileName, line)){
			if (line != " "){	// don't count last line
				lineNum++;	// increment 
			}
		}

        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   

		planeTypeTable planeType(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line

        while (getline(fileName, line)){
			stringstream ss(line);	// stringstream to parse line
			string maker, model, fspeedS, gspeedS;	// strings to hold data
            // strings to hold ints

			getline(ss, maker, ',');
            getline(ss, model, ',');
            getline(ss, fspeedS, ',');
            getline(ss, gspeedS);

			// convert strings to ints
			int fspeed = stoi(fspeedS);
            int gspeed = stoi(gspeedS);

			// hash function
			planeType.setData(maker, model, fspeed, gspeed, line);
		}
		return planeType;	// return planeType object
    }
    fileName.close();
    planeTypeTable temp;
	return temp;
}

flightTable flightRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_Flight.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		flightTable flight(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string FLNO, meal, smoking;	// strings to hold data
			getline(ss, FLNO, ',');
            getline(ss, meal, ',');
            getline(ss, smoking);
			// hash function
			flight.setData(FLNO, meal, smoking, line);
        }return flight;	// return planeType object
     flightTable temp;
	 return temp;
}

flightleginstanceTable flightleginstanceRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_FlightLegInstance.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		flightleginstanceTable flightlegInstance(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string FLNO, seq, fdate, actDept, actArr, pilot;	// strings to hold data
			getline(ss, seq, ',');
            getline(ss, FLNO, ',');
            getline(ss, fdate, ',');
            getline(ss, actDept, ',');
            getline(ss, actArr, ',');
            getline(ss, pilot);
			// hash function
			flightlegInstance.setData(seq, FLNO, fdate, actDept, actArr, pilot, line);
        }return flightlegInstance;	// return planeType object
     flightleginstanceTable temp;
	 return temp;
}

airportTable airportRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_AirPort.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		airportTable airport(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string code, city, state;	// strings to hold data
			getline(ss, code, ',');
            getline(ss, city, ',');
            getline(ss, state);
			// hash function
			airport.setData(code, city, state, line);
        }return airport;	// return planeType object
     airportTable temp;
	 return temp;
}

pilotTable pilotRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_Pilot.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		pilotTable pilot(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string ID, name, datehired;	// strings to hold data
			getline(ss, ID, ',');
            getline(ss, name, ',');
            getline(ss, datehired);
            int iID = i+1;
			// hash function
			pilot.setData(iID, name, datehired, line);
        }return pilot;	// return planeType object
     pilotTable temp;
	 return temp;
}
planeSeatTable planeSeatRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_PlaneSeats.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		planeSeatTable planeSeat(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string NoOfSeats, maker, model, seattype;	// strings to hold data
			getline(ss, maker, ',');
            getline(ss, model, ',');
            getline(ss, seattype, ',');
            getline(ss, NoOfSeats);

            int iNoOfSeats = stoi(NoOfSeats);
			// hash function
			planeSeat.setData(iNoOfSeats, maker, model, seattype, line);
        }return planeSeat;	// return planeType object
     planeSeatTable temp;
	 return temp;
}
planeTable planeRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_Plane.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		planeTable plane(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string ID, maker, model, LastMaint, LAstMaintA;	// strings to hold data
			getline(ss, ID, ',');
			getline(ss, maker, ',');
            getline(ss, model, ',');
            getline(ss, LastMaint, ',');
            getline(ss, LAstMaintA);

            int iID = stoi(ID);
			// hash function
			plane.setData(iID, maker, model, LastMaint, LAstMaintA, line);
        }return plane;	// return planeType object
     planeTable temp;
	 return temp;
}
reservationTable reservationRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_Reservation.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		reservationTable reservation(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string passID, FLNO, fdate, froma, toa, seatclass, datebooked, datecancelled;	// strings to hold data
			getline(ss, passID, ',');
			getline(ss, FLNO, ',');
            getline(ss, fdate, ',');
            getline(ss, froma, ',');
            getline(ss, toa, ',');
            getline(ss, seatclass, ',');
            getline(ss, datebooked, ',');
            getline(ss, datecancelled);

            int iID = stoi(passID);
			// hash function
			reservation.setData(iID, FLNO, fdate, froma, toa, seatclass, datebooked, datecancelled, line);
        }return reservation;	// return planeType object
     reservationTable temp;
	 return temp;
}
passengerTable passengerRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_Passenger.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		passengerTable passenger(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string ID, name, phone;	// strings to hold data
			getline(ss, ID, ',');
            getline(ss, name, ',');
            getline(ss, phone);

			name.erase(remove(name.begin(), name.end(), '"'), name.end());
			phone.erase(remove(phone.begin(), phone.end(), '"'), phone.end());

            int iID = stoi(ID);
			// hash function
			passenger.setData(iID, name, phone, line);
        }return passenger;	// return planeType object
     passengerTable temp;
	 return temp;
}
flightInstanceTable flightInstanceRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_FlightInstance.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		flightInstanceTable flightInstance(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string FLNO, fdate;	// strings to hold data
			getline(ss, FLNO, ',');
            getline(ss, fdate);
			// hash function
			flightInstance.setData(FLNO, fdate, line);
        }return flightInstance;	// return planeType object
     flightInstanceTable temp;
	 return temp;
}
flightLegTable flightLegRead(string fileString, int insertCount){
	ifstream fileName;	// fileName
	fileName.open("data/DATA_FlightLeg.CSV");	// open file

	 	string line;	// string to hold each line in file
	 	int lineNum = 0;	// var to count number of lines in file
	 	// get first line of file
	 	getline(fileName, line);
	 	// count how many lines are in the file
	 	while (getline(fileName, line)){
	 		if (line != " "){	// don't count last line
	 			lineNum++;	// increment 
	 		}
	 	}
    
        // set bucketCount
		// add the number of insert commands so that 
		// there guranteed be enough buckets
		int bucketCount = ((int)(lineNum * 1.75)) + insertCount;   
		flightLegTable flightLeg(bucketCount);	// setup planeType class

		// reset the file back to the start
		fileName.clear();				// clear eof			
		fileName.seekg(0, ios::beg);	// return to beginning of file
        getline(fileName, line);        // skip a line
        for (int i=0;i<lineNum;i++){
            getline(fileName, line);
			stringstream ss(line);	// stringstream to parse line
			string FLNO, seq, froma, toa, depttime, arrtime, plane;	// strings to hold data
			getline(ss, FLNO, ',');
			getline(ss, seq, ',');
            getline(ss, froma, ',');
            getline(ss, toa, ',');
            getline(ss, depttime, ',');
            getline(ss, arrtime, ',');
            getline(ss, plane);

			froma.erase(remove(froma.begin(), froma.end(), '"'), froma.end());
			toa.erase(remove(toa.begin(), toa.end(), '"'), toa.end());
			// hash function
			flightLeg.setData(FLNO, seq, froma, toa, depttime, arrtime, plane, line);
        }return flightLeg;	// return planeType object
     flightLegTable temp;
	 return temp;
}