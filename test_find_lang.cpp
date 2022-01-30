#include "lang.h"
// ./exec_find_lang pt/txt2.txt 3 0
int main(int argc, char *argv[])
{
    using namespace std;
    if(argc < 4){
        cout << "missing arguments -> ./exec_lang.out <filename> <k> <a>" << endl;
        return -1;
    }

    //string filename = argv[1];
    string fname = argv[1];
    // k -> order model; a -> smoothing parameter;
    unsigned int k=atoi(argv[2]);
    double alpha=stod(argv[3]);
    
    lang lang_test = lang((char*)fname.data(),NULL,k,alpha);
    char* table_lang = lang_test.find_lang((char*)fname.data());
    cout << "compression_size -> " << table_lang << endl;
    return 0;
}