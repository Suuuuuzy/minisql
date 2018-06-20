#ifndef GLOBAL_DEFINITION_H__
#define GLOBAL_DEFINITION_H__

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_CHAR 2


#define MAX_STRING 288
#define NAME_LENGTH 128

#pragma pack(1) 

class Property{
    
public:
    char property_name[NAME_LENGTH];
    int type;
    bool is_unique;
    bool is_primary_key;
    int char_capacity;//if it's char
    Property() {
        memset(property_name, 0, sizeof(property_name));
        type = TYPE_INT;
        is_unique = false;
        is_primary_key = false;
        char_capacity = -1;
    }
    void  initial() {
        memset(property_name, 0, sizeof(property_name));
        type = TYPE_INT;
        is_unique = false;
        is_primary_key = false;
        char_capacity = -1;
    }
};

class Condition {
public:
    char column_name[NAME_LENGTH];
    int op_type;
    int value_type;
    char character_buffer[MAX_STRING];
    float value;//if it's int, store as float
    void  initial() {
        memset(column_name, 0, sizeof(column_name));
        memset(character_buffer, 0, sizeof(character_buffer));
        op_type = 0;
        value_type = TYPE_INT;
        value = 0;
    }
};

#endif
