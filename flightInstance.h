#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct flightInstance{
	int key;	// combined hash key
	string FLNO;	// plane maker
	string fdate;	// plane model
    string data;
};

// hash table class using addititve string hash and mid-square hashing
class flightInstanceTable{
private:
	vector <flightInstance> flightInstances;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	flightInstanceTable();	// default constructor
	flightInstanceTable(int size); // constructor

	// function declarations
	void setData(string FLNO, string fdate, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int changefdate(string FLNO, string fdate);
	// void update(int x, std::string data);
	bool find(string FLNO, string fdate);
	void deleteEntry(string data);
	void selectDisplay(string name);
	void write();

	// hash function
	int hashStrings(string FLNO, string fdate);

};