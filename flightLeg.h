#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct flightLeg{
	int key;	// combined hash key
	string FLNO;	// plane maker
	string seq;	// plane model
    string froma;
    string toa;
    string depttime;
    string arrtime;
    string plane;
    string data;
};

// hash table class using addititve string hash and mid-square hashing
class flightLegTable{
private:
	vector <flightLeg> flightLegs;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	flightLegTable();	// default constructor
	flightLegTable(int size); // constructor

	// function declarations
	void setData(string FLNO, string seq, string froma, string toa, string depttime, string arrtime, string plane, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int getKey(string data);
	// void update(int x, std::string data);
	bool find(string FLNO, string seq, string froma, string toa, string depttime, string arrtime, string plane); //***
	void deleteEntry(string data);
	void write();

	// hash function
	int hashStrings(string FLNO, string seq, string froma, string toa, string depttime, string arrtime, string plane);

};