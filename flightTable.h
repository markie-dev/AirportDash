#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct flight{
	int key;	// combined hash key
	string FLNO;	// full entry data
	string meal;	// plane maker
	string smoking;	// plane model
	string data;
};

// hash table class using addititve string hash and mid-square hashing
class flightTable{
private:
	vector <flight> flights;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	flightTable();	// default constructor
	flightTable(int size); // constructor

	// function declarations
	void setData(string FLNO, string meal, string smoking, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	int getKey(string data);
	void display();
	// void update(int x, std::string data);
	bool find(string FLNO, string meal, string smoking);
	void deleteEntry(int x);
	void write();

	// hash function
	int hashStrings(string FLNO, string meal, string smoking);

};