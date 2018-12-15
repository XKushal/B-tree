#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "bplustreemk4.h"
#include "bplustreemk4.cpp"
using namespace std;
string dir = "C:\\Users\\reali\\Desktop\\CSCI\\us_postal_codesn+.txt";
//string dir = "C:\\Users\\reali\\Downloads\\drive-download-20181213T164829Z-001\\us_postal_codesn+.txt";
int main() {
	/*Due to the lack of time this is implemented staticly*/
	bplustreemk4 test = bplustreemk4(dir);
	return 0;
}