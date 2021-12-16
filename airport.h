#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct airport{
	int key;	// combined hash key
	string code;	// full entry data
	string city;	// plane maker
	string state;	// plane model
    string data;
};

// hash table class using addititve string hash and mid-square hashing
class airportTable{
private:
	vector <airport> airports;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	airportTable();	// default constructor
	airportTable(int size); // constructor

	// function declarations
	void setData(string code, string city, string state, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int getKey(string data);
	// void update(int x, std::string data);
	bool find(string code, string city, string state);
	void deleteEntry(int x);
	void write();

	// hash function
	int hashStrings(string code, string city, string state);

};