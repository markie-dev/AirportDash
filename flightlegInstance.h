#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct flightlegInstance{
	int key;	// combined hash key
	string seq;	// full entry data
	string FLNO;	// plane maker
	string fdate;	// plane model
	string ActDept;
    string ActArr;
    string pilot;
    string data;
};

// hash table class using addititve string hash and mid-square hashing
class flightleginstanceTable{
private:
	vector <flightlegInstance> flightLegInstances;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	flightleginstanceTable();	// default constructor
	flightleginstanceTable(int size); // constructor

	// function declarations
	void setData(string seq, string FLNO, string fdate, string ActDept, string ActArr, string pilot, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int getKey(string data);
	// void update(int x, std::string data);
	bool find(string seq, string FLNO, string fdate, string ActDept, string ActArr, string pilot);
	void deleteEntry(int x);
	void write();

	// hash function
	int hashStrings(string seq, string FLNO, string fdate, string ActDept, string ActArr, string pilot);

};