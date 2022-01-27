#ifndef H_FCM
#define H_FCM

#include <iostream>
#include <iostream>
#include <fstream>
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
        writetable = std::ofstream((char*)filename.data(), std::ios::binary|std::ios_base::app);
        writetable.close();
        
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