

#include<iostream>
#include"B_plus_tree.h"
#include"Global_definition.h"

B_plus_tree::B_plus_tree(short type){
	head=new Node();//create a bumpy node as head
	left=head;
	head->is_bottom=true;
	head->is_root=true;
	head->Set_root_bottom_same();
	if(type!=TYPE_INT&&type!=TYPE_FLOAT&&type!=TYPE_CHAR)
	{
		std::cout<<"Fatal Error!Unmatched type in B_plus_tree()"<<std::endl;
		return;
	}
	this->type=type;
}


bool B_plus_tree::InsertNodeWithKey(node_key key_in,short type, int address_in,int test_signal){
	if(type!=this->type)
	{
		std::cout<<"Error!Type doesn't match in InsertNodeWithKey, tree type is "<<this->type<<" input type is"<<type<<std::endl;
		return false;
	}

	if(head==NULL)
	{
		std::cout<<"Fatal Error in InsertNodeWithKey, head is NULL"<<std::endl;
		return false;
	}
	head->InsertKey(key_in,type, address_in,test_signal);
	if(head->Get_root_bottom_same()==false)
	{
		Node * t=(Node *)head->address[0];

		while(t->is_bottom==false)
		{
			// if current t is not bottom, goes to the next one
			t=(Node *)(t->address[0]);
		}
		left=t;
	}
	else{
		left=head;

	}
	return true;
}
void B_plus_tree::DisplayHead(){
	std::cout<<"Head start: ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
	head->DisplayThisKey(type);
	std::cout<<"Head finish: ~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

}
void B_plus_tree::DisplayAllValue(){
	std::cout<<std::endl<<"Start : Display all values &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
	if(head!=NULL)
	{
		head->RecursiveDisplayThisKey(type,0);
		/*
		Node * current_search=head;
		Node * temp_search=NULL;
		for(int i=0;i<current_search->contain_node;i++)
		{
			temp_search=(Node*)(current_search->address[i]);
			current_search->DisplayThisKey(type);
		}
		*/
	}
	std::cout<<"Finish : Display all values &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
}

bool B_plus_tree::DeleteWithKey(node_key key_in,short type){

	if(type!=this->type)
	{
		std::cout<<"Error!Type doesn't match in InsertNodeWithKey, tree type is "<<this->type<<" input type is"<<type<<std::endl;
		return false;
	}

	if(head==NULL)
	{
		std::cout<<"No insert, cannot delete"<<std::endl;
		return false;
		//no insert, cannot delete
		return false;
	}
	//std::cout<<"Before head"<<(int)head<<std::endl;
	head->DeleteKey(key_in,type);
	//std::cout<<"After head"<<(int)head<<std::endl;
	//std::cout<<"head situation, is_bottom: "<<head->is_bottom<<"is_root: "<<head->is_root<<std::endl;
	head->Set_root_bottom_same();
	if(head->Get_root_bottom_same()==false)
	{
		Node * t=(Node *)head->address[0];

		while(t->is_bottom==false)
		{
			// if current t is not bottom, goes to the next one
			t=(Node *)(t->address[0]);
		}
		left=t;
	}
	else{
		left=head;

	}
    return  true;
}

void B_plus_tree::DisplayFromLeftToRight(){
	Node * current=left;
	int i=0;
	std::cout<<std::endl;
	std::cout<<"Start : Left To Right Tree &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
	while(1)
	{
		std::cout<<"Node number: "<<i<<" ";
		current->DisplayThisKey(type);
		if(current->address[MAX_KEY_NUMBER]==-1)
			break;
		current=(Node *)(current->address[MAX_KEY_NUMBER]);
		i++;
	}
	std::cout<<"Finish : Left To Right Tree &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
    
    
    
}
