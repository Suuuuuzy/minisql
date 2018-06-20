



#ifndef B_PULS_TREE_NODE_H__


#define B_PULS_TREE_NODE_H__



#define  MAX_KEY_NUMBER 4 //MAX_KEY_NUMBER should be at least larger than 5(that's the safest guess)
// this had to be set as an even, due to some efficiency problems concerning the spliting process

#define NODE_DEBUG 0

#include <iostream>
#include"Global_definition.h"
struct node_key{

	int type_int;
	float type_float;
	//char type_char;//this one has an error!

};
class Node{
	/*
	* This is the node of B+ tree that satisfy following properties: 
	* for every delete, the node will automatically be repacked to make it compact
	*/
public:

	bool is_bottom;//whether this node is bottom node
	bool is_root;//whether this node is root node
	int up_address;
	node_key* key; //node at all keys
	int* address; //pointer at all pointers(to node)
	short contain_node;//calculate the number of node it contains, the number of key, not the number of pointer
	~Node();

	void DisplayThisKey(short type);
	void RecursiveDisplayThisKey(short type,int depth);
	bool Get_root_bottom_same();
	void Set_root_bottom_same();
	Node();
	void InsertKey(node_key key_in,short type, int address_in,int test_signal  );
	void DeleteKey(node_key key_in,short type);
private:
	bool root_bottom_same; //indicate whether this one is both bottom and head, false for no, true for yes
	inline bool  compare_key(node_key key_1,node_key key_2,short type);
	inline bool  same_key(node_key key_1,node_key key_2,short type);
	//inline static void  move_address(Node * source, int address_index_of_source, Node *destination,int address_index_of_destination);
	void add_or_split(node_key key_in,short type, int address_in,int test_singal);//key_in: the key to be added
	//type: the type of key to be added
	//address_in: the address to be added
	void delete_or_merge(node_key key_in,short type);//key_in: the key to be deleted
};




inline bool Node::compare_key(node_key key_1,node_key key_2,short type)
{
	/* check whether key_1 is less than key_2 */
	switch(type)
	{
	case TYPE_INT:  return key_1.type_int<key_2.type_int;
	case TYPE_FLOAT:  return key_1.type_float<key_2.type_float;
		//	case TYPE_CHAR:  return key_1.type_char<key_2.type_char;
	default: std::cout<<"Fatal error!, Unexpected type in compare_key"<<std::endl;break;
	}
	return false;

}
 
inline bool Node::same_key(node_key key_1,node_key key_2,short type)
{
	/* check whether key_1 is less than key_2 */
	switch(type)
	{
	case TYPE_INT:  return key_1.type_int==key_2.type_int;
	case TYPE_FLOAT:  return key_1.type_float==key_2.type_float;
		//	case TYPE_CHAR:  return key_1.type_char==key_2.type_char;
	default: std::cout<<"Fatal error!, Unexpected type in same_key"<<std::endl;break;
	}
	return false;

}
/*
inline  void   Node::move_address(Node * source, int address_index_of_source, Node *destination,int address_index_of_destination)
{
	destination->address[address_index_of_destination]=source->address[address_index_of_source];
	if(source->address[address_index_of_source]!=-1 && source->is_bottom==false)
	{
		Node * t_1=(Node*)source->address[address_index_of_source];
		t_1->up_address=(int)destination;

	}

}
*/
#endif
