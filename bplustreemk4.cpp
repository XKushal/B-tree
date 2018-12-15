#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "bplustreemk4.h"
using namespace std;

bplustreemk4::bplustreemk4(string dir) {
	//ofstream out;
	fstream myfile;
	this->dir = dir;
	string header;
	string headerout;
	myfile.open(dir, ios::in);
	myfile >> this->headerSize;
	getline(myfile, header);
	cout << header << endl;
	this->header = header;
	int fieldcount = 0;
	int count = 0;
	//a "different" way to read data in because it wasnt working
	for (int i = 1; i < this->headerSize - 2; i++) {
		if (header.at(i) == '|') {
			cout << "encounter a field marker" << endl;
			fieldcount++;
			string temp;
			for (int x = i - count; x < i; x++) {
				temp.push_back(header.at(x));
			}
			if (fieldcount == 1) {
				this->insertFlag = stoi(temp);
			}
			if (fieldcount == 2) {
				this->totalNumRecords = stoi(temp);
			}
			if (fieldcount == 3) {
				this->sizeofRecords = stoi(temp)-1;
			}
			if (fieldcount == 4) {
				this->fieldsPerRecord = stoi(temp);
			}
			if (fieldcount == 5) {
				cout << "temp aka what ever we have deemed a field " << temp;
				/*vector<string> temp2;
				for (int y = 0; y < temp.size(); y++) {

				}*/
				vector<string> temp2;
				string buffer;
				stringstream ss(buffer);
				for (int y = 0; y < temp.size(); y++) {
					ss.clear();
					ss << temp.at(y);
					//cout << "Went into the string stream" << temp.at(y) << endl;
					ss >> buffer;
					//cout << "THIS IS WHAT IS IN THE BUFFER  " << buffer << endl;
					if (buffer != "\"" || buffer != "(" || buffer != ")") {
						temp2.push_back(buffer);
					}
				}
				this->sizePerfield = temp2;
			}
			if (fieldcount == 6) {
				vector<char> temp3;
				for (int y = 0; y < temp.size(); y++) {
					if (temp.at(y) != '"'|| temp.at(y)!='(' || temp.at(y) != ')') {
						temp3.push_back(temp.at(y));
					}

				}
				this->labelPerfield = temp3;
			}
			if (fieldcount == 7) {
				this->sortField = stoi(temp);
			}
			if (fieldcount == 8) {
				this->description = temp;
			}
			count = 0;
			i++;
			
		}
		count++;
	}
	myfile.close();
	this->rbnRoot = this->header.size();
	//debugging
	cout << this->headerSize << endl;
	cout << this->totalNumRecords << endl;
	cout << this->description << endl;

	cleanUp();
	processFile();
}
bplustreemk4::bplustreemk4() {

}
void bplustreemk4::processFile() {
	ofstream outfile;
	fstream myfile;
	myfile.open(this->dir);
	outfile.open("btree.dat");
	outfile << this->header;
	sequenceB sb;
	indexB ib;
	//pair temp;
	int nextP=0;
	int preP=0;
	this->totalSequnceBlocks = 0;
	string tempLine;
	while (getline(myfile, tempLine)) {
		string zip;
		if (tempLine.size() != this->sizeofRecords) {
			cout << "Line that was not big enough dected." << endl;
			continue;
		}
		else {
			cout << "The line is of valid lenghth " << endl;
			zip = tempLine.substr(0, 5);
			cout << " The zip is " << zip << endl;
			sb.nextPointer = this->headerSize + (this->blockSize * this->totalSequnceBlocks);
			cout << "Next pointer is " << sb.nextPointer << endl;
			cout << "pushing back this : " << tempLine << endl;
			sb.seqeunce.push_back(tempLine);
			cout << " SEQUENCE SIZE BEFORE ADDING " << sb.seqeunce.size() << endl;
			ib.seqeunce.push_back(kp(zip, (this->headerSize + this->totalSequnceBlocks * 249)));
			if (sb.seqeunce.size() == 3) {
				this->totalSequnceBlocks++;
				//cout << "this is what is in the sequence block " << sb.writeToFile() << endl;
				outfile << sb.writeToFile();
				sb.seqeunce.clear();
				continue;
			}
			if (ib.seqeunce.size() == this->indexBlockSize-1 ) {
				this->totalIndexBlock++;
				cout << "this is what is in the Index block " << ib.writeToFile() << endl;
				outfile << ib.writeToFile();
				ib.seqeunce.clear();
				continue;
			}
			//cout << "The sequence size after adding " << sb.seqeunce.size() << endl;
		}
	}
	outfile.close();
	myfile.close();
	cout << this->sizeofRecords << endl;
}
void bplustreemk4::cleanUp() {
	vector<string> tempf;
	string temp;
	for (int i = 0; i < this->sizePerfield.size(); i++) {
		if (this->sizePerfield.at(i) != "\"" && this->sizePerfield.at(i) != "(" && this->sizePerfield.at(i) != ")") {
			cout << this->sizePerfield.at(i);
			tempf.push_back(this->sizePerfield.at(i));
		}	
	}
	this->sizePerfield = tempf;
	cout << endl;
	for (int i = 0; i < this->labelPerfield.size(); i++) {
		cout << this->labelPerfield.at(i);
	}
}