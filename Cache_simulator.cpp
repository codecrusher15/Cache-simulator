//IMT2020015 Pushkar Pawar
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
void cache_operation(ll cache[],ll *hits,char binary[],ll tag_offset,ll);
void sd_hex_to_bin(char a,char temp[]) //gives binary output for single digit hex input
{
	switch (a)
	{
		case '0':
		temp[3] = '0'; temp[2] = '0'; temp[1] = '0'; temp[0] = '0';
		break;
		case '1':
		temp[3] = '0'; temp[2] = '0'; temp[1] = '0'; temp[0] = '1';
		break;
		case '2':
		temp[3] = '0'; temp[2] = '0'; temp[1] = '1' ; temp[0] = '0';
		break;
		case '3':
		temp[3] = '0'; temp[2] = '0'; temp[1] = '1'; temp[0] = '1';
		break;
		case '4':
		temp[3] = '0'; temp[2] = '1'; temp[1] = '0'; temp[0] = '0';
		break;
		case '5':
		temp[3] = '0'; temp[2] = '1'; temp[1] = '0'; temp[0] = '1';
		break;
		case '6':
		temp[3] = '0'; temp[2] = '1'; temp[1] = '1'; temp[0] = '0';
		break;
		case '7':
		temp[3] = '0'; temp[2] = '1'; temp[1] = '1'; temp[0] = '1';
		break;
		case '8':
		temp[3] = '1'; temp[2] = '0'; temp[1] = '0'; temp[0] = '0';
		break;
		case '9':
		temp[3] = '1'; temp[2] = '0'; temp[1] = '0'; temp[0] = '1';
		break;
		case 'A':
		case 'a':
		temp[3] = '1'; temp[2] = '0'; temp[1] = '1'; temp[0] = '0';
		break;
		case 'B':
		case 'b':
		temp[3] = '1'; temp[2] = '0'; temp[1] = '1'; temp[0] = '1';
		break;
		case 'C':
		case 'c':
		temp[3] = '1'; temp[2] = '1'; temp[1] = '0'; temp[0] = '0';
		break;
		case 'D':
		case 'd':
		temp[3] = '1'; temp[2] = '1'; temp[1] = '0'; temp[0] = '1';
		break;
		case 'E':
		case 'e':
		temp[3] = '1'; temp[2] = '1'; temp[1] = '1'; temp[0] = '0';
		break;
		case 'F':
		case 'f':
		temp[3] = '1'; temp[2] = '1'; temp[1] = '1'; temp[0] = '1';
		break;
	}
}
void hex_to_binary(char addr[],char binary[]) //finds binary of hexadecimal address
{
	ll k = 0;
	char temp[4];
	for (ll i = 9; i>=2; i--)
	{
		sd_hex_to_bin(addr[i],temp);
		for (ll j = 0; j < 4; j++)
		{
			binary[k] = temp[j];
			k++;
		}
	}
	
}
int main()
{
	ll count = 0,hits = 0; //count is total entries and hits is number of hits
	ll block_size,cache_size,block_offset=0,cache_offset = 10,tag_offset;
	cout << "Enter block size: ";
	cin >> block_size;
	cout << "Enter cache size in kilo bits: ";
	cin >> cache_size;
	ll temp = block_size,my_cache[cache_size*1024];
	while(temp>1){temp=temp/2;block_offset++;} //calculates block offset;
	temp = cache_size;
	while(temp>1){temp=temp/2;cache_offset++;} //calculates cache offset
	tag_offset = 32 - block_offset - cache_offset; //calculates number of bits taken for tag
	cout << "Enter input file name: ";
	string s;
	cin >> s;
	fstream file;
	file.open(s,ios::in); //opening the test case file
	char ignore,addr[10],binary[32]; //addr stores hex address and binary stores binary address
	int ign;
	for (int i = 0; i < cache_size*1024; i++)
	{
		my_cache[i] = -1; //initialising all entries to -1 which takes care of valid bit
	}
	file >> ignore; //ignoring the unecessary data in file
	while(file.good())
	{
		count++;
		//cout << count <<" ";
		for (ll i = 0; i < 10; i++) //taking hex addr input from file
		{
			file >> addr[i];
			//cout << addr[i];
		}
		//cout << "  ";
		hex_to_binary(addr,binary); //converting hex addr to binary
		for (ll i = 31; i >= 0; i--)
		{
			//cout << binary[i];
		}
		//cout << "  ";
		cache_operation(my_cache,&hits,binary,tag_offset,block_offset); //function to peform cache operations
		//cout << endl;
		file >> ign; //ignoring the unecessary data in file
		if(file.eof()) break;
		file >> ignore; //ignoring the unecessary data in file
	}
	cout <<"hit percentage is: " << ((hits*1.0)/(count*1.0))*100<<"%"<<endl; //hit rate in percantage
	file.close();
}
void cache_operation(ll cache[],ll *hits,char binary[],ll tag_offset,ll block_offset)
{
	ll temp = 32 - tag_offset;
	ll i = 1;
	ll tag=0,addr=0;
	for(;temp<32;temp++) //calculating tag value in decimal
	{
		if(binary[temp] == '1')tag+=i;
		i=i*2;
	}
	i = 1;
	for(;block_offset<32-tag_offset;block_offset++) //calculating addr in decimal
	{
		if(binary[block_offset] == '1') addr+=i;
		i = i*2;
	}
	//cout <<" prevtag:"<<cache[addr];
	//cout << " addr:"<<addr<<" tag:"<<tag;
	if(tag == cache[addr] && cache[addr] != -1){ *hits = *hits+1;} //hit case 
	else cache[addr] = tag; //miss case
}