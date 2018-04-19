#include <bits/stdc++.h>
#include "ll1_table.h"

using namespace std;

class NRPParser
{
	LL1_PT table;
	stack<char> parser_stack;
	char current;
	int buffer_position;

public:
	NRPParser()
	{
		cout << "---------GRAMMAR---------\n";
		table.cfg.display();
		table.fill_table();
	}

	bool isNonTerminal(char c)
	{
		for(int i=0 ; i<table.cfg.nonTerminalCount ; i++)
		{
			if(table.cfg.nonTerminals[i] == c)
				return true;
		}
		return false;
	}

	void parse(string input)
	{
		cout << "---------PARSING---------\n";
		cout << "INPUT STRING : " << input << endl << endl;
		input += "$";
		buffer_position = 0;
		parser_stack.push('$');
		parser_stack.push(table.cfg.start);
		while(1)
		{
			if(parser_stack.top() == '$' && input[buffer_position] == '$')
			{
				cout << "PARSED SUCCESSFULLY\n";
				break;
			}
			else if(parser_stack.top() == input[buffer_position])
			{
				parser_stack.pop();
				buffer_position++;
			}
			else if(isNonTerminal(parser_stack.top()))
			{
				pair<char, string> prod = table.parsing_table[make_pair(parser_stack.top(), input[buffer_position])];
				if(prod.second == ""){
					cout << "PARSING FAILED\n";
					return;
				}
				cout << prod.first << "->" << prod.second << endl;
				parser_stack.pop();
				for(int i=prod.second.length()-1 ; i>=0 ; i--)
				{
					if(prod.second[i] != '#')
						parser_stack.push(prod.second[i]);
				}
			}
		}
	}


};

int main()
{
	NRPParser parser;
	parser.parse("i+i*i");
}