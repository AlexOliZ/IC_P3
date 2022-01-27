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
#include "fcm.h"

class lang
{
    public:
    lang(char* table, char* language_file, unsigned int a, unsigned int k)
    {
        table_file = table;
        lang_file = language_file;
        alpha = a;
        this->k = k;
    };
    lang(){};

    unsigned int check_compression_size(char* fname);
    bool set_file(char* filename);

    private:
        char* table_file;
        char* lang_file;
        unsigned int alpha;
        std::ifstream readfile;
        std::ifstream readtable;
        unsigned int k;
};


#endif