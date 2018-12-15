#include <iostream> 
#include <fstream> 
#include <iomanip>
#include <cstdlib>
#include <cstring>  
#include <string> 
#include "BPtree.h"
#include "BPtree.cpp"

using namespace std; 

const int MAX=12;//maximum size of the filename
void showMenu();//this fucntion shows the menu when called

//this function reads the file and adds read inventory's items into BPtree
void readInputFilename(ifstream& infile, BPtree &t);

//this function exits the function leaving some comment if user tries 
//to insert the item already present in the inventory,if not inserts 
//the item's id, name, quantity and price into the inventory when called
void insertItem(BPtree &t); 

//this fucntion takes id of an item from an user and reports the 
//info of item like item's name, quantity and price if it is present in 
//inventory, ELSE report not found to the console
void reportItemInfo(BPtree &t,int number);

//this fucntion prints the whole inventory to the console
// void print(BPtree &t, ofstream& outfile);
void print(BPtree &t);

int main() //main fucntion
{    
    BPtree t;    
    ifstream infile;
    ofstream outfile;
	int number;   
	char choice; 
    showMenu(); 
    while (choice != 'q')
	{         
		cout << "--> ";         
		cin >> choice;         
		switch (choice)         
		{ 	               
			case 'f': readInputFilename(infile, t); //Reads the items from the file                 
		              break;             
					  
			case 'i': insertItem(t); // Insert an item into the inventory                              
					  break;             
					  
			case 'r': cout<<" records to delete: ";
					  cin >> number;                                   
					  t.remove(number); // remove an item from the inventory                          
					  break;      
					  
			case 'e': if(t.isEmpty()==true)
						cout<<" The list is empty. \n";
					  else
					  	cout<<" The list is not empty. \n";
					  break;
					  
			case 'a': cout<<" the informationn related to this zip code: ";
					  cin >> number;                                   
					  reportItemInfo(t, number); // Reports an item's information           
					  cout << "\n";                 
					  break;                      

			case 'p': print(t); // Prints the inventory to the terminal                                  
					  break;  

			case 'h': showMenu(); // Displays the menu                                  
					  break;             
					  
			case 'q': break; // Exits program 
								  
			default:  cout << " Invalid command.  Type \"h\" to see the menu.\n";                 
					  break; 
        }//switch 
    }//while
}  

void showMenu() 
{
	cout<<"This program responds to the following commands to \n";
	cout<<"manipulate an BPtree, which is initially empty.\n";
	cout<<"The commands prompt for additional information, if necessary.\n";
	cout<<endl;
    cout<< "    f  -- Read an BPtree from a file.\n"; 
    cout<< "    i  -- insert an item into the BPtree.\n";
    cout<< "    r  -- remove an item from the BPtree.\n";
    cout<< "    e  -- Report if the tree is empty.\n";
    cout<< "    a  -- Report item's information through zip code.\n";
    cout<< "    p  -- Print the tree to the terminal.\n"; 
    cout<< "    h  -- See this menu.\n"; 
    cout<< "    q  -- Quit the program.\n";
} 

void readInputFilename(ifstream& infile, BPtree &t) 
{ 
    const int NAMESIZE = 20;
    char input_filename[NAMESIZE],name[MAX], states[MAX];  
    int number;
    double quantity; 
    double price;
    cout << "Enter file name: "; 
    cin >> input_filename; 
    infile.open(input_filename); 
    if(!infile)
    {
    	cout<<"cannot open the name of the input file.\n";
    	infile.close();  
        infile.clear();  
        return ; 
	}
    while (!infile.eof()) 
    { 
    
        infile >> number; 
        infile >> name; 
        infile >> states;
        infile >> quantity;  
        infile >> price;
        t.insert(number, name, states, quantity, price); 
    } 
    infile.close(); 
} 
 
void insertItem(BPtree &t) 
{ 
    int number; 
    char name[MAX]; 
    char states[MAX]; 
    double quantity; 
    double price; 
    cout << "Enter the description of the record:\n";
	cout << "  zip Code:   "; 
    cin >> number; 
    if (!t.isPresent(number)) 
    { 
    	cout << "  Name:     "; 
    	cin >> name; 
    	cout << "  States:     "; 
    	cin >> states; 
    	cout << "  Longitute: "; 
    	cin >> quantity; 
    	cout << "  Latutude:    "; 
    	cin >> price; 
    	t.insert(number, name, states, quantity, price); 
    }
    else
    	cout<<" Couldnt find th zip code\n";
} 

void reportItemInfo(BPtree &t, int number) 
{ 
	if (t.isPresent(number))
	{
		cout << "  " << left << setw(12) << "Name:";
		cout << t.getName(number) << "\n  ";
		cout << left << setw(12) << "States:";
		cout << t.getStates(number)<<"\n  ";
		cout << left << setw(12) << "Longitute:";
		cout << t.getQuantity(number) << "\n  ";
		cout << left << setw(12) << "Latutude:";
		cout << t.getPrice(number); 
	}
	else
		cout<<" Couldnt find the record.\n";
}
 

 
void print(BPtree &t) 
{ 
    cout<< left << setw(9) << "Zip Code";
	cout<< left << setw(12) << "   Name";
	cout<< left << setw(8) << " States";
	cout<< left << setw(7) << "Longitute";
	cout<< right << setw(8) << "  Latitude"; 
    cout<< "\n------------------------------------------------\n";
	cout<< t; 
    cout<< "------------------------------------------------\n"; 
}





 
