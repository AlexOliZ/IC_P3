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
#define NUM_LANGS 10
#define NUM_CHARS 122
class lang
{
    public:
    /**
     * @brief Construct a new lang object
     * 
     * @param file filename
     * @param table table to read
     * @param k k value as argument
     * @param a alpha value as argument
     */
    lang(char* file, char* table, unsigned int k, double a)
    {
        lang_file = file;
        table_file = table;
        alpha = a;
        this->k = k;
    };
    lang(){};
    /**
     * @brief check the compression size
     * 
     * @param fname filename
     * @return unsigned int 
     */
    unsigned int check_compression_size(char* fname);
    /**
     * @brief find the language
     * 
     * @param fname filename
     * @return char* 
     */
    char* find_lang(char* fname);
    /**
     * @brief Set the file object
     * 
     * @param filename filename
     * @return true 
     * @return false 
     */
    bool set_file(char* filename);
    /**
     * @brief Get the sequences object
     * 
     * @param fname filename
     */
    void get_sequences(char* fname);
    /**
     * @brief read the created table
     * 
     */
    void read_table();
    /**
     * @brief 
     * 
     * @param fname filename
     * @param read_sequences read the sequences
     * @return double 
     */
    double check_compression(char* fname, bool read_sequences);

    private:
        char* table_file;
        char* lang_file;
        double alpha;
        std::ifstream readfile;
        std::ifstream readtable;
        unsigned int k;
        const char* languages[10] = {"en","pt","french","spanish","german","danish","greek","italian","finnish","dutch"};
        std::map<std::string,std::map<char,unsigned int>> table;
        std::map<std::string,std::map<char,unsigned int>> file_info;
};


#endif