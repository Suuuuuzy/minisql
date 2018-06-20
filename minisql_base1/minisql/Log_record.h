


#ifndef LOG_RECORD_H__
#define LOG_RECORD_H__

#pragma warning(disable:4996)
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include"Global_definition.h"


#define TYPE_PHYSIC_UPDATE 0
#define TYPE_LOGIC_DELETE 1
#define TYPE_LOGIC_INSERT 2
#define TYPE_OPERATION_BEGIN 3
#define TYPE_OPERATION_END 4
#define TYPE_OPERATION_ABORT 5
#define TYPE_TRASACTION_BEGIN 6
#define TYPE_TRASACTION_END 7
#define TYPE_TRASACTION_ABORT 8

/* global variable for static information*/
#define ALLOCATE_NUMBER 100
#define MAX_LOG_LENGTH 800


class Log_record_List{

private:
	char log_buffer[ALLOCATE_NUMBER][MAX_LOG_LENGTH];
//	Single_Record single_record[ALLOCATE_NUMBER];
	
	//void form_single_record(char * filename);

	bool scan_back(char * filename,int *collecting_log_number){
		/* scan the log file from the end to top
		/* format of transacation:
		Operation Type & DATA TYPE & Transaction ID & PrevLsn number & Target Address & Original data & New data 
		Each attribute is seperated by a &
		Thus & cannot be contained in real value*/
		memset(log_buffer,0,sizeof(log_buffer));
		FILE *fp;

		if((fp = fopen(filename,"r+")) == NULL)
		{
			return false;
		}
		char buf[MAX_LOG_LENGTH];
		int i;
		rewind(fp);
		for(i=0;i<ALLOCATE_NUMBER;i++)// it reads ALLOCATE_NUMBER lines tops
		{
			void* address=0;
			if((address=fgets(buf,MAX_LOG_LENGTH,fp)) != NULL)
			{
				strcpy(log_buffer[i],buf);
			}
		}
		i--;
		*collecting_log_number=i;
		return true;
	};



};

class Single_Record{
public:
	unsigned char operation_type;
	int PrevLSN; //last LSN in the same transaction
	unsigned char data_type;
	int target_address;
	void * original_data;
	void * changed_data;
	int transaction_id;
	Single_Record(){
		original_data=new char[MAX_STRING];
		changed_data=new char[MAX_STRING];

	}
	~Single_Record(){

		delete original_data;
		delete changed_data;
		
	}
};
#endif