#include<iostream>
#include<ctime>
//#include"B_plus_tree.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<regex>
#define TEST_NUMBER 1000
#include"Interpreter.h"

#define BUF_SIZE 1024

#pragma  once


int main()
{

    char* test = "ello";
    char* test2 = "aou";
    cout << test-test2 << endl;
    cout << strcmp(test,test2) << endl;

    
	Interpreter main;
	std::string input_string = ("create table student (sno char(8),sname char(16) unique,sage int,sgender char(1),primary key ( sno ));");
	//std::string input_string = ("execfile a.txt;");
	std::cout << input_string << std::endl;
	main.Translate(input_string);
    
//    std::string input_string_2 = ("drop table student;");
//    //std::string input_string = ("execfile a.txt;");
//    std::cout << input_string_2 << std::endl;
//    main.Translate(input_string_2);
//    
    
//    std::string input_string_3 = ("create index index1 on student(sno);");
//    //std::string input_string = ("execfile a.txt;");
//    std::cout << input_string_3 << std::endl;
//    main.Translate(input_string_3);
//    
//    
//    std::string input_string_4 = ("drop index inde1;");
//    //std::string input_string = ("execfile a.txt;");
//    std::cout << input_string_4 << std::endl;
//    main.Translate(input_string_4);
//    
//
//    std::string input_string_5 = ("select * from student;");
//    //std::string input_string = ("execfile a.txt;");
//    std::cout << input_string_5 << std::endl;
//    main.Translate(input_string_5);
//    
//    std::string input_string_6 = ("select * from student where sno='88888' and sname='yudfyusyfi';");
//    //std::string input_string = ("execfile a.txt;");
//    std::cout << input_string_6 << std::endl;
//    main.Translate(input_string_6);
//    
    
//    std::string input_string_7 = ("delete from student where sn='1';");
//    //std::string input_string = ("execfile a.txt;");
//    std::cout << input_string_7 << std::endl;
//    main.Translate(input_string_7);
//    
    std::string input_string_8 = ("insert into student values ('12345678','wy',22,'M');");
    //std::string input_string = ("execfile a.txt;");
    std::cout << input_string_8 << std::endl;
    main.Translate(input_string_8);
    
    

    
    
	/*
	for (int random_seed = 0; random_seed < 100000; random_seed++)
	{

		srand(random_seed);

		//cout<<"SEED: "<<random_seed<<endl;
		struct node_key a[TEST_NUMBER];

		B_plus_tree main_tree = B_plus_tree(TYPE_INT);//input int as test
		for (int j = 0; j < 1; j++)
		{

			for (int i = 0; i < TEST_NUMBER; i++)
			{
				a[i].type_int = rand();
				//cout<<"Insert A value "<< a[i].type_int<<"\t"<<"i: "<<i<<endl;

				main_tree.InsertNodeWithKey(a[i], TYPE_INT, (int)&a[i], 0);


				//cout<<"\n\n\n\n\n\n"<<endl;
				//if(a[i].type_int==44 || a[i].type_int==35)
				//main_tree.DisplayAllValue();
			}

			//main_tree.DisplayFromLeftToRight();

		}
		//cout<<"Congragulations for inserting!"<<endl;

		//main_tree.DisplayAllValue();//after

		for (int i = 0; i < TEST_NUMBER; i++)
		{

			//	main_tree.DisplayHead();//before
			//	cout<<"Tree before finished*************************************************************************"<<endl;
			//cout<<"Delete: "<<i<<" With value : "<< a[i].type_int<<endl;


			main_tree.DeleteWithKey(a[i], TYPE_INT);

			//main_tree.DisplayAllValue();//after
			//
			//main_tree.DisplayHead();
		}

	}
	//main_tree.DisplayAllValue();
	*/
	system("pause");

	


	return 0;

}
