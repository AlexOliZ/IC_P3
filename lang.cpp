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
    readtable = ifstream(table_file,  ios::binary);
    readfile = ifstream(lang_file, ios::binary);
    if(!(readtable.good() && readfile.good())){
        cout << "file NO GOOD" << endl;
        return 0;
    }
    map<string,map<char,unsigned int>> sequence_table;
    //map<char,unsigned int> letters_count;
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
        //cout << (aux_sequence + " " + letter + " " + number) << endl;
        // contar o nº de vezes que cada letra aparece em todos os contextos 
        /*
        if(letters_count.find(letter) != letters_count.end())
            letters_count[letter] = num;
        else
            letters_count[letter] += num;
        */
        //std::cout << (aux_sequence + " " + letter + " " + number) << endl;     
    }

    ifstream readfile = ifstream(lang_file, ios::binary);
    map<string,map<char,unsigned int>> file_table;
    map<char,unsigned int> letters_count;
    char* letters_history = (char*) malloc(sizeof(char)*k);
    unsigned int history_pointer=k-1;
    // preencher os primeiros k-1 chars no circular_buffer
    for(i=0; i<k; i++)
        readfile.read((char*) &letters_history[i],1);
    // ler sequencias do ficheiro
    // mas usar os valores da tabela para calcular o valor da compressão
    // ler cenas do ficcheiro
    // calcular 
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
        if(byte ==0x20 || (byte >= 0x41 && byte <= 0x5A) || (byte >= 0x61 && byte <= 0x7A) || (byte >= 0xC0)){
            aux_sequence = "";
            for(i=1; i<=k; i++)
            {   
                aux_sequence += letters_history[(history_pointer+i)%k];
            }
            if(file_table.find(aux_sequence) != file_table.end()){
                if(file_table[aux_sequence].find(byte) != file_table[aux_sequence].end())
                    file_table[aux_sequence][byte] += 1;
                else
                    file_table[aux_sequence][byte] = 1;
            }else{
                file_table[aux_sequence] = map<char,unsigned int>();
                file_table[aux_sequence][byte] = 1;
            }
            
            history_pointer = (history_pointer+1) % k;
            letters_history[history_pointer] = byte;
            count_seq ++;
        }
    }
    //for(map<string,map<char,unsigned int>>::iterator string_iter = sequence_table.begin(); string_iter != sequence_table.end(); ++string_iter)
    //    for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
    //        cout << string_iter -> first << " " << char_iter -> first << " " << char_iter->second << endl;
    
    double global_entropy = 0,prob_ctx;
    unsigned int sum_table;
    for(map<string,map<char,unsigned int>>::iterator string_iter = file_table.begin(); string_iter != file_table.end(); ++string_iter)
    {
        prob_ctx = 0;
        sum_table = 0;
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            sum_table += char_iter->second;
        }
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            //cout << char_iter -> second << endl;
            global_entropy -= log2(((double)(char_iter -> second + alpha)/((double)(sum_table + 3*alpha))));
        }
    }
    
    //cout << global_entropy << endl;
    /*
    double compression_size = 0,prob_ctx,local_entropy,global_entropy=0;
    unsigned int sum_table,count_ctx;
    for(map<string,map<char,unsigned int>>::iterator string_iter = file_table.begin(); string_iter != file_table.end(); ++string_iter)
    {
        //  (N(context|letter)+alpha)/(sum(all_context|letter)+alpha*3)
        count_ctx = 0;
        sum_table = 0;
        local_entropy = 0;

        for(map<char,unsigned int>::iterator char_iter = file_table[string_iter->first].begin(); char_iter != file_table[string_iter->first].end(); ++char_iter)
        {
            count_ctx += char_iter->second;
        }
        //cout <<"str:" << string_iter -> first << endl;
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            //cout <<"ITER: " << char_iter->second << endl;
            sum_table += char_iter->second;
        }
        //cout << "sum: " << sum_table << endl;
        for(map<char,unsigned int>::iterator char_iter = sequence_table[string_iter->first].begin(); char_iter != sequence_table[string_iter->first].end(); ++char_iter)
        {
            //cout <<"val " <<char_iter->second << endl;
            prob_ctx = ((double)(char_iter -> second + alpha)/((double)(sum_table + 3*alpha)));
            local_entropy -= prob_ctx*log2(prob_ctx);
        }
        global_entropy += local_entropy * ((double)count_ctx/(double)count_seq);
        //cout << global_entropy << endl;
    }
    */
    cout << global_entropy << endl;
    cout << count_seq << endl;
    return global_entropy;
}

char* lang::find_lang(char*fname)
{
    char* language;
    unsigned int compression_size;
    unsigned int min_size=0xffffffff;

    for(int i=0 ; i<NUM_LANGS ; i++)
    {
        string lang_name(languages[i]);
        lang_file = (char*)("./"+lang_name+"/table_"+to_string(k)+".txt").data();
        compression_size = check_compression_size(fname);
        if(compression_size<min_size)
        {
            min_size = compression_size;
            language = (char*)(languages[i]);
        } 
    }
    return language;
}