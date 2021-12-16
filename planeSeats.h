#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct planeSeat{
	int key;	// combined hash key
	int NoOfSeats;	// full entry data
	string maker;	// plane maker
	string model;	// plane model
    string seattype;
	string data;
};

// hash table class using addititve string hash and mid-square hashing
class planeSeatTable{
private:
	vector <planeSeat> planeSeats;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	planeSeatTable();	// default constructor
	planeSeatTable(int size); // constructor

	// function declarations
	void setData(int NoOfSeats, string maker, string model, string seattype, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int updateByMakenModel(string make, string model, string seattype, string noofseats);
	void deleteEntries(string data);
	// void update(int x, std::string data);
	// int find(std::string tuple, std::string tableName);
	void deleteEntry(string data);
	void write();

	// hash function
	int hashStrings(string maker, string model, string seattype);
    int hashInts(int);

};