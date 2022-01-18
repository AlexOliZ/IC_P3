#include "fcm.h"

using namespace std;

void fcm::read_table(char* fname)
{
    // antes de começar a ler o novo histograma
    // dar load ao ficheiro se tiver a tabela escrita
    //ifstream readtable = ifstream((char*)filename.data(), ios::binary);
    
    string path = "./"+ language + "/" +fname;
    cout << path << endl;
    ifstream readfile = ifstream((char*) path.data(), ios::binary);
    map<string,map<char,unsigned int>> sequence_table;
    string aux_sequence;
    char byte;
    char* letters_history = (char*) malloc(sizeof(char)*k);
    unsigned int history_pointer=k-1;
    int i;
    
    // preencher os primeiros k-1 chars no circular_buffer
    // 
    for(i=0; i<k-1; i++)
        readfile.read((char*) &letters_history[i],1);
    
    //while(readfile.peek() != EOF )
    while(1)
    {
        if(readfile.eof()){
            break;
        }
        readfile.read((char*) &byte,1);
        if(byte != '\n' && byte != '\t'){
            letters_history[history_pointer] = byte;
            aux_sequence = "";
            
            // ter cuidado que nas primeiras k letras não vai ter k letras na 
            // sequence_table para adicionar ao histograma  
            for(i=k-1; i>=0; i--)
            {   
                aux_sequence += letters_history[(history_pointer+i)%k];
            }

            if(sequence_table.find(aux_sequence) != sequence_table.end()){
                if(sequence_table[aux_sequence].find(byte) != sequence_table[aux_sequence].end())
                    sequence_table[aux_sequence][byte] += 1;
                else
                    sequence_table[aux_sequence][byte] = 1;
            }else{
                sequence_table[aux_sequence] = map<char,unsigned int>();
                sequence_table[aux_sequence][byte] = 1;
            }

            history_pointer = (history_pointer+1) % k;
        }
    }

    // escrever num ficheiro 
    ofstream writetable;
    writetable.clear();
    writetable.open((char*)filename.data());

    for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
    {
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            writetable << string_iter->first +' '+ char_iter->first +' '+ to_string(char_iter->second) +'\n';
        }
    }
}