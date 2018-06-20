


#ifndef B_PULS_TREE_H__
#define B_PULS_TREE_H__


#include"B_plus_tree_node.h"



class B_plus_tree{


public:
	

	
	B_plus_tree(short type);

	bool InsertNodeWithKey(node_key key_in,short type, int address_in,int test_signal);//It's from head
	bool DeleteWithKey(node_key key_in,short type);//It's from head
	void DisplayAllValue();
	void DisplayFromLeftToRight();
	void DisplayHead();
private:
	Node * head;
	Node * left;
	short type;
};



#endif