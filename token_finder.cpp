#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

std::map<string, int> SYMBOL_TABLE;
const int KW_COUNT = 24;

void init_map()
{
	SYMBOL_TABLE["if"] = 1;
	SYMBOL_TABLE["else"] = 2;
	SYMBOL_TABLE["while"] = 3;
	SYMBOL_TABLE["do"] = 4;
	SYMBOL_TABLE["break"] = 5;
	SYMBOL_TABLE["continue"] = 6;
	SYMBOL_TABLE["int"] = 7;
	SYMBOL_TABLE["double"] = 8;
	SYMBOL_TABLE["float"] = 9;
	SYMBOL_TABLE["return"] = 10;
	SYMBOL_TABLE["char"] = 11;
	SYMBOL_TABLE["case"] = 12;
	SYMBOL_TABLE["char"] = 13;
	SYMBOL_TABLE["sizeof"] = 14;
	SYMBOL_TABLE["long"] = 15;
	SYMBOL_TABLE["short"] = 16;
	SYMBOL_TABLE["typedef"] = 17;
	SYMBOL_TABLE["switch"] = 18;
	SYMBOL_TABLE["unsigned"] = 19;
	SYMBOL_TABLE["void"] = 20;
	SYMBOL_TABLE["static"] = 21;
	SYMBOL_TABLE["struct"] = 22;
	SYMBOL_TABLE["goto"] = 23;
	SYMBOL_TABLE["main"] = 24;
}

bool isOperator(char cur)
{
	switch(cur)
	{
		case '+':
		case '-':
		case '/':
		case '*':
		case '%':
		case '=':
			return true;
	}
	return false;
}

int isKeywordOrIdentifier(char buffer[])
{
	int lookup = SYMBOL_TABLE[buffer];
	if(lookup == 0)
		return 0;
	if(lookup <= KW_COUNT)
		return 1;
	if(lookup > KW_COUNT)
		return 2;
}

bool isDelimiter(char cur)
{
	string DELIMITERS = ",; \n$";
	for(int i=0 ; DELIMITERS[i]!='\0' ; i++)
	{
		if(cur == DELIMITERS[i])
			return true;
	}
	return false;
}

int main()
{
	init_map();
	char cur, buffer[20];
	int buffer_end=0, IDENTIFIER_COUNT=25, line_number=0;
	std::vector<pair<int, string> > ERRORS;
	ifstream codefile("sample.cpp");
	if( codefile.is_open() )
	{
		while( !codefile.eof() )
		{
			string line;
			getline(codefile, line);
			line_number++;
			line += "$";
			for(int i=0 ; line[i]!='\0' ; i++){
				cur = line[i];
				if(isOperator(cur))
				{
					cout << "<" << cur << ">";
				}
				else if(isalnum(cur))
				{
					buffer[buffer_end++] = cur;
				}
				else if(isDelimiter(cur) && buffer_end!=0)
				{
					buffer[buffer_end] = '\0';
					buffer_end = 0;
					int kw_id_check = isKeywordOrIdentifier(buffer);
					if(kw_id_check == 1)
						cout << "<KW," << SYMBOL_TABLE[buffer] << ">";
					else if(isdigit(buffer[0])){
						ERRORS.push_back(make_pair(line_number, buffer));
					}
					else
					{
						if(kw_id_check != 2)
							SYMBOL_TABLE[buffer] = IDENTIFIER_COUNT++;
						cout << "<ID," << SYMBOL_TABLE[buffer] << ">";
					}
				}
			}
			cout << endl;
		}
		cout << "ERRORS : \n";
		for(int i=0 ; i<ERRORS.size() ; i++)
		{
			cout << "LINE " << ERRORS[i].first << " -> " << ERRORS[i].second << " is INVALID.\n";
		}
		codefile.close();
	}
	else
	{
		cout << "Unable to open\n";
	}
}