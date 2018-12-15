#include<iostream> 
#ifndef BPTREE_H
#define BPTREE_H

//const int NAME_MAX = 12; //maximum number of characters in the name

class BPtree 
{
    public: 
    	//constructor 
        BPtree() { root = NULL; } //inline 
        
        //destructor
        ~BPtree();
        
        //modification member function
        
        void insert(int itemId, char itemName[], char states[], double itemQty, double itemPri); 
        //pre-condition:the inventory doesnt currently contains the value itemId
        //Post-condition:a new item is added to the inventory
        
        void remove(int itemId);
        //pre-condition: The inventory contains the value itemId
		//post-condition: itemId has been removed from the inventory
        
        double calcVal(); 
        //post-conditon: the total value of the inventory is returned 

        bool isEmpty(){return root == NULL;}
        //post-condition:If the invoking BPtree is empty, returns true OTHERWISE false
        
        bool isPresent(int itemId); 
        //post-condtion:if the target ID is present, returns true OTHERWISE false
         
        char* getName(int itemId); 
        //post-condition: the name of the itemId is returned

        char* getStates(int itemId); 

        double getQuantity(int itemId);
        //post-condition: the total quantity of an itemId is returned 
        
        double getPrice(int itemId);
        //post-condition: The price of the itemId is returned
        
        friend std::ostream &operator << (std::ostream& out_s, BPtree& t);
		//post-condition: The contents of the inventory have been written to the output stream out_s 
        
 
    private: 
    //private data members
        struct Node 
        { 
            int id; 
            char name[NAME_MAX]; 
            char states[NAME_MAX]; 
            double quantity; 
            double price; 
            Node* left; 
            Node* right; 
        }; 
        Node* root; 
        
        //private member functions
		void destroy(Node*r);
		// Post: The tree or sub-tree is deleted 
        void help_insert(Node* &r, int itemId, char itemName[], char states[], double itemQty, double itemPri); 
        double help_calcVal(Node* r); 
        void help_remove(Node *&r, int itemId);
        void remove_node(Node *&r);
        Node* getNode(int itemId); 
        // Pre-condition: the node being searched for does exist 
		// Post-condition: the pointer to the node containing itemId is returned 
        void printInventory(std::ostream& out_s, Node*p); 
}; 
#endif 
 

