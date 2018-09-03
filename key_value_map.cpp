#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

long long unChar2unInt(unsigned char * pBuf){
    unsigned long long value = 0;
    value = (short)pBuf[0]*256*256*256*256;
    value += (short)pBuf[1]*256*256*256;
    value += (short)pBuf[2]*256*256;
    value += (short)pBuf[3]*256;
    value += (short)pBuf[4];
    return value;
    //for (unsigned int i = 0; i < 5; i++){
    //   value = 1 | ((unsigned long long)buffer[i] << (8*i));
}

void Long2unchar(unsigned char* pBuf, long long value)
{
    pBuf[0] = (unsigned char)(value>>32);
    pBuf[1] = (unsigned char)(value>>24);
    pBuf[2] = (unsigned char)(value>>16);
    pBuf[3] = (unsigned char)(value>>8);
    pBuf[4] = (unsigned char)(value);
}
    
void add_key_array(unsigned char* m_data_key, unsigned char* loc_temp, unsigned int line_idx)
{
    for (unsigned int i = 0; i < 5; i++)
    {
        m_data_key[line_idx*5+i] = loc_temp[i];
    }
}

void add_value_array(unsigned char* m_data_value, unsigned char* data_val, long long total_loc, unsigned value_len)
{
    for (unsigned int i = 0; i < value_len; i++)
    {
        m_data_value[total_loc + i] = data_val[i];
    }
}

void put_data(unsigned char* m_data_value, unsigned char* m_data_key, unsigned int value_len, unsigned data_val, unsigned key){
 
    
int main()
{
    //read test.dat
    ifstream infile("/data/key_value_sys/test.dat", ios::binary);
    
    string temp;
    if(!infile.is_open())
    {
        cerr<<"can not open the file\n"<<endl;
        return -1;
    }
   
    //apply for data value memory
    long long nLen = 90 * 1024 * 1024 * 1024LL;
    char* m_data_value;
    m_data_value = (char*)malloc(nLen*sizeof(char));
    cout<<"applying for memory successes!"<<endl;
    
    //apply for key value memory
    long long kLen = 1024LL * 1024 * 1024 * 4 * 5;
    char* m_data_key;
    m_data_key = (char*)malloc(kLen*sizeof(char));

    //read dat file  
    long long key_pre = 0LL;
    long long total_loc = 0LL;
    unsigned char* loc_temp;
    long long value_temp;
    unsigned int line_idx = 0;

    while(!infile.eof())
    {
        unsigned int data_key;
        unsigned int value_len;
        infile.read((char*)&data_key, sizeof(unsigned int));
        infile.read((char*)&value_len, sizeof(unsigned int));
        char data_val[value_len];
        infile.read(data_val, value_len*sizeof(char));
        if (value_len <1){
            cout<<"key: "<<data_key<<" data size: "<<value_len<<" data: "<<endl;
        }

        //for the inconsistent data key
        for (int idx = key_pre; idx < data_key; idx++)
        {
            loc_temp = int2char(0xFFFFFFFFFF);
            add_key_array(m_data_key, loc_temp, line_idx);
        }
        
       
        loc_temp = int2char(value_len);
        add_key_array(m_data_key, loc_temp, line_idx);
        add_value_array(m_data_value, data_val, total_loc, value_len);
      
        total_loc += value_len; 
        line_idx++;
        key_pre = data_key;
    }

    infile.close();

    return 0;
}
        
