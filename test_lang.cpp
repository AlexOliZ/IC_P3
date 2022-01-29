#include "lang.h"

int main(int argc, char *argv[])
{
    using namespace std;
    if(argc < 5){
        cout << "missing arguments -> ./exec_lang.out <filename> <lang/table_k.txt> <k> <a>" << endl;
        return -1;
    }

    //string filename = argv[1];
    string fname = argv[1];
    string language = argv[2];
    // k -> order model; a -> smoothing parameter;
    unsigned int k=atoi(argv[3]);
    double alpha=stod(argv[4]);
    
    lang lang_test = lang((char*)fname.data(),(char*)language.data(),k,alpha);
    unsigned int compression_size = lang_test.check_compression_size((char*)language.data());
    cout << "compression_size -> " << compression_size << endl;
    return 0;
}