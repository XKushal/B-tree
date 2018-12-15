#include <iostream> 
#include <cstring> 
#include <iomanip> 
#include "BPtree.h" 
 
//destructor
BPtree::~BPtree()
{
	destroy(root);
} 

// Deletes the BPtree tree 
void BPtree::destroy(Node*r) 
{ 
    if(r != NULL) 
    { 
        destroy(r->left); 
        destroy(r->right); 
        delete r; 
    } 
} 

// Adds a new item to an the inventory
void BPtree::insert(int itemId, char itemName[], char states[], double itemQty, double itemPri) 
{ 
    help_insert(root, itemId, itemName, states, itemQty, itemPri);
}

void BPtree::help_insert(Node* &r, int itemId, char itemName[], char states[], double itemQty, double itemPri) 
{ 
    if (r == NULL) 
    { 
        r = new Node; 
        r->id = itemId;
		//as both being the string, just-read name is copied to the 
		//node r in name section 
        strcpy(r->name, itemName); 
        strcpy(r->states, states); 
        r->quantity = itemQty; 
        r->price = itemPri; 
        r->left = NULL; 
        r->right = NULL; 
    }
    else if (itemId < r->id) 
        help_insert(r->left, itemId, itemName, states, itemQty, itemPri); 
    else 
        help_insert(r->right, itemId, itemName, states, itemQty, itemPri); 
} 

//removes the item from the inventory
void BPtree::remove(int itemId)
{
	help_remove(root, itemId);
}

void BPtree::help_remove(Node *&r, int itemId)
{
	if(r->id == itemId)
		remove_node(r);
	else if(itemId < r->id)
		help_remove(r->left, itemId);
	else
		help_remove(r->right, itemId);
}

void BPtree::remove_node(Node *&r)
{
	Node*ptr;
	Node*back;
	if(r->left==NULL && r->right==NULL)
	{
		delete r;
		r=NULL;
	}
	else if(r->left==NULL)
	{
		ptr=r;
		r=r->right;
		delete ptr;
	}
	else if(r->right==NULL)
	{
		ptr=r;
		r=r->left;
		delete ptr;
	}
	else
	{
		back=r;
		ptr=r->right;
		while(ptr->left!=NULL)
		{
			back=ptr;
			ptr=ptr->left;
		}
		r->id = ptr->id;
		if(back==r)
			remove_node(back->right);
		else
			remove_node(back->left);
	}
}

//returns the total value of the inventory
double BPtree::calcVal() 
{ 
    return help_calcVal(root);
}

double BPtree::help_calcVal(Node* r) 
{ 
    if (r != NULL)
    {
    	return ( (r->price * r->quantity) + 
		help_calcVal(r->left) + 
		help_calcVal(r->right) );
	}    
	else 
        return 0;
}

//returns the node containing itemId
BPtree::Node* BPtree::getNode(int itemId) 
{ 
    Node* r = root; 
    while (itemId != r->id) 
    { 
        if (itemId < r->id) 
            r = r->left; 
        else
	        r = r->right; 
    } 
    return r; 
} 

// returns the name of a particular item 
char* BPtree::getName(int itemId) 
{ 
    Node* r = getNode(itemId); 
    return r->name;
} 

char* BPtree::getStates(int itemId) 
{ 
    Node* r = getNode(itemId); 
    return  r->states; 
} 

// returns the price of a particular item 
double BPtree::getPrice(int itemId) 
{ 
    Node* r = getNode(itemId); 
    return r->price; 
} 

// returns the quantity of a particular item 
double BPtree::getQuantity(int itemId) 
{ 
    Node* r = getNode(itemId); 
    return r->quantity; 
} 


//returns TRUE if item is present, FALSE otherwise 
bool BPtree::isPresent(int itemId) 
{ 
    Node *r;
	r = root; 
    while (true)//r != NULL 
    {
		if(r == NULL)
			return false; 
        else if (itemId == r->id) 
            return true; 
        else if (itemId < r->id) 
            r = r->left; 
        else 
            r = r->right; 
    }  
} 
 
//contents of the inventory is returned to the terminal
std::ostream &operator << (std::ostream& out_s, BPtree& t) 
{ 
    t.printInventory(out_s, t.root); 
    return out_s; 
} 

void BPtree::printInventory(std::ostream& out_s, Node*r) 
{ 
    if (r != NULL) 
    { 
        printInventory(out_s, r->left); 
        out_s << std::right<< std::setw(5)<< r->id<< std::setw(7) << "  ";               
		out_s << std::left<< std::setw(12)<< r->name; 
        out_s << std::right<< std::setw(2)<< r->states<<std::setw(1)<<"  "; 
        out_s << std::right<< std::setw(8)<< r->quantity<<std::setw(3)<<"  "; 
        out_s << std::right << std::setw(8) << std::fixed;
        out_s << std::setprecision(2) << r->price << "\n"; 
        printInventory(out_s, r->right);
    } 
} 






