#include"Log_record.h"
/*
void Log_record_List::form_single_record(char * filename){

	
		int collecting_log_number=0;
		if(scan_back(filename,&collecting_log_number)==true)
		{
			// successfully scanned, scanned information is stored in log_buffer
			// split the string 
			//char s[] = "a,b*c,d";
			for(int i=0;i<collecting_log_number;i++)
			{
				const char *sep = "&"; //可按多个字符来分割
				char *p;
				p = strtok(log_buffer[i], sep);
				//Operation Type & DATA TYPE & Transaction ID & PrevLsn number & Target Address & Original data & New data 
				// Operation Type
				single_record[i].operation_type =atoi(p);
				p = strtok(NULL, sep);
				// DATA TYPE
				single_record[i].data_type = atoi(p);
				p = strtok(NULL, sep);
				//Transaction ID
				single_record[i].transaction_id = atoi(p);
				p = strtok(NULL, sep);
				//PrevLsn number
				single_record[i].PrevLSN = atoi(p);
				p = strtok(NULL, sep);
				//Target Address
				single_record[i].target_address=atoi(p);
				// Original data
				switch(single_record[i].data_type){
					//case TYPE_INT: int * t=(int)single_record[i].original_data[0];
					//			   *t =atoi(p);// place original data into this position


				}
			}
		}
		else{


		}

		
}
*/
