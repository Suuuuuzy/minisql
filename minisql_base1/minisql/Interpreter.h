#ifndef INTERPRETER_H__
#define INTERPRETER_H__
#include<iostream>
#include<regex>
#include"Global_definition.h"
#include<fstream>
#include"connect_catalog_add_offset.h"

#define PROPERTY_LENGTH 10000
#define PROPERTY_MAX  128

#pragma  once
#pragma pack(1) 

#define CONDITION_LARGER_EQUAL 0
#define CONDITION_LARGER 1
#define CONDITION_SMALLER_EQUAL 2
#define CONDITION_SMALLER 3
#define CONDITION_EQUAL 4
#define CONDITION_NOT_EQUAL 5


class Interpreter{
public:
	bool Translate(std::string input);
	void Display_group();
	Interpreter();
	~Interpreter();
private:
    
    CatlogManage* catlog;
    
	Condition t_select_condition[PROPERTY_MAX];
	Property t_property_group[PROPERTY_MAX];
	char s_table_name[NAME_LENGTH];
	char s_index_name[NAME_LENGTH];
	char s_file_name[NAME_LENGTH];
	int property_used;
	int condition_used;
	bool Match_Create_Table(std::string input); // create table (
						//  column type
						//  column type
	bool Match_Drop_Table(std::string input);  //  drop table
	bool Match_Create_Index(std::string input); // create index on table
	bool Match_Drop_Index(std::string input);   // drop index
	bool Match_Unconditional_Select(std::string input);// select from table 
	bool Match_Conditional_Select(std::string input);  //select from table where
	bool Match_Insert_Column(std::string input);
	bool Match_Unconditional_Delete_Column(std::string input);
	bool Match_Conditional_Delete_Column(std::string input);

	bool Match_Execute_File(std::string input);
	

};
#endif
