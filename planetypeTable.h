#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct planeType{
	int key;	// combined hash key
	string data;	// full entry data
	string maker;	// plane maker
	string model;	// plane model
    int fspeed; // flying speed
    int gspeed; // ground speed
};

// hash table class using addititve string hash and mid-square hashing
class planeTypeTable{
private:
	vector <planeType> planeTypes;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	planeTypeTable();	// default constructor
	planeTypeTable(int size); // constructor

	// function declarations
	void setData(string maker, string model, int fspeed, int gspeed, string data);
	
	// // operation functions
	int insert(string tuple, string tableName);
	void display();
	int getKey(string data);
	// void update(int x, std::string data);
	// int find(std::string tuple, std::string tableName);
	void deleteEntry(int x);
	void write();

	// hash function
	int hashStrings(string maker, string model);
    int hashInts(int);

};