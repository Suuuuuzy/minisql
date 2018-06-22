//
//  test_record_checker.cpp
//  minisql
//
//  Created by 余蒹葭 on 2018/6/21.
//  Copyright © 2018年 余蒹葭. All rights reserved.
//

#include <stdio.h>


 //according to the turn in catalog
 struct MetaData{
 	int Len;// the length of this att
 	int offset; // from the head of this tuple to this att
 };
 typedef struct MetaData PMetaData;

//int con_att[]: 这里需要每个condition的属性在一个tuple中的是第几个att att[i], 下标和condition一致
// int offset: 这个tuple在文件中的offset
// this funciton solves the check of one tuple from memory
// you have to check all the condtions in the list
// the data tyoe you read should be consistent with the tyoe defined in the catalog
bool check(PMetaData meta_data,char* s_table_name, int tuple_size, Condition** t_select_condition, int* con_att,int condition_used,int offset){
    // 用index给我的地址，调用buffer，读到一条数据
    // 如何解析成各种类型的数据？？？？
    // 需要知道这个table是如何组织的
    // 通过gettable,得到表的头指针，就一切解决了！但是问题在于，不能访问它的数据？？？
    // 还需要知道：每个condition的offset
    //
    // 对这一条数据，用condition中的信息，看每个条件是否符合，先看类型，再看操作
    // 如果符合要求，就把这个数据输出了，不用传出去hhh
    // calculate tuple in one block
    int tuple_in_one_block = Block_Size/tuple_size;
    
    int tuplenum = offset/tuple_size;
    
    int block_num = (tuplenum % tuple_in_one_block == 0) ? tuplenum / tuple_in_one_block - 1 : tuplenum / tuple_in_one_block;
    
    Block_Package* BlockStartAdd = Read_Block(DBname,s_table_name,block_num,tuple_size);
    
    // calculate the pointer to the tuple we want to find in memory
    char* TupleAddInMem = BlockStartAdd + (tuplenum % tuple_in_one_block)*tuple_size;
    
    // define the pointer to the tuple we want
    char OneTuple[MAXLEN] = {NULL}; // the maximum length of one tuple
    
    /*调用buffer，读出一条，长度是：TupleSize*/
    memcpy(OneTuple, TupleAddInMem, tuple_size);
    cout << "read this tuple from mem" << endl;
    
    int su = 1;
    for(int i=0; i<condition_used; i++){
        if(t_select_condition[i].value_type==TYPE_INT || t_select_condition[i].value_type==TYPE_FLOAT){
            if(t_select_condition[i].value_type==TYPE_INT)
                memcpy(a, TupleAddInMem+meta_data[con_att[i]].Len, sizeof(int));
            else if(t_select_condition[i].value_type==TYPE_FLOAT)
                memcpy(a, TupleAddInMem+meta_data[con_att[i]].Len, sizeof(float));
            float b = condition_used[i].value;
            x = a-b;
        }
        else if(t_select_condition[i].value_type==TYPE_CHAR){
            char * a;
            a = memcpy(a, TupleAddInMem+meta_data[con_att[i]].Len, strlen(t_select_condition[i].character_buffer));
            b = condition_used[i].character_buffer;
            x = strcmp(a,b);
        }
        switch(condition_used[i].op_type){
                
            case CONDITION_LARGER_EQUAL:
                if(x<0){su = 0; cout << "this record fail" <<endl;} // if one condition failed, this tuple is not eligible
                break;
            case CONDITION_LARGER:
                if(x<=0){su = 0; cout << "this record fail" <<endl;} // if one condition failed, this tuple is not eligible
                break;
            case CONDITION_SMALLER_EQUAL:
                if(x>0){su = 0; cout << "this record fail" <<endl;} // if one condition failed, this tuple is not eligible
                break;
            case CONDITION_SMALLER:
                if(x>=){su = 0; cout << "this record fail" <<endl;} // if one condition failed, this tuple is not eligible
                break;
            case CONDITION_EQUAL:
                if(x!=0){su = 0; cout << "this record fail" <<endl;} // if one condition failed, this tuple is not eligible
                break;
            case CONDITION_NOT_EQUAL:
                if(x==0){su = 0; cout << "this record fail" <<endl;} // if one condition failed, this tuple is not eligible
                break;
        }
        if(!su) break;// if one condtion failed, no need to test any more conditions
    }
    if(!su)// unsuccessful
        return false;
    else true;
}

