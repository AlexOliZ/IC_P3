#include "fcm.h"

using namespace std;
int main(int argc, char *argv[])
{
    using namespace std;
    if(argc < 5){
        cout << "missing arguments -> ./exec_fcm.out <k> <a>" << endl;
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


// ./exec_fcm txt1.txt en 3 0
// ./exec_fcm txt2.txt en 3 0
// ./exec_fcm txt3.txt en 3 0
// ./exec_fcm txt4.utf8 en 3 0
// ./exec_fcm txt5.en en 3 0

// ./exec_fcm txt1.utf8 pt 3 0
// ./exec_fcm txt2.txt pt 3 0
// ./exec_fcm txt3.txt pt 3 0
// ./exec_fcm txt4.txt pt 3 0

// ./exec_fcm txt1.utf8 spanish 3 0
// ./exec_fcm txt2.txt spanish 3 0
// ./exec_fcm txt3.txt spanish 3 0
// ./exec_fcm txt4.txt spanish 3 0

// ./exec_fcm txt1.utf8 french 3 0
// ./exec_fcm txt2.txt french 3 0
// ./exec_fcm txt3.txt french 3 0
// ./exec_fcm txt4.txt french 3 0

// ./exec_fcm txt1.txt finnish 3 0
// ./exec_fcm txt2.txt finnish 3 0
// ./exec_fcm txt3.txt finnish 3 0
// ./exec_fcm txt4.txt finnish 3 0

// ./exec_fcm txt1.utf8 italian 3 0
// ./exec_fcm txt2.it italian 3 0
// ./exec_fcm txt3.txt italian 3 0
// ./exec_fcm txt4.txt italian 3 0
// ./exec_fcm txt5.txt italian 3 0

// ./exec_fcm txt1.utf8 german 3 0
// ./exec_fcm txt1.utf8 dutch 3 0
// ./exec_fcm txt1.utf8 danish 3 0
// ./exec_fcm txt1.utf8 greek 3 0
