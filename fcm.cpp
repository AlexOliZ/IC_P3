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
    ifstream readtable = ifstream((char*)filename.data(), ios::binary);
    while(1)
    {
        if(readtable.eof()){
            break;
        }
        
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
        cout << (aux_sequence + " " + letter + " " + number) << endl;
        //readtable.read(&byte,1);
    }


    string path = "./"+ language + "/" +fname;
    ifstream readfile = ifstream((char*) path.data(), ios::binary);
    
    
    char* letters_history = (char*) malloc(sizeof(char)*k);
    unsigned int history_pointer=k-1;
    
    // preencher os primeiros k-1 chars no circular_buffer
    // 
    for(i=0; i<k; i++)
        readfile.read((char*) &letters_history[i],1);
    
    //while(readfile.peek() != EOF )
    while(1)
    {
        if(readfile.eof()){
            break;
        }
        readfile.read((char*) &byte,1);
        if(byte != '\n' && byte != '\t'){
            // ter cuidado que nas primeiras k letras não vai ter k letras na 
            // sequence_table para adicionar ao histograma  
            aux_sequence = "";
            for(i=0; i<k; i++)
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
        }
    }

    // calcular a prob para cada char seguido de uma sequencia
    // H_sequence = -sum(p_letter * log(p_letter))
    // M_sequence = sum(H_sequence*P(sequence)), c -> sequence
    // nº de sequencias -> sequence_table.size();
    // primeiro calcular o nº total de sequencias ... para fazer as probs
    // depois calcular a  entropia
    readtable.close();
    readfile.close();

    unsigned int count_seq=0;
    for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
            count_seq += char_iter->second;
    // escrever num ficheiro e calcular a entropia
    cout << "count_seq: " << count_seq << endl;
    unsigned int sum_sequence;        // nº de ocorrencias de uma sequencia ... somar para todas as letras
    double entropy=0,local_entropy=0,pi;
    ofstream writetable;
    writetable.clear();
    writetable.open((char*)filename.data());
    //map<string,unsigned int>> entropy_table; 
    cout << "___________________________" << endl;
    for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
    {
        sum_sequence = 0;
        local_entropy=0;
        // calcular o total de combinações com a seq
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            //cout << char_iter->first << endl;
            //cout << char_iter->second << endl;
            sum_sequence += char_iter->second;
            writetable << string_iter->first+ " " +char_iter->first+" " +to_string(char_iter->second) +'\n';
        }
        cout << "sum_sequence: " << sum_sequence << endl;
        // calcular a entropia para uma sequencia
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            pi = ((double)char_iter->second)/((double)sum_sequence);
            cout << "sum: " << sum_sequence << endl;
            cout << "char: " << char_iter->second << endl;
            cout << "pi: " << (double)pi << endl;
            cout << ((double)char_iter->second)/((double)sum_sequence) << endl;
            local_entropy -= (double)pi*log(pi);
        }
        //cout << "b";
        cout << "local_entropy: " << local_entropy << endl;
        entropy += local_entropy*((double)sum_sequence/(double)count_seq);
        //cout << "c" << endl;
    }
    cout << "entropy: " << entropy << endl;
    writetable.close();
}