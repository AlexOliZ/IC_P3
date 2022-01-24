#ifndef H_LANG
#define H_LANG

#include <iostream>
#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include <map>
#include "math.h"
#include <set>

class lang
{
    public:
    lang(std::string table, std::string language)
    {
        
    };
    lang(){};

    void check_table(char* fname);

    private:
        std::string table_file;
        std::string lang_file;
};


#endif