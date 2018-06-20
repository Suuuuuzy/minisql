#ifndef PAGE_TABLE_H__
#define PAGE_TABLE_H__

class Page_table{


	unsigned int volumn; //current number of pages in page_table

	int* Page_id;  
	int* Page_LSN; // lagrest LSN(latest LSN) which modifies the page in "memory"
	int* RecLSN;   // lagrest LSN(latest LSN) which modifies the page in "disk"
	



};

#endif