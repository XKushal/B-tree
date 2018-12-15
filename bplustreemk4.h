#pragma once
#include <string>
#include <sstream>
#include <vector>
using namespace std;
struct kp {
	string key;
	int value;

	kp(string nkey,int value) {
		this->key = nkey;
		this->value = value;
	}
	void setValue(int nValue) {
		this->value = nValue;
	}
	int getValue() {
		return this->value;
	}
	
};
struct sequenceB {
	int nextPointer;
	int prevPointer;
	vector<string> seqeunce;

	sequenceB() {

	}
	sequenceB(int prev,string item) {
		this->prevPointer = prev;
		this->seqeunce.push_back(item);
	}
	void setNext(int next){
		this->nextPointer = next;
	}
	string writeToFile() {
		string temp;
		stringstream ss(temp);
		temp.push_back('s');
		//temp.push_back('|');
		//temp.push_back(prevPointer);
		temp.push_back('|');
		for (int i = 0; i < seqeunce.size(); i++) {
			for (int x = 0; x < seqeunce.at(i).size(); x++) {
				temp.push_back(seqeunce.at(i).at(x));
			}
			//ss << seqeunce.at(i);
			//cout << "What is going into the sequence " << seqeunce.at(i) << endl;
			//ss >> temp;
		}
		//cout << "THE LAST ITEM IN THE SEQEUENCE " << seqeunce.at(2)<<endl;
		//cout << "THE SIZE OF THE SEQUENCE BLOCK " << seqeunce.size() << endl;
		temp.push_back('|');
		temp.push_back(nextPointer);
		temp.push_back('|');
		//cout << "WHAT IS BEING RETURNED TO BE PRINTED " << temp << endl;
		//for (int i = 0; i < seqeunce.size(); i++) {
		//	cout << "IN THE SEQUENCE " << seqeunce.at(i) << endl;
		//}
		return temp;
	}

};
struct indexB {
	int nextPointer;
	int prevPointer;
	vector<kp> seqeunce;

	indexB() {

	}
	indexB(int prev, kp item) {
		this->prevPointer = prev;
		this->seqeunce.push_back(item);
	}
	void setNext(int next) {
		this->nextPointer = next;
	}
	string writeToFile() {
		string temp;
		stringstream ss(temp);
		temp.push_back('i');
		temp.push_back('|');
		for (int i = 0; i < seqeunce.size(); i++) {
			ss >> temp;
		}
		temp.push_back('|');
		return temp;
	}

};
class bplustreemk4 {

private:
	//Header Record Variables
	int headerSize;
	int insertFlag;
	int blockSize ;
	int indexBlockSize;
	int totalSequnceBlocks;
	int totalIndexBlock;
	int numAvalBlocks;//Number of open blocks
	int numOfLevels;
	string header;
	int rbnRoot; //Relative offest to root node
	int rbnLevels;//Relative offset to levels
	int rbnAvailList;//Relative offset to the avial list
	int totalNumRecords;//total number of records
	int sizeofRecords;
	int fieldsPerRecord;
	vector<string> sizePerfield;
	vector<char> labelPerfield;
	int sortField;
	string description;
	string time;
	string lastMod;
	string dir;
public:
	bplustreemk4();
	bplustreemk4(string directory);
	void processFile();
	void cleanUp();
};