#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct reservation{
	int key;	// combined hash key
	int PassID;	// full entry data
	string FLNO;	// plane maker
	string fdate;	// plane model
    string froma;
    string toa;
	string seatclass;
    string datebooked;
    string datecancelled;
    string data;
};

// hash table class using addititve string hash and mid-square hashing
class reservationTable{
private:
	vector <reservation> reservations;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	reservationTable();	// default constructor
	reservationTable(int size); // constructor

	// function declarations
	void setData(int PassID, string FLNO, string fdate, string froma, string toa, string seatclass, string datebooked, string datecancelled, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int changeSeatClass(string passID, string FLNO, string  fdate, string froma, string seatclass, string datecancelled);
	// void update(int x, std::string data);
	// int find(std::string tuple, std::string tableName);
	void selectDisplay(string name);
	void deleteEntry(int x);
	void write();

	// hash function
	int hashStrings(string FLNO, string fdate, string froma, string toa, string seatclass, string datebooked, string datecancelled);
    int hashInts(int);
};