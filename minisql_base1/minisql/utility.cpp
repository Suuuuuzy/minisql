
#include"utility.h"
#include "B_plus_tree_node.h"


void move_address(Node * source, int address_index_of_source, Node *destination,int address_index_of_destination){
	//move address(actually it moves block) from source to destination, and automatically chages the upper_address pointer

	destination->address[address_index_of_destination]=source->address[address_index_of_source];
	if(source->address[address_index_of_source]!=-1 && source->is_bottom==false)
	{
		Node * t_1=(Node*)source->address[address_index_of_source];
		t_1->up_address=(int)destination;

	}
};