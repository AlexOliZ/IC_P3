#include "lang.h"


using namespace std;
bool lang::set_file(char* fname)
{
    lang_file = fname;
    readtable = ifstream(fname, ios::binary);
    return readtable.good();
}

unsigned int lang::check_compression_size(char* fname)
{
    char byte,letter;
    string aux_sequence;
    string number;
    int i,num;
    unsigned int count_seq=0;
    readtable = ifstream(table_file,  ios::binary);
    readfile = ifstream(lang_file, ios::binary);
    if(!(readtable.good() && readfile.good())){
        cout << "file NO GOOD" << endl;
        return 0;
    }
    map<string,map<char,unsigned int>> sequence_table;
    map<char,unsigned int> letters_count;
    // ler a tabela do ficheiro
    while(1)
    {
        if(readtable.eof()){
             break;
        }
        
        aux_sequence = "";
        number = "";
        if(readtable.peek() == -1){
            std::cout << "no more info in file" << endl;
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
        num = atoi(number.data());
        sequence_table[aux_sequence][letter] = num;
        // contar o nº de vezes que cada letra aparece em todos os contextos 
        if(letters_count.find(letter) != letters_count.end())
            letters_count[letter] = num;
        else
            letters_count[letter] += num;

        count_seq += num;
        //std::cout << (aux_sequence + " " + letter + " " + number) << endl;     
    }
    
    
    for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
            count_seq += char_iter->second;
    
    double compression_size = 0;
    for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
    {
        //  (N(context|letter)+alpha)/(sum(all_context|letter)+alpha*3)
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            //if(letters_count[char_iter->first] == 0)
            //    cout << "ERROR" << endl;
            compression_size += (char_iter->second+alpha)/(letters_count[char_iter->first]!=0?letters_count[char_iter->first]:1);
        }

    }
    return compression_size;
}