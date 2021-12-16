#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct pilot{
	int key;	// combined hash key
	int ID;	// full entry data
	string name;	// plane maker
	string datehired;	// plane model
	string data;
};

// hash table class using addititve string hash and mid-square hashing
class pilotTable{
private:
	vector <pilot> pilots;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	pilotTable();	// default constructor
	pilotTable(int size); // constructor

	// function declarations
	void setData(int ID, string name, string datehired, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int changeNamebyID(int ID, string name);
	int getKey(string data);
	// void update(int x, std::string data);
	// int find(std::string tuple, std::string tableName);
	void deleteEntry(int x);
	void selectDisplay(string name);
	void write();

	// hash function
	int hashStrings(string name, string datehired);
    int hashInts(int);

};