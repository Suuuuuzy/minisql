//
//  CatlogManage.cpp
//  cpp_test
//
//  Created by 余蒹葭 on 2018/6/11.
//  Copyright © 2018年 余蒹葭. All rights reserved.
//

/*
 要实现的语句：
 create table， 在数据库里面增加这个表的信息
 drop table, 删除这个表的信息就好了
 create index XX on xx(xx)， 增加这个索引的信息
 drop index xx ， 删除这个索引的信息，如果是主键，不允许删除索引
 select * from ... where .. and ..， 找表（rm做） 找是否有索引（im做） 如果没有，遍历找（bm做） 提供这个表的record需要几个block存
 insert into ... values (vhcxj,vcxjkv,vcx) 看主键是否重复，比较一次就行了，增加某个表的行的数目，更新这个表需要几个block存
 delete from ... where... 减少某个表的行的数目，具体减少多少，由rm给我（因为必定是先找的）
 quit;
 execfile ...
 */

//待会写一个测试的文件，测试一下


#include "connect_catalog_add_offset.h"
using namespace std;

//catalog manager直接从文件读数据

//默认构造函数，无参数，测试用
CatlogManage::CatlogManage(){
    DirtyTable = NULL;
    DataBaseNum = 1;
}

//通过访问文件来构造catalog
CatlogManage::CatlogManage(char * filename){
    DataBaseNum = 1;
    DirtyTable = NULL;
    FILE *p;
    if((p = fopen(filename, "rb"))==NULL){
        printf("open file error!\n");
    }
    
    int DBcounter = 0;
    int i=0, j = 0, k = 0;
    //当前对象的指针
    PAttribute PAttributeNow;
    PTableHeader PTableHeaderNow;
    PINDEX PINDEXNow;
    
    while(!feof(p)){
        //处理一个数据库的头文件
        DBHeader[DBcounter] = (PDataBaseHeader)malloc(sizeof(struct DataBaseHeader));
        fread(DBHeader[DBcounter],1,32*sizeof(char)+2*sizeof(int),p);
        DBHeader[DBcounter]->FirstTable = NULL;
        DBHeader[DBcounter]->NextDB = NULL;
        DBHeader[DBcounter]->FirstINDEX = NULL;
       //printf("database:%s,%d,%d\n",DBHeader[DBcounter]->DatabaseName, DBHeader[DBcounter]->TableNum, DBHeader[DBcounter]->IndexNum);
        
        if(DBHeader[DBcounter]->TableNum!=0){//
            
            //开始处理每一个表
            i=0;
            while(i<DBHeader[DBcounter]->TableNum){
                i++;
                PTableHeaderNow = (PTableHeader)malloc(sizeof(struct TableHeader));// 为第一个表格分配空间
                DBHeader[DBcounter]->FirstTable = PTableHeaderNow;
                PTableHeaderNow->NextTable = NULL;
                fread(PTableHeaderNow,1,64*sizeof(char)+3*sizeof(int),p);
                //printf("table:%s,%d,%s,%d,%d\n",PTableHeaderNow->TableName, PTableHeaderNow->AttNum,PTableHeaderNow->PK, PTableHeaderNow->RowLen,PTableHeaderNow->RowNum );
                if(PTableHeaderNow->AttNum!=0){
                    j=0;
                    while(j< PTableHeaderNow->AttNum){
                        j++;
                        PAttributeNow = (PAttribute)malloc(sizeof(struct Attribute));
                        PTableHeaderNow->FirstAtt = PAttributeNow;
                        PAttributeNow->NextAtt = NULL;
                        //开始处理每一个attribute
                        fread(PAttributeNow,1,32*sizeof(char)+3*sizeof(int),p);
                        //printf("att:%s,%d, %d, %d\n",PAttributeNow->AttributeName, PAttributeNow->DataType, PAttributeNow->Len, PAttributeNow->Unique);
                    }
                }
            }
        }
        //对索引进行处理（读入）
        if(DBHeader[DBcounter]->IndexNum!=0){
            k = 0;
            while(k<DBHeader[DBcounter]->IndexNum){
                k++;
                PINDEXNow = (PINDEX)malloc(sizeof(struct INDEX));
                DBHeader[DBcounter]->FirstINDEX = PINDEXNow;
                PINDEXNow->NextIndex = NULL;
                //开始一个个地处理索引
                fread(PINDEXNow,1,3*32*sizeof(char),p);
                //printf("index:%s,%s, %s\n",PINDEXNow->name, PINDEXNow->InTableName, PINDEXNow->InAtt);
            }
        }
        //一个数据库处理完毕。。。一行终于结束了。。
        char c = fgetc(p); // 如果不加这句话，后面会多输出一个database 属性是0，0 原因是在读到最后一个字符的时候，feof还没有检测到这已经是文件的末尾了。。。就会多来一个，但是这样写的问题就在于如果有多个数据库就凉了（先假设只有一个数据库）
        //printf("ccccc: %c",c);
        DBcounter++;
    }
    fclose(p);
    return;
}


bool  CatlogManage::save(char* filename){//如何写回去？
    FILE *p;
    if((p = fopen(filename, "wb"))==NULL){
        printf("open file error!\n");
        return false;
    }
    int DBcounter = 0;
    
    PAttribute PAttributeNow;
    PTableHeader PTableHeaderNow;
    PINDEX PINDEXNow;
    
    //写入一个数据库头，注意数据长度
    fwrite(&DBHeader[DBcounter]->DatabaseName,1,32*sizeof(char),p);
    fwrite(&DBHeader[DBcounter]->TableNum,1,sizeof(int),p);
    fwrite(&DBHeader[DBcounter]->IndexNum,1,sizeof(int),p);
    //对每一个表
    PTableHeaderNow = DBHeader[DBcounter]->FirstTable;
    while(PTableHeaderNow!=NULL){
        fwrite(PTableHeaderNow->TableName,1,32*sizeof(char),p);
        fwrite(&PTableHeaderNow->AttNum,1,sizeof(int),p);
        fwrite(PTableHeaderNow->PK,1,32*sizeof(char),p);
        fwrite(&PTableHeaderNow->RowLen,1,sizeof(int),p);
        fwrite(&PTableHeaderNow->RowNum,1,sizeof(int),p);
        
        PAttributeNow = PTableHeaderNow->FirstAtt;
        //对每一个属性
        while(PAttributeNow!=NULL){
            fwrite(PAttributeNow->AttributeName,1,32*sizeof(char),p);
            fwrite(&PAttributeNow->offset,1,sizeof(int),p);
            fwrite(&PAttributeNow->DataType,1,sizeof(int),p);
            fwrite(&PAttributeNow->Len,1,sizeof(int),p);
            fwrite(&PAttributeNow->Unique,1,sizeof(int),p);            
            PAttributeNow = PAttributeNow->NextAtt;
        }
        //为下一个表分配
        PTableHeaderNow = PTableHeaderNow->NextTable;
    }
    //对索引进行写入
    PINDEXNow = DBHeader[DBcounter]->FirstINDEX ;
    //开始一个个地处理索引
    while(PINDEXNow!=NULL){
        fwrite(PINDEXNow->name,1,32*sizeof(char),p);
        fwrite(PINDEXNow->InTableName,1,32*sizeof(char),p);
        fwrite(PINDEXNow->InAtt,1,32*sizeof(char),p);
        PINDEXNow = PINDEXNow->NextIndex;
    }
    //一个数据库处理完毕。。。一行终于结束了。。
    
    fclose(p);
    return true;

}



void  CatlogManage::test(char* filename){//
    FILE *p;
    if((p = fopen(filename, "wb"))==NULL){
        printf("open file error!\n");
    }
    int DBcounter = 0;
    
    PAttribute PAttributeNow;
    PTableHeader PTableHeaderNow;
    PINDEX PINDEXNow;
    
    //fwrite(DBHeader[DBcounter]->DatabaseName, 1,32*sizeof(char), p);
    DBHeader[DBcounter] = (PDataBaseHeader)malloc(sizeof(struct DataBaseHeader));
    
    strcpy(DBHeader[DBcounter]->DatabaseName, "hello sql");
    DBHeader[DBcounter]->TableNum = 1;
    DBHeader[DBcounter]->IndexNum = 1;
    DBHeader[DBcounter]->FirstTable = (PTableHeader)malloc(sizeof(struct TableHeader));
    DBHeader[DBcounter]->FirstINDEX = (PINDEX)malloc(sizeof(struct INDEX));
    
    strcpy(DBHeader[DBcounter]->FirstTable->TableName,"first table");
    DBHeader[DBcounter]->FirstTable->AttNum = 1;
    strcpy(DBHeader[DBcounter]->FirstTable->PK,"pk");
    DBHeader[DBcounter]->FirstTable->RowLen = 10;
    DBHeader[DBcounter]->FirstTable->RowNum = 100;
    DBHeader[DBcounter]->FirstTable->FirstAtt = (PAttribute)malloc(sizeof(PAttribute));
    DBHeader[DBcounter]->FirstTable->NextTable = NULL;
    
    
    strcpy(DBHeader[DBcounter]->FirstTable->FirstAtt->AttributeName,"att name");
    DBHeader[DBcounter]->FirstTable->FirstAtt->offset = 4;
    DBHeader[DBcounter]->FirstTable->FirstAtt->offset = 0;
    DBHeader[DBcounter]->FirstTable->FirstAtt->DataType = 3;
    DBHeader[DBcounter]->FirstTable->FirstAtt->Len = 4;
    DBHeader[DBcounter]->FirstTable->FirstAtt->Unique = 0;
    DBHeader[DBcounter]->FirstTable->FirstAtt->NextAtt = NULL;
    
    
    strcpy(DBHeader[DBcounter]->FirstINDEX->name,"index");
    strcpy(DBHeader[DBcounter]->FirstINDEX->InTableName, "first table");
    strcpy(DBHeader[DBcounter]->FirstINDEX->InAtt, "att name");
    DBHeader[DBcounter]->FirstINDEX->NextIndex = NULL;
    
    
    
    //写入一个数据库头，注意数据长度
    fwrite(&DBHeader[DBcounter]->DatabaseName,1,32*sizeof(char),p);
    fwrite(&DBHeader[DBcounter]->TableNum,1,sizeof(int),p);
    fwrite(&DBHeader[DBcounter]->IndexNum,1,sizeof(int),p);
    //对每一个表
    PTableHeaderNow = DBHeader[DBcounter]->FirstTable;
    while(PTableHeaderNow!=NULL){
        fwrite(PTableHeaderNow->TableName,1,32*sizeof(char),p);
        fwrite(&PTableHeaderNow->AttNum,1,sizeof(int),p);
        fwrite(PTableHeaderNow->PK,1,32*sizeof(char),p);
        fwrite(&PTableHeaderNow->RowLen,1,sizeof(int),p);
        fwrite(&PTableHeaderNow->RowNum,1,sizeof(int),p);
        
        PAttributeNow = PTableHeaderNow->FirstAtt;
        //对每一个属性
        while(PAttributeNow!=NULL){
            fwrite(PAttributeNow->AttributeName,1,32*sizeof(char),p);
            fwrite(&PAttributeNow->offset,1,sizeof(int),p);
            fwrite(&PAttributeNow->DataType,1,sizeof(int),p);
            fwrite(&PAttributeNow->Len,1,sizeof(int),p);
            fwrite(&PAttributeNow->Unique,1,sizeof(int),p);
            
            PAttributeNow = PAttributeNow->NextAtt;
        }
        //为下一个表分配
        PTableHeaderNow = PTableHeaderNow->NextTable;
    }
    //对索引进行写入
    PINDEXNow = DBHeader[DBcounter]->FirstINDEX ;
    //开始一个个地处理索引
    while(PINDEXNow!=NULL){
        fwrite(PINDEXNow->name,1,32*sizeof(char),p);
        fwrite(PINDEXNow->InTableName,1,32*sizeof(char),p);
        fwrite(PINDEXNow->InAtt,1,32*sizeof(char),p);
        PINDEXNow = PINDEXNow->NextIndex;
    }
    //一个数据库处理完毕。。。一行终于结束了。。
    
    fclose(p);
}

// create table
// info[0]:表名
// info[1]:pk名
// info[2]:pk类型
// info[3]:pk长度
// info[4]:pk unique
// info[5]:属性名
// info[6]:属性类型
// info[7]:属性长度
// info[8]:属性是否unique   1：unique 0：不unique
// info[9]:。。。。
//info 以null结尾

bool CatlogManage::CreateTable(char* s_table_name,Property* t_property_group,int property_used){
    
    int i = 0;
    PTableHeader table = DBHeader[0]->FirstTable;
    PAttribute att = NULL;
    int rowlen = 0; // rowlen is incremented every time we add an attribute, so offset is equal to it
    
    while(table!=NULL){
        if(!strcmp(table->TableName,s_table_name)){
            printf( "this table has already in this database!!!!try another name!!!\n" );
            return false;
        }
        table = table->NextTable;
    }
    
    table = (PTableHeader)malloc(sizeof(struct TableHeader));
    table->NextTable = DBHeader[0]->FirstTable;
    DBHeader[0]->FirstTable = table;
    strcpy(table->TableName, s_table_name);
    //strcpy(table->PK,Info[1]);
    att = (PAttribute)malloc(sizeof(struct Attribute));
    table->FirstAtt = att;
    att->NextAtt = NULL;
    while(i<property_used){
        att->Unique = t_property_group[i].is_unique; //一个字符表示是否unique 1：unique
        if(t_property_group[i].is_primary_key==true){
            strcpy(table->PK,t_property_group[i].property_name);
            att->Unique = 1;// rewrite unique property before when is is pk
        }
        strcpy(att->AttributeName,t_property_group[i].property_name);
        att->offset = rowlen;
        att->DataType = t_property_group[i].type; // 用一个字符表示数据类型！！！
        att->Len = t_property_group[i].char_capacity;//一个字符表示数据长度！！！最多256
        rowlen+=att->Len;
        i++;
        if(i<property_used){
            att->NextAtt = (PAttribute)malloc(sizeof(struct Attribute));
            att = att->NextAtt;
        }
    }
    att->NextAtt = NULL;
    table->AttNum = property_used;
    table->RowNum = 0;
    table->RowLen = rowlen;
    printf("create table success!!!\n");
    return true;
}

void CatlogManage::FreeAtt(PAttribute attnow){
    if(attnow->NextAtt==NULL)free(attnow);
    else{
        FreeAtt(attnow->NextAtt);
        free(attnow);
    }
}

//drop table，删除某个表，并且删除这个表上的索引
bool CatlogManage::DropTable(char* s_table_name){
    PTableHeader tablenow = DBHeader[0]->FirstTable;
    PTableHeader dtable = NULL;
    PINDEX indexnow = DBHeader[0]->FirstINDEX;
    PINDEX dindex = NULL;
    int su = 0;
    if(tablenow==NULL){
        printf("There's no table in this database, error!\n" );
        return false;
    }
    else{
        if(!strcmp(tablenow->TableName,s_table_name)){
            DBHeader[0]->FirstTable = tablenow->NextTable;
            FreeAtt(tablenow->FirstAtt);
            free(tablenow);
            su = 1;
            printf("drop this table successfullly!\n");
        }
        else{
            while(tablenow->NextTable!=NULL) {
                // if equal
                if(!strcmp(tablenow->NextTable->TableName,s_table_name)){
                    dtable = tablenow->NextTable;
                    tablenow->NextTable = dtable->NextTable;
                    if(dtable->FirstAtt!=NULL) {
                        FreeAtt(dtable->FirstAtt);
                    }
                    free(dtable);
                    su = 1;
                    printf("drop this table successfullly!") ;
                    break;
                }
                else tablenow = tablenow->NextTable;
            }
            if(su==0) printf("There is no such table in this database! error!\n");
        }
    if(indexnow==NULL){
        printf("There's no index on this database!\n" );
    }
    else{
        if(!strcmp(indexnow->InTableName,s_table_name)){
            DBHeader[0]->FirstINDEX = indexnow->NextIndex;
            free(indexnow);
            printf("Drop one index on this table\n" );
        }
        while (indexnow->NextIndex!=NULL) {
            if(!strcmp(indexnow->NextIndex->InTableName,s_table_name)){//if this index is on this table, delete it, too
                dindex = indexnow->NextIndex;
                indexnow->NextIndex = dindex->NextIndex;
                printf("Drop one index on this table\n" );
                free(dindex);
            }
            indexnow = indexnow->NextIndex;
        }
    }
    }
    if(su) return true;
    else return false;
}

//create index
//创建索引
//完整性检查
//先检查这个表是否存在
//再检查这个属性是不是存在
//若存在，看是不是主键
//再检查是不是已经有了在同一个表的同一个属性上的相同索引
//如果有，就不再创建了，还要返回那个已经有的索引的名字
bool CatlogManage::CreateIndex(char* s_index_name,char* s_table_name,char* property_name){
    PTableHeader table;
    PAttribute att;
    PINDEX index;
    
    int sutable = 0; // 1: 存在这个表
    int suatt = 0; // 1: 存在个属性
    table = DBHeader[0]->FirstTable;
    while(table!=NULL){
        if(!strcmp(table->TableName,s_table_name)){// 找到了这个表，再看是否有这个属性
            sutable = 1;
            if(!strcmp(table->PK,property_name)){ // 如果是要在主键上创建索引，不用再创建
                printf("this attribute is pk, no need to create an index on it again");
                return false;
            }
            att = table->FirstAtt;
            while(att!=NULL){
                if(!strcmp(att->AttributeName,property_name)){
                    suatt = 1;
                    break;
                }
                att = att->NextAtt;
            }
            break;
        }
        table = table->NextTable;
    }
    if(sutable && suatt) {
        //再检查是否已经在同样的表和属性上有了一个索引，那就返回已经有的索引的名字
        index = DBHeader[0]->FirstINDEX;
        while(index!=NULL){
            if(!strcmp(index->InTableName,s_table_name) && (!strcmp(index->InAtt,property_name))){
                printf("there has been an index on this attribute, name is %s",index->name);
                printf("no need to create an index again\n");
                return false;
            }
            index = index->NextIndex;
        }
        //终于检查完毕之后，插入
        PINDEX newindex = (PINDEX)malloc(sizeof(struct INDEX));
        strcpy(newindex->name,s_index_name);
        strcpy(newindex->InTableName, s_table_name);
        strcpy(newindex->InAtt, property_name);
        newindex->NextIndex = DBHeader[0]->FirstINDEX;
        DBHeader[0]->FirstINDEX = newindex;
        return  true;
    }
    else if(sutable && !suatt) printf("NO such attribut %s in table %s",property_name, s_table_name);
    else if(!sutable) printf("there is no such table %s",s_table_name);
    return false;
}

//drop index
//删除某个索引，前提是：索引表中有这个索引
bool CatlogManage::DropIndex(char* s_index_name){
    PINDEX dindex;
    PINDEX indexnow;
    indexnow = DBHeader[0]->FirstINDEX;
    int su = 0;// 1:
    if(indexnow==NULL) printf("No index in this database\n");
    else if(!strcmp(indexnow->name,s_index_name)){
        DBHeader[0]->FirstINDEX = indexnow->NextIndex;
        free(indexnow);
        printf("drop this index successfullly!\n");
        return  true;
    }
    else{
        while(indexnow->NextIndex!=NULL){
            if(!strcmp(indexnow->NextIndex->name,s_index_name)){
                dindex = indexnow->NextIndex;
                indexnow->NextIndex = dindex->NextIndex;
                free(dindex);
                su = 1;
                printf("drop this index successfullly!\n");
                return  true;
            }
            indexnow = indexnow->NextIndex;
        }
        if(!su) printf("no such index named as %s in this database",s_index_name);
    }
    return false;
}


// select: 0
// insert: 1
// delete: 2

// 语句格式：
// type 如上说明
//Info 的格式：
// select: info[0] : 表名  info[1] :属性1 的名字，。。之后是各个条件里面的属性名字
//最后一个元素是null
//
// insert:  info[0] : table name, info[1]:第一个值的类型，info[2]: 第二个值的类型。。


//info的最后一个元素是NULL
//
//delete  : info[0]:表名  info[1] :属性1 的名字，。。之后是各个条件里面的属性名字
//最后一个元素是null,
// delete 和 select 是差不多的
//
//
// select * from b where  jfisogd and jfkdgh and fghd
bool CatlogManage::SelectORDelete(char* s_table_name,Condition* t_select_condition,int type, int condition_used){
    //0:select, 1: delete
    
    PTableHeader table;
    PAttribute att;
    table = DBHeader[0]->FirstTable;
    int sutable = 0;
    int suatt = 0;
    int i = 0;
    
    while(table!=NULL){
        if(!strcmp(table->TableName,s_table_name)) { //found  this table!!! 
            sutable  = 1;
            printf("found this table (%s) \n",s_table_name);
               // printf("select or delete\n");
                while(i!=condition_used){ //对每个属性名，都看看是不是存在
                    att = table->FirstAtt;
                    suatt = 0;
                    while(att!=NULL){
                        if(!strcmp(att->AttributeName,t_select_condition[i].column_name)){
                            suatt = 1;
                            break;
                        }
                        att = att->NextAtt;
                    }
                    if(!suatt){
                        printf("NO matching attibute (%s) in this table, wrong!!!\n",t_select_condition[i].column_name);
                        break;
                    }
                    i++;//看下一个属性
                }
                if(type==1) DirtyTable = table;// delete
                if(i==condition_used){
                    printf("no problem with att\n");
                    return true;
                }
            break; // 如果找到这个表了， 就不用再看下一个表了
        }
        table = table->NextTable; // 如果目前还没找到这个表，看下一个表
    }
    return false; //
}

bool CatlogManage::Insert(char* s_table_name, Condition* t_select_condition,int condition_used){
    
    PTableHeader table;
    table = DBHeader[0]->FirstTable;
    while(table!=NULL){
        if(!strcmp(table->TableName,s_table_name)) break;
        else table = table->NextTable;
    }
    if(table==NULL){
        printf("no this table in this database!\n");
        return false;
    }
    PAttribute att = table->FirstAtt;
    table->RowNum++;
    int i = 0;
    string value = string(t_select_condition[i].character_buffer);
    int len;
    
    while(i<condition_used && att!=NULL){
        len = strlen(t_select_condition[i].character_buffer)-1;
        if(att->DataType!=t_select_condition[i].value_type || (att->Len<len && t_select_condition[i].value_type==2)){
            printf("wrong type!!!!insert failed!\n");
            return false;
        }
        att = att->NextAtt;
        i++;
    }
    if(att!=NULL && i==condition_used) printf("not enough values!\n");
    else if(i!=condition_used && att==NULL) printf("too many values!\n");
    else {
        table->RowNum++;
        printf("rownum++\n");
        return true;
    }// insert  success
    return  false;
}


void CatlogManage::show(){
    PTableHeader table = DBHeader[0]->FirstTable;
    PAttribute att = NULL;
    PINDEX INDEX = DBHeader[0]->FirstINDEX;
    
    printf("\n\n_________________show___begin_____________\n");
    printf("database:%s,%d,%d\n",DBHeader[0]->DatabaseName, DBHeader[0]->TableNum, DBHeader[0]->IndexNum);
    
    while(table!=NULL){
         printf("table:%s,%d,%s,%d,%d\n",table->TableName, table->AttNum,table->PK, table->RowLen,table->RowNum );
        att = table->FirstAtt;
        while(att!=NULL){
            printf("att:%s,%d,%d, %d, %d\n",att->AttributeName, att->offset,att->DataType, att->Len, att->Unique);
            att = att->NextAtt;
        }
        table = table->NextTable;
    }
    
    while(INDEX!=NULL){
        printf("index:%s,%s, %s\n",INDEX->name, INDEX->InTableName, INDEX->InAtt);
        INDEX = INDEX->NextIndex;
    }

     printf("_______________show___end________________\n\n");

}

// find the indexe appear in select conditions, return a list
PINDEX* CatlogManage::GetIndex(char* s_table_name, Condition* t_select_condition, int condition_used){ // 在一句select或delete语句中找到，是否存在的对应的index
    // 输入是表名，条件的属性名，条件的数目
    int i = 0;
    PINDEX temp;
    PINDEX re[10] = {NULL};
    int count = 0;
    temp = DBHeader[0]->FirstINDEX;
    while(temp!=NULL){
        i = 0;
        while(i<condition_used){
            if(!strcmp(s_table_name,temp->InTableName) && !strcmp(t_select_condition[i].column_name,temp->InAtt)){ // found this index!!!
                re[count] = temp;
                count++;
                break;
            }
            i++;
        }
        temp = temp->NextIndex;
    }
    if(count==0){
        printf("there are no index on any of the attributes in this sentence\n");
        return  NULL;
    }
    return re; // 是一个数组指针，返回是一个数组，里面有各个有索引的条件的全部信息（struct index）
}

PTableHeader CatlogManage::GetTable(char* tablename){
    PTableHeader  re;
    re = DBHeader[0]->FirstTable;
    while(re!=NULL){
        if(!strcmp(re->TableName,tablename)){
            return re;
        }
        re = re->NextTable;
    }
    return  NULL;// this table does not exist
}

PAttribute CatlogManage::GetAtt(char* tablename, char* attname){
    PAttribute re;
    PTableHeader table;
    table = DBHeader[0]->FirstTable;
    while(table!=NULL){
        if(!strcmp(tablename,table->TableName)){ // found this table!!!
            re = table->FirstAtt;
            while (re!=NULL) {
                if(!strcmp(re->AttributeName, attname)){
                    printf("found this attribute!\n");
                    return  re;
                }
                re = re->NextAtt;
            }
            printf("can not find this attribute in this table\n");
            return NULL;
        }
        table = table->NextTable;
    }
    printf("can not find this table\n");
    return  NULL;
}



