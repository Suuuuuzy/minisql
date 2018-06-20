//
//  CatlogManage.hpp
//  cpp_test
//
//  Created by 余蒹葭 on 2018/6/11.
//  Copyright © 2018年 余蒹葭. All rights reserved.
//


/*
 要实现的语句：
 OK     create table， 检查是否有重复，在数据库里面增加这个表的信息
 ok     drop table, 删除这个表的信息就好了
 create index XX on xx(xx)， 增加这个索引的信息
 ok     drop index xx ， 删除这个索引的信息，如果是主键，不允许删除索引
 0 select * from ... where .. and ..， 找表（rm做） 找是否有索引（im做） 如果没有，遍历找（bm做） 提供这个表的record需要几个block存
1  insert into ... values (vhcxj,vcxjkv,vcx) 
 需要比较，每个值的类型是不是对，还要看，更新这个表需要几个block存
 2 delete from ... where... 减少某个表的行的数目，具体减少多少，由rm给我（因为必定是先找的）
 ok   quit;
 execfile ...
 */



#ifndef CATLOGMANAGE__H_
#define CATLOGMANAGE__H_

#pragma pack(1)   ///字节对齐，没有此指令读取文件时会出错

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Global_definition.h"

#pragma  once

#define  BLOCK 4096
#define NAME_LENGTH 128
#define SELECT 0
#define DELETE 1
using namespace std;

typedef struct INDEX* PINDEX;
typedef struct DataBaseHeader* PDataBaseHeader;
typedef struct Attribute * PAttribute;
typedef struct TableHeader* PTableHeader;

struct INDEX{
    char name[32];
    char InTableName[32];
    char InAtt[32]; //属性名称
    
    PINDEX NextIndex;
};

struct DataBaseHeader{
    char DatabaseName[32];
    unsigned int TableNum; // number of tables in this database
    unsigned int IndexNum;
    
    PTableHeader FirstTable; // point to the first database in the table
    PDataBaseHeader  NextDB; // point to the next DB
    PINDEX FirstINDEX; // point to the first index in this database
};

struct TableHeader{
    char TableName[32]; // 32 bytes
    unsigned int AttNum; // number of attributes in this table
    char PK[32]; // 1 byte, the index of the primary key
    unsigned int RowLen; // the length of one row
    unsigned int RowNum; // the number of rows
    
    PAttribute  FirstAtt;// point to the first att in the table
    PTableHeader NextTable; // point to the next table in this database
};

struct Attribute{
    char AttributeName[32]; // 32 bytes
    unsigned int offset; // how many bytes from the head of this tuple to this attribute
    unsigned int DataType; //
    unsigned int Len; // length of this attribute, if the attribute is char(n), 2bytes
    unsigned int Unique; //
    
    PAttribute NextAtt; // point to the next att in this table
};



class CatlogManage{
public:
    CatlogManage(char* filename);
    CatlogManage();
    
    bool  save(char* filename); // save catalog into file
    
    void  test(char* filename); //存一个文件测试一下
    bool CreateTable(char* s_table_name,Property* t_property_group,int property_used);
    bool DropTable(char * TableName);
    void FreeAtt(PAttribute attnow);
    bool CreateIndex(char* s_index_name,char* s_table_name,char* property_name);
    bool DropIndex(char* IndexName);
    bool SelectORDelete(char* s_table_name,Condition* t_select_condition,int type, int condition_used);
    bool Insert(char* s_table_name, Condition* t_select_condition, int condition_used);
    
    
    
    PINDEX* GetIndex(char* s_table_name, Condition* t_select_condition, int condition_used);// 根据select和的delect语句中的属性的信息，得到索引的信息数组
    PTableHeader GetTable(char* tablename); // 根据表名得到表头的信息
    PAttribute GetAtt(char* tablename, char* attname); // 根据表名和属性名得到这个属性的信息
    
    
    void show();
    
    
    //还需要的函数是：
    //获得某个表的文件名？
    //获得某个表的索引信息
    //需要完成的语句：
    
    //int FindTable(char * TableName);
    
private:
    
    int DataBaseNum; // 有几个数据库，可能更新
    //int DataBaseOffset; // 对每个数据库，存储信息所需的空间大小都一样，每次都移动一样的offset，不更新
    PDataBaseHeader DBHeader[32]; //假设最多32个database
    PTableHeader DirtyTable;
    char info[NAME_LENGTH][NAME_LENGTH];
    
    //void CreateTableInfoConvert();
    
   
    
};

#endif /* CatlogManage_hpp */
