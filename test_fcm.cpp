#include "fcm.h"
/*
 * Develop a program, named fcm, with the aim of collecting 
 * statistical information about texts, using finite-context 
 * models. The order of the model, k, as well as the smoothing 
 * parameter, α, should be parameters passed to the program. 
 * This program should provide the entropy of the text, 
 * as estimated by the model.
*/
/*
struct stats{
    std::string sequence;
    unsigned int count=0;
};
*/
// g++ test_fcm.cpp fcm.cpp -o exec_fcm
// ./exec_fcm test.txt en 3 0
// ./exec_fcm europarl-v7.it-en.en en 3 0
// ./exec_fcm txt1.utf8 en 3 0
// ./exec_fcm txt1.utf8 pt 3 0
int main(int argc, char *argv[])
{
    using namespace std;
    if(argc < 5){
        cout << "missing arguments -> ./exec_fcm.out <filename> <language (pt/en)> <k> <a>" << endl;
        return -1;
    }

    //string filename = argv[1];
    string fname = argv[1];
    string language = argv[2];
    // k -> order model; a -> smoothing parameter;
    int k=atoi(argv[3]), alpha=atoi(argv[4]),i;
    
    fcm fcm_table = fcm(k,alpha,language);
    fcm_table.read_table((char*) fname.data());

    return 0;
}