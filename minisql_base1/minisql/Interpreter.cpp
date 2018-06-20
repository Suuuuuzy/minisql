#include"Interpreter.h"


Interpreter::Interpreter()
{
	catlog = new CatlogManage("new.bin");

}
Interpreter::~Interpreter()
{
	delete catlog;
}
bool Interpreter::Translate(std::string input){
	if (Match_Create_Table(input))
	{
        catlog->show();
		catlog->CreateTable(s_table_name, t_property_group, property_used);
        catlog->show();


		std::cout << "Match create table" << std::endl;
		std::cout << "Table Name: " << s_table_name << std::endl;
		for (int i = 0; i < property_used; i++) {
			std::cout << "Index number : " << i << std::endl;
			std::cout << "property_name : " << t_property_group[i].property_name << std::endl;
			std::cout << "is_primary_key : " << t_property_group[i].is_primary_key << std::endl;
			std::cout << "is_unique : " << t_property_group[i].is_unique << std::endl;
			std::cout << "type : " << t_property_group[i].type << std::endl;
			std::cout << "char_capacity : " << t_property_group[i].char_capacity << std::endl;
		}
		return true;
	}
	else if(Match_Drop_Table(input)){
		
        catlog->DropTable(s_table_name);
        catlog->show();
        
		std::cout << "Match drop table " << std::endl;
		std::cout << "Table name: " << s_table_name << std::endl;
		return true;
	}
	else if (Match_Create_Index(input)) {
		
        catlog->CreateIndex(s_index_name, s_table_name, t_property_group[0].property_name);
        catlog->show();
        
        
		std::cout << "Match create index" << std::endl;
		std::cout << "Index name: "<<s_index_name << std::endl;
		std::cout << "Table name: " << s_table_name << std::endl;
		std::cout << "Column name: " << t_property_group[0].property_name << std::endl;
		return true;
	}
	else if (Match_Drop_Index(input)) {
		catlog->DropIndex(s_index_name);
        catlog->show();
        
		std::cout << "Match drop index" << std::endl;
		std::cout << "Index name: " << s_index_name << std::endl;
		return true;
	}   // drop index
	else if (Match_Unconditional_Select(input)) {
        catlog->show();
		
        catlog->SelectORDelete(s_table_name, t_select_condition, SELECT, condition_used);
        
        catlog->show();
        
		std::cout << "Match unconditional select" << std::endl;
		std::cout << "Table name: " << s_table_name << std::endl;
		return true;
	}// select from table 
	else if (Match_Conditional_Select(input)) {
		
        
        catlog->SelectORDelete(s_table_name, t_select_condition, SELECT, condition_used);
        catlog->show();
        
		//select from table where
		
		std::cout << "Match conditional select" << std::endl;
		std::cout << "Table Name: " << s_table_name << std::endl;

		for (int i = 0; i < condition_used; i++) {
			std::cout << "Index number : " << i << std::endl;
			std::cout << "column_name : " << t_select_condition[i].column_name << std::endl;
			std::cout << "op_type : " << t_select_condition[i].op_type << std::endl;
			std::cout << "value_type : " << t_select_condition[i].value_type << std::endl;
			std::cout << "character_buffer : " << t_select_condition[i].character_buffer << std::endl;
			std::cout << "value : " << t_select_condition[i].value << std::endl;
		}
		
		return true;
	}
	else if (Match_Insert_Column(input)) {
        
        
		catlog->Insert(s_table_name, t_select_condition, condition_used);
        catlog->show();
        


		std::cout << "Match insert column" << std::endl;
		std::cout << "Table Name: " << s_table_name << std::endl;
		for (int i = 0; i < condition_used; i++) {
			std::cout << "Index number : " << i << std::endl;
			std::cout << "column_name : " << t_select_condition[i].column_name << std::endl;
			std::cout << "op_type : " << t_select_condition[i].op_type << std::endl;
			std::cout << "value_type : " << t_select_condition[i].value_type << std::endl;
			std::cout << "character_buffer : " << t_select_condition[i].character_buffer << std::endl;
			std::cout << "value : " << t_select_condition[i].value << std::endl;
		}
		return true;
	}
	else if(Match_Unconditional_Delete_Column(input)) {

		catlog->SelectORDelete(s_table_name, t_select_condition, DELETE, condition_used);
        catlog->show();
        
        
		std::cout << "Match unconditional delete" << std::endl;
		std::cout << "Table name: " << s_table_name << std::endl;

		return true;
	}
	else if (Match_Conditional_Delete_Column(input)) {
		
        catlog->SelectORDelete(s_table_name, t_select_condition, DELETE, condition_used);
        catlog->show();
        
		std::cout << "Match conditional delete column" << std::endl;
		std::cout << "Table Name: " << s_table_name << std::endl;
		for (int i = 0; i < condition_used; i++) {
			std::cout << "Index number : " << i << std::endl;
			std::cout << "column_name : " << t_select_condition[i].column_name << std::endl;
			std::cout << "op_type : " << t_select_condition[i].op_type << std::endl;
			std::cout << "value_type : " << t_select_condition[i].value_type << std::endl;
			std::cout << "character_buffer : " << t_select_condition[i].character_buffer << std::endl;
			std::cout << "value : " << t_select_condition[i].value << std::endl;
		}
		return true;
	}

	else if (Match_Execute_File(input) == true)
	{

		std::cout << "Match Execute file" << std::endl;
		std::cout << "File name: " << s_file_name<<   std::endl;
		std::ifstream in;
		in.open(s_file_name, std::ios::in);
		if(!in.is_open())
		{
			 std::cout << "Error opening file, file doesn't exist or cannot be opened "<< s_file_name<<std::endl; 
		}
		else {
			std::string instruction="";
			std::string temp_instruction = "";
			while (!in.eof())
			{
				std::getline(in, temp_instruction);
				while (1) {
					std::string::size_type idx = temp_instruction.find(";");//‘⁄a÷–≤È’“b.
					if (idx == std::string::npos)
					{
						instruction += temp_instruction;
						break;
					}
					else
					{
						instruction += temp_instruction.substr(0, idx+1);//find a full instruction
						std::cout << instruction << std::endl;
						Translate(instruction);
						instruction = "";
						temp_instruction = temp_instruction.substr(idx + 1);
					}
				}
			}
		}
	}
	else {

		std::cout << "Error, syntax unrecognized, transcation terminated " << std::endl;

	}
    return false;
}


bool Interpreter::Match_Create_Table(std::string input) {
	//return NULL as success
	
	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*create[\\s\\t\\n]+table[\\s\\t\\n]+(\\w+)[\\s\\t\\n]*\\(([\\s\\S]*),[\\n\\s\\t]*primary[\\n\\s\\t]+key[\\n\\s\\t]*\\([\\n\\s\\t]*(\\w+)[\\n\\s\\t]*\\)[\\n\\s\\t]*\\)[\\s\\t\\n]*;[\\n\\s\\t;]*");
	std::regex r(pattern);
	
	bool match = std::regex_match(input_lower, result, r);
	
	if (match == false)
	{

		return false;
	}
	std::string table_name= result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	
	std::string property = result[2];
	std::string primary_key = result[3];
	if (property.length() > PROPERTY_LENGTH)
	{
		std::cout << "Error, too much property" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());

	char t[PROPERTY_LENGTH];

	strcpy(t, property.c_str());
	int current_property_group_pointer = 0;
	char *pch = strtok(t, ",");
	
	pattern="[\\n\\s\\t]*(\\w+)[\\n\\s\\t]+(int|float|char)[\\n\\s\\t]*(\\([\\n\\s\\t]*(\\d+)[\\n\\s\\t]*\\))?[\\n\\s\\t]*(unique)?[\\n\\s\\t]*";


	std::regex r1(pattern);
	int primary_key_set = 0;
	while (pch != NULL)
	{
		if (current_property_group_pointer >= PROPERTY_MAX)
		{
			std::cout << "Error: property number too large" << std::endl;
			return false;
		}
		t_property_group[current_property_group_pointer].initial();
		std::string t_s_match(pch);
		bool match = std::regex_match(t_s_match, result, r1);
		if (match == false)
		{
			std::cout << "Error, syntax error in property " << current_property_group_pointer << std::endl;
			return false;
		}
		std::string property_name = result[1];
		std::string property_type = result[2];
		std::string char_number = result[4];
		std::string unique = result[5];
		if (property_name.length() + 1 >= NAME_LENGTH)
		{
			std::cout << "Error, property name out of length " << current_property_group_pointer << std::endl;
			return false;
		}
		strcpy(t_property_group[current_property_group_pointer].property_name, property_name.c_str());
		if (primary_key.compare(t_property_group[current_property_group_pointer].property_name) == 0)
		{
			//set primary key
			primary_key_set++;
			t_property_group[current_property_group_pointer].is_primary_key = true;
		}
		t_property_group[current_property_group_pointer].is_unique = (unique.compare("") == 0) ? false : true;

		if (property_type.compare("char") != 0)
		{
			//int character
			t_property_group[current_property_group_pointer].type = (property_type.compare("int") == 0) ? TYPE_INT : TYPE_FLOAT;
			if (property_type.compare("int") == 0)
			{
				t_property_group[current_property_group_pointer].char_capacity = sizeof(int);
			}
			else{
				t_property_group[current_property_group_pointer].char_capacity = sizeof(float);
			}
		}
		else {
			//char
			int char_cap = std::stoi(char_number, NULL, 10);
			if (char_cap >= MAX_STRING)
				return "Error, char exceeds maximum limitation";
			t_property_group[current_property_group_pointer].type = TYPE_CHAR;
			t_property_group[current_property_group_pointer].char_capacity = char_cap;
		}
		current_property_group_pointer++;
		pch = strtok(NULL, ",");
	}
	if (primary_key_set == 0)
	{
		std::cout << "Error, primary key is not set" << std::endl;
		return false;
	}
	if (primary_key_set >1)
	{
		std::cout << "Error, multiple primary keys are assigned" << std::endl;
		return false;
	}
	property_used = current_property_group_pointer;
	//successfully assigned 
	return true;
}

void Interpreter::Display_group() {


}

bool Interpreter::Match_Drop_Table(std::string input) {  //  drop table


	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*drop[\\s\\t\\n]+table[\\s\\t\\n]+(\\w+)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);

	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
		return false;
	std::string table_name = result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());
	return true;
}

bool Interpreter::Match_Create_Index(std::string input) {



	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*create[\\s\\t\\n]+index[\\s\\t\\n]+(\\w+)[\\s\\t\\n]+on[\\s\\t\\n]+(\\w+)[\\s\\t\\n]*\\([\\s\\t\\n]*(\\w+)[\\s\\t\\n]*\\)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);
	//result[1] index_name
	//result[2] table_name
	//result[3] column_name
	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
		return false;


	std::string index_name = result[1];//index name
	if (index_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, index name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_index_name, index_name.c_str());

	std::string table_name = result[2];//table name
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());


	std::string column_name = result[3];//property name(column name), stores in property[0].property_name
	if (column_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, column name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(t_property_group[0].property_name, column_name.c_str());


	return true;

}


bool Interpreter::Match_Drop_Index(std::string input) {   // drop index


	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*drop[\\s\\t\\n]+index[\\s\\t\\n]+(\\w+)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);

	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
		return false;
	std::string index_name = result[1];
	if (index_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, index name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_index_name, index_name.c_str());
	return true;

}
bool Interpreter::Match_Unconditional_Select(std::string input) {// select from table 

	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*select[\\s\\t\\n]*\\*[\\s\\t\\n]*from[\\s\\t\\n]+(\\w+)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);

	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
		return false;
	std::string table_name = result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());
	condition_used = 0;
	return true;

}
bool Interpreter::Match_Conditional_Select(std::string input) {  //select from table where
																 //return NULL as success

	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	size_t pos = input_lower.find(" and ");//change every and to &
	while (pos != std::string::npos)
	{
		input_lower.replace(pos, 5, " & ");
		pos = input_lower.find(" and ");
	}


	std::smatch result;
	std::string pattern("[\\s\\t\\n]*select[\\s\\t\\n]*\\*[\\s\\t\\n]*from[\\s\\t\\n]+(\\w+)[\\s\\t\\n]+where[\\s\\t\\n]+([\\s\\t\\n]*\\w+[\\s\\t\\n]*[>=<]+[\\s\\t\\n]*(\\d+|\\d+\\.\\d+|\'[^\']*\'|\"[^\"]*\")[\\s\\t\\n]*)((&[\\s\\t\\n]*\\w+[\\s\\t\\n]*[>=<]+[\\s\\t\\n]*(\\d+|\\d+\\.\\d+|\'[^\']*\'|\"[^\"]*\")[\\s\\t\\n]*)*)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);
	// result[1] table_name 
	// result[2] condition_1
	// result[4] condition_remaining
	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
	{
		return false;
	}
	std::string table_name = result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());
	std::string first_condition = result[2];
	std::string remaining_condition = result[4];

	//single_condition pattern
	pattern = "[\\n\\s\\t]*(\\w+)[\\n\\s\\t]*(>|<|>=|<=|=|<>)[\\n\\s\\t]*((\\d+)|(\\d+\\.\\d+)|\'([^\']*)\'|\"([^\"]*)\")[\\n\\s\\t]*";
	// result[1] column name
	// result[2] op
	// result[3] total_not_used
	// result[4] match_int
	// result[5] match_float
	// result[6] match " "
	// result[7] match ' '

	int current_condition_pointer = 0;
	std::regex r1(pattern);





	std::string t_s_match(first_condition.c_str());
	
	match = std::regex_match(t_s_match, result, r1);
	if (match == false)
	{
		std::cout << "Error, syntax error in where condition " << current_condition_pointer << std::endl;
		return false;
	}
	std::string column_name = result[1];
	std::string op = result[2];
	std::string match_int = result[4];
	std::string match_float = result[5];
	std::string match_char_single = result[6];
	std::string match_char_double = result[7];
	t_select_condition[current_condition_pointer].initial();
	strcpy(t_select_condition[current_condition_pointer].column_name, column_name.c_str());

	if (column_name.length() + 1 >= MAX_STRING)
	{
		std::cout << "Error, column_name exceeds limitation in where condition: " << current_condition_pointer << std::endl;
	}
	if (op.compare(">=")==0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER_EQUAL;
	else if (op.compare(">") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER;
	else if(op.compare("<=") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER_EQUAL;
	else if(op.compare("<") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER;
	else if(op.compare("=") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_EQUAL;
	else if(op.compare("<>") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_NOT_EQUAL;
	else {
		std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x000" << std::endl;
		exit(1);
	}
	if (match_int.compare("") != 0)
	{
		//match int
		t_select_condition[current_condition_pointer].value_type = TYPE_INT;
		t_select_condition[current_condition_pointer].value = atoi(match_int.c_str());

	}
	else if(match_float.compare("") != 0){
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_FLOAT;
		t_select_condition[current_condition_pointer].value = atof(match_int.c_str());

	}
	else if (match_char_single.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
		strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_single.c_str());
	}
	else if (match_char_double.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
		strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_double.c_str());
	}
	else {
		std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x001" << std::endl;
		exit(1);
	}

	current_condition_pointer++;



	char t[PROPERTY_LENGTH];

	strcpy(t, remaining_condition.c_str());
	if (t[0] == 0)
	{
		//no further condition
		condition_used = current_condition_pointer;

		return true;
	}

	char *pch = strtok(t, "&");
	while (pch != NULL)
	{
		if (current_condition_pointer >= PROPERTY_MAX)
		{
			std::cout << "Error: condition number too large" << std::endl;
			return false;
		}

		std::string t_s_match(pch);
		bool match = std::regex_match(t_s_match, result, r1);
		if (match == false)
		{
			std::cout << "Error, syntax error in where condition " << current_condition_pointer << std::endl;
			return false;
		}
		std::string column_name = result[1];
		std::string op = result[2];
		std::string match_int = result[4];
		std::string match_float = result[5];
		std::string match_char_single = result[6];
		std::string match_char_double = result[7];
		t_select_condition[current_condition_pointer].initial();

		strcpy(t_select_condition[current_condition_pointer].column_name, column_name.c_str());

		if (column_name.length() + 1 >= MAX_STRING)
		{
			std::cout << "Error, column_name exceeds limitation in where condition: " << current_condition_pointer << std::endl;
		}
		if (op.compare(">=")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER_EQUAL;
		else if (op.compare(">")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER;
		else if (op.compare("<=")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER_EQUAL;
		else if (op.compare("<")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER;
		else if (op.compare("=")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_EQUAL;
		else if (op.compare("<>")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_NOT_EQUAL;
		else {
			std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x000" << std::endl;
			exit(1);
		}
		if (match_int.compare("") != 0)
		{
			//match int
			t_select_condition[current_condition_pointer].value_type = TYPE_INT;
			t_select_condition[current_condition_pointer].value = atoi(match_int.c_str());

		}
		else if (match_float.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_FLOAT;
			t_select_condition[current_condition_pointer].value = atof(match_int.c_str());

		}
		else if (match_char_single.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
			strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_single.c_str());
		}
		else if (match_char_double.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
			strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_double.c_str());
		}
		else {
			std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x001" << std::endl;
			exit(1);
		}

		current_condition_pointer++;

		pch = strtok(NULL, "&");
	}

	condition_used = current_condition_pointer;
	//successfully assigned 
	return true;

}
bool Interpreter::Match_Insert_Column(std::string input) {
	std::string input_lower;
	//result store in condition
	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*insert[\\s\\t\\n]+into[\\s\\t\\n]+(\\w+)[\\s\\t\\n]+values[\\s\\t\\n]*\\([\\s\\t\\n]*(\'[^\']*\'|\"[^\"]*\"|\\d+|\\d+\\.\\d+)[\\s\\t\\n]*((,[\\s\\t\\n]*(\'[^\']*\'|\"[^\"]*\"|\\d+|\\d+\\.\\d+)[\\s\\t\\n]*)*)\\)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);

	// result[1] table_name 
	// result[2] first_value
	// result[4] remaining_value
	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
	{
		return false;
	}
	std::string table_name = result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());

	std::string first_value = result[2];
	std::string remaining_value = result[3];
	std::cout << "remaining_value : " << remaining_value << std::endl;
	//single_condition pattern
	pattern = "[\\s\\t\\n]*(\'([^\']*)\'|\"([^\"])*\"|(\\d+)|(\\d+\\.\\d+))[\\s\\t\\n]*";
	// result[1] not_used
	// result[2] match ' '
	// result[3] match " "
	// result[4] match_int
	// result[5] match_float


	int current_condition_pointer = 0;
	std::regex r1(pattern);





	std::string t_s_match(first_value.c_str());

	match = std::regex_match(t_s_match, result, r1);
	if (match == false)
	{
		std::cout << "Error, syntax error in insert value index:  " << current_condition_pointer << std::endl;
		return false;
	}
	std::string match_int = result[4];
	std::string match_float = result[5];
	std::string match_char_single = result[2];
	std::string match_char_double = result[3];
	t_select_condition[current_condition_pointer].initial();
	if (match_int.compare("") != 0)
	{
		//match int
		t_select_condition[current_condition_pointer].value_type = TYPE_INT;
		t_select_condition[current_condition_pointer].value = atoi(match_int.c_str());

	}
	else if (match_float.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_FLOAT;
		t_select_condition[current_condition_pointer].value = atof(match_int.c_str());

	}
	else if (match_char_single.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
		strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_single.c_str());
	}
	else if (match_char_double.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
		strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_double.c_str());
	}
	else {
		std::cout << " Expected error in Match_Insert_Column, repair the system, Code 0x001" << std::endl;
		exit(1);
	}

	current_condition_pointer++;



	char t[PROPERTY_LENGTH];

	strcpy(t, remaining_value.c_str());
	if (t[0] == 0)
		//no further value
		return true;

	char *pch = strtok(t, ",");
	while (pch != NULL)
	{
		if (current_condition_pointer >= PROPERTY_MAX)
		{
			std::cout << "Error: condition number too large" << std::endl;
			return false;
		}
		std::string t_s_match(pch);

		bool match = std::regex_match(t_s_match, result, r1);
		if (match == false)
		{
			std::cout << "Error, syntax error in insert value index:  " << current_condition_pointer << std::endl;
			return false;
		}
		std::string match_int = result[4];
		std::string match_float = result[5];
		std::string match_char_single = result[2];
		std::string match_char_double = result[3];

		t_select_condition[current_condition_pointer].initial();

		if (match_int.compare("") != 0)
		{
			//match int
			t_select_condition[current_condition_pointer].value_type = TYPE_INT;
			t_select_condition[current_condition_pointer].value = atoi(match_int.c_str());

		}
		else if (match_float.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_FLOAT;
			t_select_condition[current_condition_pointer].value = atof(match_int.c_str());

		}
		else if (match_char_single.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
			strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_single.c_str());
		}
		else if (match_char_double.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
			strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_double.c_str());
		}
		else {
			std::cout << " Expected error in Match_Insert_Column, repair the system, Code 0x001" << std::endl;
			exit(1);
		}

		current_condition_pointer++;

		pch = strtok(NULL, ",");
	}

	condition_used = current_condition_pointer;
	return true;
}
bool Interpreter::Match_Unconditional_Delete_Column(std::string input) {

	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*delete[\\s\\t\\n]+from[\\s\\t\\n]+(\\w+)[\\s\\t\\n]*;[\\s\\t\\n]*");
	std::regex r(pattern);

	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
		return false;
	std::string table_name = result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());
	condition_used = 0;
	return true;


}

bool Interpreter::Match_Conditional_Delete_Column(std::string input) {

	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	size_t pos = input_lower.find(" and ");//change every and to &
	while (pos != std::string::npos)
	{
		input_lower.replace(pos, 5, " & ");
		pos = input_lower.find(" and ");
	}


	std::smatch result;
	std::string pattern("[\\s\\t\\n]*delete[\\s\\t\\n]*from[\\s\\t\\n]+(\\w+)[\\s\\t\\n]+where[\\s\\t\\n]+([\\s\\t\\n]*\\w+[\\s\\t\\n]*[>=<]+[\\s\\t\\n]*(\\d+|\\d+\\.\\d+|\'[^\']*\'|\"[^\"]*\")[\\s\\t\\n]*)((&[\\s\\t\\n]*\\w+[\\s\\t\\n]*[>=<]+[\\s\\t\\n]*(\\d+|\\d+\\.\\d+|\'[^\']*\'|\"[^\"]*\")[\\s\\t\\n]*)*)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);
	// result[1] table_name 
	// result[2] condition_1
	// result[4] condition_remaining
	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
	{
		return false;
	}
	std::string table_name = result[1];
	if (table_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, table name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_table_name, table_name.c_str());
	std::string first_condition = result[2];
	std::string remaining_condition = result[4];

	//single_condition pattern
	pattern = "[\\n\\s\\t]*(\\w+)[\\n\\s\\t]*(>|<|>=|<=|=|<>)[\\n\\s\\t]*((\\d+)|(\\d+\\.\\d+)|\'([^\']*)\'|\"([^\"]*)\")[\\n\\s\\t]*";
	// result[1] column name
	// result[2] op
	// result[3] total_not_used
	// result[4] match_int
	// result[5] match_float
	// result[6] match " "
	// result[7] match ' '

	int current_condition_pointer = 0;
	std::regex r1(pattern);





	std::string t_s_match(first_condition.c_str());

	match = std::regex_match(t_s_match, result, r1);
	if (match == false)
	{
		std::cout << "Error, syntax error in where condition " << current_condition_pointer << std::endl;
		return false;
	}
	std::string column_name = result[1];
	std::string op = result[2];
	std::string match_int = result[4];
	std::string match_float = result[5];
	std::string match_char_single = result[6];
	std::string match_char_double = result[7];
	t_select_condition[current_condition_pointer].initial();

	strcpy(t_select_condition[current_condition_pointer].column_name, column_name.c_str());

	if (column_name.length() + 1 >= MAX_STRING)
	{
		std::cout << "Error, column_name exceeds limitation in where condition: " << current_condition_pointer << std::endl;
	}
	if (op.compare(">=")==0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER_EQUAL;
	else if (op.compare(">") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER;
	else if (op.compare("<=") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER_EQUAL;
	else if (op.compare("<") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER;
	else if (op.compare("=") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_EQUAL;
	else if (op.compare("<>") == 0)
		t_select_condition[current_condition_pointer].op_type = CONDITION_NOT_EQUAL;
	else {
		std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x000" << std::endl;
		exit(1);
	}
	if (match_int.compare("") != 0)
	{
		//match int
		t_select_condition[current_condition_pointer].value_type = TYPE_INT;
		t_select_condition[current_condition_pointer].value = atoi(match_int.c_str());

	}
	else if (match_float.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_FLOAT;
		t_select_condition[current_condition_pointer].value = atof(match_int.c_str());

	}
	else if (match_char_single.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
		strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_single.c_str());
	}
	else if (match_char_double.compare("") != 0) {
		//match float
		t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
		strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_double.c_str());
	}
	else {
		std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x001" << std::endl;
		exit(1);
	}

	current_condition_pointer++;



	char t[PROPERTY_LENGTH];

	strcpy(t, remaining_condition.c_str());
	if (t[0] == 0)
	{
		//no further condition
		condition_used = current_condition_pointer;

		return true;
	}
	char *pch = strtok(t, "&");
	while (pch != NULL)
	{
		if (current_condition_pointer >= PROPERTY_MAX)
		{
			std::cout << "Error: condition number too large" << std::endl;
			return false;
		}
		std::string t_s_match(pch);

		bool match = std::regex_match(t_s_match, result, r1);
		if (match == false)
		{
			std::cout << "Error, syntax error in where condition " << current_condition_pointer << std::endl;
			return false;
		}
		std::string column_name = result[1];
		std::string op = result[2];
		std::string match_int = result[4];
		std::string match_float = result[5];
		std::string match_char_single = result[6];
		std::string match_char_double = result[7];
		t_select_condition[current_condition_pointer].initial();

		strcpy(t_select_condition[current_condition_pointer].column_name, column_name.c_str());

		if (column_name.length() + 1 >= MAX_STRING)
		{
			std::cout << "Error, column_name exceeds limitation in where condition: " << current_condition_pointer << std::endl;
		}
		if (op.compare(">=")==0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER_EQUAL;
		else if (op.compare(">") == 0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_LARGER;
		else if (op.compare("<=") == 0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER_EQUAL;
		else if (op.compare("<") == 0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_SMALLER;
		else if (op.compare("=") == 0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_EQUAL;
		else if (op.compare("<>") == 0)
			t_select_condition[current_condition_pointer].op_type = CONDITION_NOT_EQUAL;
		else {
			std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x000" << std::endl;
			exit(1);
		}
		if (match_int.compare("") != 0)
		{
			//match int
			t_select_condition[current_condition_pointer].value_type = TYPE_INT;
			t_select_condition[current_condition_pointer].value = atoi(match_int.c_str());

		}
		else if (match_float.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_FLOAT;
			t_select_condition[current_condition_pointer].value = atof(match_int.c_str());

		}
		else if (match_char_single.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
			strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_single.c_str());
		}
		else if (match_char_double.compare("") != 0) {
			//match float
			t_select_condition[current_condition_pointer].value_type = TYPE_CHAR;
			strcpy(t_select_condition[current_condition_pointer].character_buffer, match_char_double.c_str());
		}
		else {
			std::cout << " Expected error in Match_Conditional_Select, repair the system, Code 0x001" << std::endl;
			exit(1);
		}

		current_condition_pointer++;

		pch = strtok(NULL, "&");
	}

	condition_used = current_condition_pointer;
	//successfully assigned 
	return true;

}
bool Interpreter::Match_Execute_File(std::string input) {

	std::string input_lower;

	transform(input.begin(), input.end(), back_inserter(input_lower), ::toupper);
	transform(input.begin(), input.end(), input_lower.begin(), ::tolower);// transfer the input to lower case

	std::smatch result;
	std::string pattern("[\\s\\t\\n]*execfile[\\s\\t\\n]+([\\w\\.]+)[\\s\\t\\n]*;[\\s\\t\\n;]*");
	std::regex r(pattern);

	bool match = std::regex_match(input_lower, result, r);
	if (match == false)
		return false;
	std::string file_name = result[1];
	if (file_name.length() + 1 >= NAME_LENGTH)
	{
		std::cout << "Error, file name exceeds maximum limitation" << std::endl;
		return false;
	}
	strcpy(s_file_name, file_name.c_str());
	return true;
}
