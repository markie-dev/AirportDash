#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct passenger{
	int key;	// combined hash key
	int ID;	// full entry data
	string name;	// plane maker
	string phone;	// plane model
    string data;
};

// hash table class using addititve string hash and mid-square hashing
class passengerTable{
private:
	vector <passenger> passengers;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	passengerTable();	// default constructor
	passengerTable(int size); // constructor

	// function declarations
	void setData(int ID, string name, string phone, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int changePhoneNum(string ID, string name, string phone);
	// void update(int x, std::string data);
	// int find(std::string tuple, std::string tableName);
	void deleteEntry(string data);
	void write();

	// hash function
	int hashStrings(string name, string phone);
    int hashInts(int);

};