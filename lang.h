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
#define NUM_LANGS 11
#define NUM_CHARS 122
class lang
{
    public:
    lang(char* file, char* table, unsigned int k, double a)
    {
        lang_file = file;
        table_file = table;
        alpha = a;
        this->k = k;
    };
    lang(){};

    unsigned int check_compression_size(char* fname);
    char* find_lang(char* fname);
    bool set_file(char* filename);
    void get_sequences(char* fname);
    void read_table();
    double check_compression(char* fname, bool read_sequences);

    private:
        char* table_file;
        char* lang_file;
        double alpha;
        std::ifstream readfile;
        std::ifstream readtable;
        unsigned int k;
        const char* languages[11] = {"en","pt","french","spanish","german","danish","greek","italian","finnish","danish","dutch"};
        std::map<std::string,std::map<char,unsigned int>> table;
        std::map<std::string,std::map<char,unsigned int>> file_info;
};


#endif