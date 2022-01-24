#ifndef H_FCM
#define H_FCM

#include <iostream>
#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include <map>
#include "math.h"
#include <set>

class fcm
{
    public:
    fcm(unsigned int k, int alpha, std::string language)
    {
        this->k = k;
        this->alpha = alpha;
        filename = "./"+ language + "/table_"+std::to_string(k)+".txt";
        this->language = language;
        std::ofstream writetable;
        writetable.open((char*)filename.data());
        //std::cout << filename << std::endl;
    };
    fcm(){};

    void read_table(char* fname);

    private:
        std::string filename;
        unsigned int k;
        int alpha;
        std::string language;
};


#endif