
#include"B_plus_tree_node.h"

#include <stdio.h>
#include <iostream>
#include"utility.h"

Node::Node()
{
	/* initialization of this node 
	* allocate new spaces in heap
	* set all pointer to null 
	*/
	key=new node_key [MAX_KEY_NUMBER];
	address=new int [MAX_KEY_NUMBER+1];
	memset(key,0,sizeof(node_key)*MAX_KEY_NUMBER);
	memset(address,-1,sizeof(int)*(MAX_KEY_NUMBER+1));
	is_bottom=false;
	is_root=false;
	up_address=-1;
	contain_node=0;
}
Node::~Node(){

	delete  key;
	delete  address;

}
void Node::DisplayThisKey(short type){
	// this is to show the information of node, efficiency can be improved, but not necessary


	std::cout<< std::endl<<"Start to display key value in this node ********"<< std::endl;
	//cout<<"A "<<address[0]<<"  ";
	for(int i=0;i<contain_node;i++)
	{

		switch(type){
			case TYPE_INT:std::cout<<"K "<<key[i].type_int<<" ";break;
			case TYPE_FLOAT:std::cout<<"K "<<key[i].type_float<<" ";break;
	//		case TYPE_INT:cout<<"K "<<key[i].type_int<<" "<<"A "<<address[i+1]<<"  ";break;
	//		case TYPE_FLOAT:cout<<"K "<<key[i].type_float<<" "<<"A "<<address[i+1]<<"  ";break;
			//		case TYPE_CHAR:cout<<"K"<<key[i].type_char<<" ";break;
		default:std::cout<<"Fatal error! Type not matched in DisplayThisKey"<< std::endl;
		}
	}
	std::cout<< std::endl;
	std::cout<<"Current contain: "<<contain_node<< std::endl;
	std::cout<<"Current root: "<<is_root<< std::endl;
	std::cout<<"Current bottom: "<<is_bottom<< std::endl;
	std::cout<<"Up address: "<<up_address<< std::endl;
	std::cout<<"this address: "<<(long)this<< std::endl;
	if(is_bottom==true)
		std::cout<<"Tail record address: "<<address[MAX_KEY_NUMBER]<< std::endl;
	std::cout<<"Finish to display key value in this node ********"<< std::endl;
	std::cout<< std::endl;
	return;
	/*
	Node * current_search=NULL;
	for(int i=0;i<=contain_node;i++)
	{
	current_search=(Node*)address[i];
	current_search->DisplayThisKey(type,depth+1);
	}
	*/
}

void Node::RecursiveDisplayThisKey(short type,int depth){
	// this is to show the information of node, efficiency can be improved, but not necessary


	//cout<<endl<<"Start to display key value in this node ********"<<endl;
	std::cout<<"Depth : "<<depth<< std::endl;
	//cout<<"A "<<address[0]<<"  ";
	for(int i=0;i<contain_node;i++)
	{

		switch(type){
			case TYPE_INT:std::cout<<"K "<<key[i].type_int<<" ";break;
			case TYPE_FLOAT:std::cout<<"K "<<key[i].type_float<<" ";break;
		//	case TYPE_INT:cout<<"K "<<key[i].type_int<<" "<<"A "<<address[i+1]<<"  ";break;
		//	case TYPE_FLOAT:cout<<"K "<<key[i].type_float<<" "<<"A "<<address[i+1]<<"  ";break;
			//		case TYPE_CHAR:cout<<"K"<<key[i].type_char<<" ";break;
		default:std::cout<<"Fatal error! Type not matched in DisplayThisKey"<< std::endl;
		}
	}

	std::cout<< std::endl;
	std::cout<<"Current contain: "<<contain_node<< std::endl;
	std::cout<<"Current root: "<<is_root<< std::endl;
	std::cout<<"Current bottom: "<<is_bottom<< std::endl;
	std::cout<<"Up address: "<<up_address<< std::endl;
	std::cout<<"this address: "<<(long)this<< std::endl;
	if(is_bottom==true)
		std::cout<<"Tail record address: "<<address[MAX_KEY_NUMBER]<< std::endl;
	std::cout<<"Finish to display key value in this node ********"<< std::endl;
	std::cout<< std::endl;
	if(is_bottom==true)
		return;

	Node * current_search=NULL;
	for(int i=0;i<=contain_node;i++)
	{
		current_search=(Node*)address[i];
		current_search->RecursiveDisplayThisKey(type,depth+1);
	}

}


bool Node::Get_root_bottom_same()
{
	return root_bottom_same;
}

void Node::Set_root_bottom_same()
{

	if(is_bottom==true && is_root==true)
	{
		root_bottom_same=true;
	}
}
void Node::add_or_split(node_key key_in,short type, int address_in,int test_signal)
{
	if(is_bottom==true)
	{
		for(int i=0;i<contain_node;i++)
		{
			if(same_key(key_in,key[i],type)==true)
				//no need to add
				return;

		}
	}
	if(contain_node<MAX_KEY_NUMBER)
	{
		//if this node is not full
		int flag=(is_bottom==true)?0:1;

		//not bottom
		int i;
		for(i=0;i<contain_node;i++)
		{

			if(compare_key(key_in,key[i],type))
			{
				for(int j=contain_node;j>i;j--)
				{
					address[j+flag]=address[j-1+flag];
					key[j]=key[j-1];
				}
				address[i+flag]=address_in;
				key[i]=key_in;
				contain_node++;
				return;

			}

		}
		address[i+flag]=address_in;
		key[i]=key_in;
		contain_node++;

	}
	else{
		// if we need to split

		if(is_root==true)
		{

			//if current one is root
			Node* new_sibling_left=new Node();
			Node* new_sibling_right=new Node();

			if(is_bottom== true)
			{
				root_bottom_same=false;
				if(NODE_DEBUG==1)
					std::cout<<"\nROOT+BOTTOM split"<< std::endl;
				is_bottom=false;
				int i0=-1;
				for(int i=0;i<MAX_KEY_NUMBER;i++)
				{
					if(compare_key(key_in,key[i],type))
					{
						i0=i;
						break;
					}
				}
				bool insert_in_left=(i0==-1 || i0>=(MAX_KEY_NUMBER>>1)+1)?false:true;//whether we insert in the left subnode
				int t_add=(insert_in_left==false)?1:0; 

				int left_size=(MAX_KEY_NUMBER>>1)+t_add; //key number in the left node, before inserting a new one
				int right_size=MAX_KEY_NUMBER-left_size; //key number in the right node, before inserting a new one
				for(int i=0;i<left_size;i++)
				{
					new_sibling_left->key[i]=key[i];
					//new_sibling_left->address[i]=address[i];
					move_address(this,i,new_sibling_left,i);
				}
				for(int i=0;i<right_size;i++)
				{
					new_sibling_right->key[i]=key[i+left_size];
					//new_sibling_right->address[i]=address[i+left_size];
					move_address(this,i+left_size,new_sibling_right,i);
				}

				/*
				for(int i=original_size;i<MAX_KEY_NUMBER;i++)
				address[i]=-1;
				*/
				new_sibling_left->address[MAX_KEY_NUMBER]=(long)new_sibling_right;
				new_sibling_right->contain_node=right_size;
				new_sibling_left->contain_node=left_size;
				if(insert_in_left==false)
					new_sibling_right->add_or_split(key_in,type,address_in,test_signal);
				else
					new_sibling_left->add_or_split(key_in,type,address_in,test_signal);

				new_sibling_left->up_address=(long)this;
				new_sibling_right->up_address=(long)this;
				new_sibling_left->is_bottom=true;
				new_sibling_right->is_bottom=true;
				memset(address,-1,sizeof(int)*(MAX_KEY_NUMBER+1));
				key[0]=new_sibling_right->key[0];
				address[0]=(long)new_sibling_left;
				address[1]=(long)new_sibling_right;
				contain_node=1;
				if(NODE_DEBUG==1)
					std::cout<<"ROOT+BOTTOM split finish"<< std::endl;
			}
			else{
				if(NODE_DEBUG==1)
					std::cout<<"ROOT, No bottom split"<< std::endl;
				//this one is not a bottom
				int i0=-1;
				for(int i=0;i<MAX_KEY_NUMBER;i++)
				{
					if(compare_key(key_in,key[i],type))
					{
						i0=i;
						break;
					}
				}
				bool insert_in_left=(i0==-1 || i0>=(MAX_KEY_NUMBER>>1)+1)?false:true;//indicate where it inserts the node
				int t_add=(insert_in_left==false)?1:0;

				//new one is in the sibling node
				int left_size=(MAX_KEY_NUMBER>>1)+t_add;
				int right_size=MAX_KEY_NUMBER-left_size;
				if(insert_in_left==false)
					//insert in right
				
					move_address(this,left_size,new_sibling_right,0);
					/*
					new_sibling_right->address[0]=address[left_size];
					if(address[left_size]!=-1)
					{
						Node * t_1=(Node*)address[left_size];
						t_1->up_address=(int)new_sibling_right;

					}*/
				
				else
					// insert in left
				
					move_address(this,left_size,new_sibling_left,left_size);
					/*
					new_sibling_left->address[left_size]=address[left_size];
					if(address[left_size]!=-1)
					{
						Node * t_1=(Node*)address[left_size];
						t_1->up_address=(int)new_sibling_left;

					}*/

				
				for(int i=0;i<left_size;i++)
				{
					new_sibling_left->key[i]=key[i];
					move_address(this,i,new_sibling_left,i);
					/*
					new_sibling_left->address[i]=address[i];
					if(address[i]!=-1)
					{
						Node * t_1=(Node*)address[i];
						t_1->up_address=(int)new_sibling_left;
					}
					*/
				}
				for(int i=0;i<right_size;i++)
				{
					new_sibling_right->key[i]=key[i+left_size];
					move_address(this,i+left_size+1,new_sibling_right,i+1);
					/*
					new_sibling_right->address[i+1]=address[i+left_size+1];
					if(address[i+left_size+1]!=-1)
					{
						Node * t_1=(Node*)address[i+left_size+1];
						t_1->up_address=(int)new_sibling_right;
					}*/
				}
				/*
				for(int i=original_size+1;i<MAX_KEY_NUMBER+1;i++)
				address[i]=-1;
				*/

				new_sibling_right->contain_node=right_size;
				new_sibling_left->contain_node=left_size;
				if(insert_in_left==false)
				{
					new_sibling_right->add_or_split(key_in,type,address_in,test_signal);
					if(address_in!=-1)
					{
						Node * t_1=(Node*)address_in;
						t_1->up_address=(long)new_sibling_right;
					}
				}
				else
				{
					new_sibling_left->add_or_split(key_in,type,address_in,test_signal);
					if(address_in!=-1)
					{
						Node * t_1=(Node*)address_in;
						t_1->up_address=(long)new_sibling_left;
					}

				}
				if(insert_in_left==true)
				{
					new_sibling_right->address[0]=new_sibling_left->address[new_sibling_left->contain_node];
					if(new_sibling_left->address[new_sibling_left->contain_node]!=-1)
					{
						Node * t_1=(Node*)new_sibling_left->address[new_sibling_left->contain_node];
						t_1->up_address=(long)new_sibling_right;
					}
					new_sibling_left->address[new_sibling_left->contain_node]=-1;
				}
				memset(address,-1,sizeof(int)*(MAX_KEY_NUMBER+1));
				if(MAX_KEY_NUMBER%2==0)
				{

					key[0]=new_sibling_left->key[new_sibling_left->contain_node-1];
					//new_sibling_left->address[new_sibling_left->contain_node]=-1;
					new_sibling_left->contain_node--;

				}
				else
					std::cout<<"Inefficient Paramater Setting, please set MAX_KEY_NUMBER as an even "<< std::endl;

				new_sibling_left->up_address=(long)this;
				new_sibling_right->up_address=(long)this;

				address[0]=(long)new_sibling_left;
				address[1]=(long)new_sibling_right;
				/*
				cout<<endl<<"Test left upper$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
				for(int i=0;i<new_sibling_left->contain_node+1;i++)
				{
					Node * t_1= (Node *)new_sibling_left->address[i];
					Node * t_2= (Node *)(t_1->up_address);
					t_2->DisplayThisKey(type);

				}
				
				cout<<endl<<"Test left upper finishes$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
				cout<<endl<<"Test right upper$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
				for(int i=0;i<new_sibling_right->contain_node+1;i++)
				{
					Node * t_1= (Node *)new_sibling_right->address[i];
					Node * t_2= (Node *)(t_1->up_address);
					t_2->DisplayThisKey(type);

				}
				cout<<endl<<"Test right upper finishes$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;*/
				contain_node=1;
				if(NODE_DEBUG==1)
					std::cout<<"ROOT, No bottom split finish"<< std::endl;
			}
		}
		else{

			//if current one is not root

			Node* new_sibling=new Node();

			if(is_bottom== true)
			{
				
				int i0=-1;
				for(int i=0;i<MAX_KEY_NUMBER;i++)
				{
					if(compare_key(key_in,key[i],type))
					{
						i0=i;
						break;

					}
				}
				bool insert_in_this=(i0==-1 || i0>=(MAX_KEY_NUMBER>>1)+1)?false:true;
				int t_add=(insert_in_this==false)?1:0;

				//new one is in the sibling node
				int original_size=(MAX_KEY_NUMBER>>1)+t_add;
				int new_size=MAX_KEY_NUMBER-original_size;
				for(int i=0;i<new_size;i++)
				{
					new_sibling->key[i]=key[i+original_size];
					//new_sibling->address[i]=address[i+original_size];
					move_address(this,i+original_size,new_sibling,i);
				}
				//new_sibling->address[MAX_KEY_NUMBER]=address[MAX_KEY_NUMBER];
				move_address(this,MAX_KEY_NUMBER,new_sibling,MAX_KEY_NUMBER);
				for(int i=original_size;i<MAX_KEY_NUMBER;i++)
					address[i]=-1;

				address[MAX_KEY_NUMBER]=(long)new_sibling;
				new_sibling->contain_node=new_size;
				new_sibling->up_address=up_address;
				new_sibling->is_bottom=true;
				contain_node=original_size;
				if(insert_in_this==false)
					new_sibling->add_or_split(key_in,type,address_in,test_signal);
				else
					add_or_split(key_in,type,address_in,test_signal);
				Node * this_root=(Node*)up_address;
				
				if(test_signal==1)
				{
					std::cout<<"Display this_root$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
				this->DisplayThisKey(type);
				std::cout<<"finish Display this_root$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
				}
				if(test_signal==1)
				{
					std::cout<<"Display upper $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
				this_root->DisplayThisKey(type);
				std::cout<<"Finish display upper $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
				}
				
				this_root->add_or_split(new_sibling->key[0],type,(long)new_sibling,test_signal);//upword this function in a recurisve way
				
				if(test_signal==1)
				{
					std::cout<<"Display upper $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
				this_root->DisplayThisKey(type);
				std::cout<<"Finish display upper $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
				}
				
				/*
				cout<<"After Display this$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
				this_root->DisplayThisKey(type);
				cout<<"finish Display this$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
				*/

			}
			else{
				
				//this one is not a bottom
				int i0=-1;
				for(int i=0;i<MAX_KEY_NUMBER;i++)
				{
					if(compare_key(key_in,key[i],type))
					{
						i0=i;
						break;
					}
				}
				bool insert_in_this=(i0==-1 || i0>=(MAX_KEY_NUMBER>>1)+1)?false:true;//indicate where it inserts the node
				int t_add=(insert_in_this==false)?1:0;

				//new one is in the sibling node
				int original_size=(MAX_KEY_NUMBER>>1)+t_add;
				int new_size=MAX_KEY_NUMBER-original_size;

				new_sibling->address[0]=address[original_size];//warning: this cannot be replaced by move_address, since move_address automactically change the up address of its child node

				for(int i=0;i<new_size;i++)
				{
					new_sibling->key[i]=key[i+original_size];
					move_address(this,i+original_size+1,new_sibling,i+1);
					/*
					new_sibling->address[i+1]=address[i+original_size+1];
					if(address[i+original_size+1]!=-1)
					{
						Node * t_1=(Node*)address[i+original_size+1];
						t_1->up_address=(int)new_sibling;

					}
					*/
				}
				for(int i=original_size+1;i<MAX_KEY_NUMBER+1;i++)
					address[i]=-1;


				new_sibling->contain_node=new_size;
				contain_node=original_size;


				if(insert_in_this==false)
				{
					new_sibling->add_or_split(key_in,type,address_in,test_signal);
					if(address_in!=-1)
					{
						Node * t_1=(Node*)address_in;
						t_1->up_address=(long)new_sibling;
					}

				}
				else
				{
					/*
					if(compare_key(key[contain_node-1],key_in,type)==true)
					{
						//key_in will be send to the last, thus the additional one won't be eliminated 
						address[contain_node]=address_in;
						Node * t_1=(Node*)address_in;
						t_1->up_address=(int)this;
					}
					*/
					add_or_split(key_in,type,address_in,test_signal);
					
					if(address_in!=-1)
					{
						Node * t_1=(Node*)address_in;
						t_1->up_address=(long)this;
					}


				}
				if(test_signal==1)
				{
					std::cout<<"Display this $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
					this->DisplayThisKey(type);
					std::cout<<"After Display this_root $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
					std::cout<<"insert_in_this: "<<insert_in_this<< std::endl;

					std::cout<<"Display sibling_node $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;
					new_sibling->DisplayThisKey(type);
					std::cout<<"After Display sibling_node $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< std::endl;

				}
				if(MAX_KEY_NUMBER%2==0)
				{

					Node * this_root=(Node*)up_address;
					new_sibling->up_address=up_address;///////////////////////////newly changed
					this_root->add_or_split(key[contain_node-1],type,(long)new_sibling,test_signal);//upword this function in a recurisve way
					
					move_address(this,contain_node,new_sibling,0);
					/*
					new_sibling->address[0]=address[contain_node];
					if(address[contain_node]!=-1)
					{
						Node * t_1=(Node*)address[contain_node];
						t_1->up_address=(int)new_sibling;
					}
					*/
					address[contain_node]=-1;
					contain_node--;

				}
				else
					std::cout<<"Inefficient Paramater Setting, please set MAX_KEY_NUMBER as an even "<< std::endl;

				

				
				if(NODE_DEBUG==1)
					std::cout<<"NO ROOT, NO bottom split finishes"<< std::endl;
			}



		}
		//if this node has been full 
		//unfinished
	}


}

void Node::delete_or_merge(node_key key_in,short type){
	//we won't call root if its contain_node is no larger than 2(means that the root will be deleted very soon 
	// principle of merging: merge to its left as long as a left node exists

	
	Node * up=(Node *)up_address;// t is the upper node
	int t_delete_index=-1;
	for(int i=0;i<contain_node;i++)
	{
		if(same_key(key_in,key[i],type)==true)
		{
			t_delete_index=i;
			break;
		}
	}

	if(t_delete_index==-1)//if the node we want to delete doesn't exist in B+ tree
		return;
	if(is_bottom==true)
	{
		//it's the bottom
		//if it's the bottom, its values may affect the ones above it

		for(int i=t_delete_index;i<contain_node-1;i++)
		{
			key[i]=key[i+1];
			address[i]=address[i+1];

		}
		if(t_delete_index==0 && is_root==false)
		{
			//delete the first one, have to update the up key
			int up_pointer=-1;
			for(int i=0;i<up->contain_node+1;i++)
			{
				if(up->address[i]==(long)this)
				{
					up_pointer=i;
					break;
				}
			}
			if(up_pointer!=0)
			{
				up->key[up_pointer-1]=key[0];
			}
			else{
				// if up->is_root==true, we don't need to change anything
				if(up->is_root==false){
					Node * c_s_node=up;//abbreviation for current_search node
					while(1)
					{
						Node * u_c_s_node=(Node *)(c_s_node->up_address);
						if(u_c_s_node->address[0]!=(long)c_s_node){

							for(int i=1;i<=u_c_s_node->contain_node;i++)
							{
								if(u_c_s_node->address[i]==(long)c_s_node)
								{
									u_c_s_node->key[i-1]=key[0];
									break;

								}
							}


							break;
						}
						if(u_c_s_node->is_root==true)
						{
							break;
						}
						c_s_node=u_c_s_node;
					}
				}
			}
		}
		address[contain_node-1]=-1;
		contain_node--;

	}
	else{
		//if it's not bottom
		for(int i=t_delete_index;i<contain_node-1;i++)
		{
			key[i]=key[i+1];
			address[i+1]=address[i+2];

		}
		address[contain_node]=-1;
		contain_node--;

	}
	//have been deleted
	// we have to merge, it should occur only when is_root ==false
	node_key delete_value=key[0];//stores for future use
	if(contain_node<(MAX_KEY_NUMBER>>1))
	{
		//we will merge it 
		if(is_root==false )
		{
			int bottom_add=(is_bottom==true)?0:1;



			int current_address=(long)this;

			if(up->address[0]!=current_address)
			{

				// this node is not the leftmost
				int t_index_address_pointer=-1;//store previous address
				int t_index_serial_number=-1;
				//cout<<"up contain_node: "<<up->contain_node<<endl;
				for(int i=1;i<up->contain_node+1;i++)
				{
					if(up->address[i]==current_address)
					{
						t_index_address_pointer=up->address[i-1];
						t_index_serial_number=i-1;
						//cout<<"Current address"<<current_address<<endl;
						//cout<<"Left address"<<t_index_address_pointer<<endl;

						break;
					}

				}

				Node * left=(Node *)t_index_address_pointer;// t is the left node
				//cout<<t_index_serial_number<<endl;
				if(left->contain_node>(MAX_KEY_NUMBER>>1))
				{

					// simply borrow one node from left 
					if(is_bottom==false)
						address[contain_node+1]=address[contain_node];

					for(int i=contain_node;i>=1;i--)
					{
						key[i]=key[i-1];
						address[i]=address[i-1];
					}

					if(is_bottom==false)
					{
						Node * down=(Node *)address[0];
						while(down->is_bottom==false)
							down=(Node *)(down->address[0]);
						key[0]=down->key[0];
					}
					else
						key[0]=left->key[left->contain_node-1];

					//address[0]=left->address[left->contain_node-1+bottom_add];
					move_address(left,left->contain_node-1+bottom_add,this,0);
					/*
					if(left->address[left->contain_node-1+bottom_add]!=-1)
					{
						Node * t_1=(Node*)left->address[left->contain_node-1+bottom_add];
						t_1->up_address=(int)this;

					}*/
					left->address[(left->contain_node)-1+bottom_add]=-1;
					(left->contain_node)--;
					contain_node++;
					//cout<<endl<<"I was called"<<endl;
					//this->DisplayThisKey(type);
					//cout<<"I was called finished"<<endl;
					if(is_bottom==true)
						up->key[t_index_serial_number]=key[0];
					else
						up->key[t_index_serial_number]=left->key[left->contain_node];
				}
				else{
					
					//cout<<"hello1!"<<endl;
					// cannot borrow, have to merge
					if(up->is_root==true && up->contain_node==1)
					{
						//cout<<"hello!"<<endl;
						// the head will be eliminated, and all show be merged into single node
						if(is_bottom==true)
							up->is_bottom=true;

						int left_size=left->contain_node;
						for(int i=0;i<left_size;i++)
						{
							up->key[i]=left->key[i];
							move_address(left,i,up,i);
							/*
							up->address[i]=left->address[i];
							if(left->address[i]!=-1)
							{
								Node * t_1=(Node*)left->address[i];
								t_1->up_address=(int)up;

							}*/
						}

						if(is_bottom==false)
						{
							Node * down=(Node *)address[0];
							while(down->is_bottom==false)
								down=(Node *)(down->address[0]);
							move_address(left,left_size,up,left_size);
							/*
							up->address[left_size]=left->address[left_size];
							if(left->address[left_size]!=-1)
							{
								Node * t_1=(Node*)left->address[left_size];
								t_1->up_address=(int)up;

							}
							*/
							up->key[left_size]=down->key[0];
						}

						for(int i=0;i<contain_node;i++)
						{
							up->key[left_size+i+bottom_add]=key[i];
							move_address(this,i,up,left_size+i+bottom_add);
							/*
							up->address[left_size+i+bottom_add]=address[i];
							if(address[i]!=-1)
							{
								Node * t_1=(Node*)address[i];
								t_1->up_address=(int)up;

							}
							*/
						}
						up->contain_node=(bottom_add+contain_node+left->contain_node);
						if(is_bottom==false)
						{
							move_address(this,contain_node,up,up->contain_node);
							/*
							up->address[up->contain_node]=address[contain_node];
							if(address[contain_node]!=-1)
							{
								Node * t_1=(Node*)address[contain_node];
								t_1->up_address=(int)up;

							}
							*/
						}

						delete left;
						delete this;
					}
					else{

						int left_size=left->contain_node;
						Node * down=(Node *)address[0];
						if(is_bottom==false)
						{

							while(down->is_bottom==false)
								down=(Node *)(down->address[0]);
							left->key[left_size]=down->key[0];
						}
						for(int i=0;i<contain_node;i++)
						{
							left->key[i+left_size+bottom_add]=key[i];
							//left->address[i+left_size+bottom_add]=address[i];
							move_address(this,i,left,i+left_size+bottom_add);
							//if(address[i]!=-1)
							//{
							//	Node * t_1=(Node*)address[i];
							//	t_1->up_address=(int)left;

							//}
						}
						left->contain_node=contain_node+left_size+bottom_add;

						if(is_bottom==true)
						
							//left->address[MAX_KEY_NUMBER]=address[MAX_KEY_NUMBER];
							move_address(this,MAX_KEY_NUMBER,left,MAX_KEY_NUMBER);
							
						else
							move_address(this,contain_node,left,left->contain_node);
						//	left->address[left->contain_node]=address[contain_node];
						if(is_bottom==false)
							up->delete_or_merge(down->key[0],type);
						else
							up->delete_or_merge(delete_value,type);

						delete this;

					}
					
				}
			}
			else{
				// no others in the left, just merge with right
				Node * right=(Node *)up->address[1];

				int right_size=right->contain_node;

				if(right->contain_node>(MAX_KEY_NUMBER>>1))
				{
					//simply borrow one
					Node * down=(Node *)right->address[0];
					if(is_bottom==true)
					{
						key[contain_node]=right->key[0];
						//address[contain_node]=right->address[0];
						move_address(right,0,this,contain_node);
					}
					else{
						while(down->is_bottom==false)
							down=(Node *)(down->address[0]);
						key[contain_node]=down->key[0];
						//address[contain_node+1]=right->address[0];
						move_address(right,0,this,contain_node+1);
					}
					contain_node++;

					for(int i=0;i<right_size-1;i++)
					{
						right->key[i]=right->key[i+1];
						right->address[i]=right->address[i+1];
						//move_address(right,0,this,contain_node+1);
					}
					if(is_bottom==false)
						right->address[right_size-1]=right->address[right_size];
					right->address[right_size-1+bottom_add]=-1;
					(right->contain_node)--;
					if(is_bottom==true)
						up->key[0]=right->key[0];

					else
					{
						down=(Node *)right->address[0];
						while(down->is_bottom==false)
							down=(Node *)(down->address[0]);
						up->key[0]=down->key[0];


					}

				}

				else{
					//cannot just borrow, must merge
					if(up->is_root==true && up->contain_node==1)
					{

						if(is_bottom==true)
							up->is_bottom=true;

						for(int i=0;i<contain_node;i++)
						{
							up->key[i]=key[i];
							//up->address[i]=address[i];
							move_address(this,i,up,i);
						}
						Node * down=(Node *)(right->address[0]);
						if(is_bottom==false)
						{

							while(down->is_bottom==false)
								down=(Node *)(down->address[0]);
							//up->address[contain_node]=address[contain_node];
							move_address(this,contain_node,up,contain_node);
							up->key[contain_node]=down->key[0];
							//move_address(right,0,up,contain_node+1);
						}
						for(int i=0;i<right_size;i++)
						{
							up->key[contain_node+i+bottom_add]=right->key[i];
							//up->address[contain_node+i+bottom_add]=right->address[i];
							move_address(right,i,up,contain_node+i+bottom_add);
						}
						if(is_bottom==false){
							move_address(right,right_size,up,contain_node+right_size+1);
						}
						up->contain_node=(contain_node+right_size+bottom_add);
						
						delete right;
						delete this;
						if(NODE_DEBUG==1)
						{
							std::cout<<"Output the situation after the final merge________________"<< std::endl;
							std::cout<<"Start to output up"<< std::endl;
							up->DisplayThisKey(type);
							std::cout<<"Finish to output up"<< std::endl;
							std::cout<<"Contain node of up: "<<up->contain_node<< std::endl;
							std::cout<<"Up address: "<<(long)up<< std::endl;

							std::cout<<"Finish Output the situation after the final merge________________"<< std::endl;
						}
					}
					else{
						//we merge it to this(the left one)
						Node * down=(Node *)(right->address[0]);

						if(is_bottom==false)
						{

							while(down->is_bottom==false)
								down=(Node *)(down->address[0]);
							key[contain_node]=down->key[0];
						}
						for(int i=0;i<right_size;i++)
						{
							key[i+contain_node+bottom_add]=right->key[i];
							move_address(right,i,this,i+contain_node+bottom_add);
							//address[i+contain_node+bottom_add]=right->address[i];
						}
						if(is_bottom==true)
						{
							//address[MAX_KEY_NUMBER]=right->address[MAX_KEY_NUMBER];
							move_address(right,MAX_KEY_NUMBER,this,MAX_KEY_NUMBER);
						}
						else{
							move_address(right,right_size,this,right_size+contain_node+bottom_add);

						}
						contain_node+=(right->contain_node+bottom_add);
						
						//up->DisplayThisKey(type);
						if(is_bottom==false)
						{
							up->delete_or_merge(down->key[0],type);
						}
						else
						{

							up->delete_or_merge(right->key[0],type);

						}
						delete  right;



					}
				}
			}



		}
	}

}



void Node::InsertKey(node_key key_in,short type, int address_in,int test_signal ){
	/* insert one key to this tree


	*/
	if(is_bottom==true)
	{
		// if this node is a bottom node
		/*
				if(test_signal==1)
		{	cout<<endl;
			cout<<"Enter add sub function at this node, with the display as following"<<endl;
			cout<<"*******************************************************************"<<endl;
			this->DisplayThisKey(type);
			cout<<"*******************************************************************"<<endl;
			cout<<"Insert value: "<<key_in.type_int<<endl;
			cout<<"Entering node display finishes"<<endl;
		}
		*/
		add_or_split(key_in,type,address_in,test_signal);

		
	}
	else{

		// if this node is not a bottom node
		int i;
		for( i=0;i<MAX_KEY_NUMBER;i++)
		{
			if(address[i+1]==-1)
			{
				//abrupts, 
				break;
			}
			if(compare_key(key_in,key[i],type))
			{
				Node * t=(Node *)address[i];// input the address of next node
				t->InsertKey(key_in,type,address_in,test_signal);
				return;
			}



		}
		Node * t=(Node *)address[i];// input the address of next node
		t->InsertKey(key_in,type,address_in,test_signal);
		return;
	}

}
void Node::DeleteKey(node_key key_in,short type)
{
	if(is_bottom==false)
	{
		// it's not a bottom, find until the bottom
		int target_address=0;
		for(int i=0;i<contain_node;i++)
		{
			if(compare_key(key_in,key[i],type))
			{
				target_address=address[i];
				break;
			}
		}
		if(target_address==0)
			target_address=address[contain_node];
		Node * t=(Node *)target_address;
		t->DeleteKey(key_in,type);
	}
	else{
		//current node is bottom
		delete_or_merge(key_in,type);
	}

}
