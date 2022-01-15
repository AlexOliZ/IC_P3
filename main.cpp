#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <map>
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

int main(int argc, char *argv[])
{
    using namespace std;
    if(argc < 4){
        cout << "missing arguments -> ./a.out <k> <a>" << endl;
        return -1;
    }

    //string filename = argv[1];
    ifstream readfile = ifstream(argv[1], ios::binary);
    // k -> order model; a -> smoothing parameter;
    int k=atoi(argv[2]), a=atoi(argv[3]),i;
    map<string,unsigned int> sequence_table;
    string aux_sequence;
    char byte;
    char* letters_history = (char*) malloc(sizeof(char)*k);
    unsigned int history_pointer=0;
    
    while(readfile.peek() != EOF )
    {
        
        readfile.read((char*)&byte,1);
        letters_history[history_pointer] = byte;
        aux_sequence = "";
        // ter cuidado que nas primeiras k letras não vai ter k letras na 
        // sequence_table para adicionar ao histograma  
        for(i=0; i<k; i++)
        {   
            aux_sequence += letters_history[(history_pointer+i)%k];
            if(sequence_table.find(aux_sequence) != sequence_table.end())
                sequence_table[aux_sequence] += 1;
            else
                sequence_table[aux_sequence] = 1;
        }
        history_pointer = (history_pointer+1) % k;
    }
    return 0;
}