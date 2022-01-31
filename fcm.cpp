#include "fcm.h"

using namespace std;

void fcm::read_table(char* fname)
{
    // antes de começar a ler o novo histograma
    // dar load ao ficheiro se tiver a tabela escrita
    int i;    
    char byte,letter;
    string number;
    string aux_sequence;
    map<string,map<char,unsigned int>> sequence_table;
    // set<char> letters_list;
    ifstream readtable = ifstream((char*)filename.data(), ios::binary);
    while(1)
    {
        if(readtable.eof()){
             break;
        }
        //cout << readtable.good() << endl;
        aux_sequence = "";
        number = "";
        if(readtable.peek() == -1){
            cout << "no more info in file" << endl;
            break;
        }
        for(i=0; i<k; i++){
            readtable.read(&byte,1);
            aux_sequence += byte;
        }
        readtable.read(&byte,1);
        readtable.read(&letter,1);
        readtable.read(&byte,1);
        while(byte  != '\n'){
            readtable.read(&byte,1);
            number += byte;
            if(readtable.eof())
                break;
        
        }
        sequence_table[aux_sequence][letter] = atoi(number.data());
        //cout << (aux_sequence + " " + letter + " " + number) << endl;
        //readtable.read(&byte,1);
    }
    
    string path = "./"+ language + "/" +fname;
    ifstream readfile = ifstream((char*) path.data(), ios::binary);
    
    
    char* letters_history = (char*) malloc(sizeof(char)*k);
    unsigned int history_pointer=k-1;
    // preencher os primeiros k-1 chars no circular_buffer
    for(i=0; i<k; i++)
        readfile.read((char*) &letters_history[i],1);
    unsigned int count_seq=1;
    while(1)
    {
        if(readfile.eof()){
            break;
        }
        readfile.read((char*) &byte,1);
        // só lê letras entre A-Z e a-z ou space
        // space -> 0x20            A-Z                                 a-z                     letras com acentos
        if(byte == '\n' || byte == '\t' || byte == '\r')
            byte = 0x20;
        if(byte==0x27 || byte==0x2D || byte ==0x20 || (byte >= 0x41 && byte <= 0x5A) || (byte >= 0x61 && byte <= 0x7A) || (byte >= 0xC0)){
            aux_sequence = "";
            for(i=1; i<=k; i++)
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
            letters_history[history_pointer] = byte;
            count_seq ++;
        }
    }

    readtable.close();
    readfile.close();

    cout << "count_seq: " << count_seq << endl;
    
    ofstream writetable;
    writetable.clear();
    writetable.open((char*)filename.data());
    
    cout << "___________________________" << endl;
    for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
    {
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            writetable << string_iter->first+ " " +char_iter->first+" " +to_string(char_iter->second) +'\n';
        }
    }
    writetable.close();
}