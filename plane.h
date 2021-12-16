#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct to hold plane type data
struct plane{
	int key;	// combined hash key
	int ID;	// full entry data
	string maker;	// plane maker
	string model;	// plane model
    string lastmaint;
    string lastmainta;
	string data;
};

// hash table class using addititve string hash and mid-square hashing
class planeTable{
private:
	vector <plane> planes;	// vector of plane types to hold data
	int bucket;	// number of buckets
	
public:
	planeTable();	// default constructor
	planeTable(int size); // constructor

	// function declarations
	void setData(int ID, string maker, string model, string lastmaint, string lastmainta, string data);
	
	// // operation functions
	int insert(std::string tuple, std::string tableName);
	void display();
	int getKey(string data);
	// void update(int x, std::string data);
	// int find(std::string tuple, std::string tableName);
	void deleteEntry(int x);
	void write();

	// hash function
	int hashStrings(string maker, string model, string lastmaint, string lastmainta);
    int hashInts(int);

};