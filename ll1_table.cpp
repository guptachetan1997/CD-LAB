#include <bits/stdc++.h>
#include "first_follow.h"
#define MAX 10

using namespace std;

class LL1_PT
{
	Grammar cfg;
	map< pair<char, char>, pair<char,string> > parsing_table;
	map< pair<char, char>, int> error;

public:
	LL1_PT()
	{
		cfg.setFromFile();
		cfg.calculate_first();
		cfg.calculate_follow();
		cfg.display();
		cfg.print_first_follow();
	}

	void fill_table()
	{
		for(int i=0 ; i<cfg.productionsCount ; i++)
		{
			for(int j=0 ; j<cfg.productions[i].expansion.size() ; j++)
			{
				string prod = cfg.productions[i].expansion[j];
				char origin = cfg.productions[i].origin;
				for(int k=0 ; k<cfg.first[prod[0]].size() ; k++)
				{
					if(cfg.isTerminal(cfg.first[prod[0]][k]))
					{
						parsing_table[make_pair(origin, cfg.first[prod[0]][k])] = make_pair(origin, prod);
						error[make_pair(origin, cfg.first[prod[0]][k])] = 1;
					}
					else if(cfg.isNULL(cfg.first[prod[0]][k]))
					{
						for(int l=0 ; l<cfg.follow[origin].size() ; l++)
						{
							if(cfg.follow[origin][l] != '#'){
								parsing_table[make_pair(origin, cfg.follow[origin][l])] = make_pair(origin, prod);
								error[make_pair(origin, cfg.follow[origin][l])] = 1;
							}
						}
					}
				}
			}
		}
	}
	void display_table()
	{
		cout << "\n-----------PARSING TABLE-----------\n";
		cout << " ";
		for(int j=0 ; j<cfg.terminalCount-1 ; j++)
			cout << std::setw(11) << cfg.terminals[j];
		cout  << std::setw(11) << "$" << endl;
		for(int i=0 ; i<cfg.nonTerminalCount ; i++)
		{
			cout << cfg.nonTerminals[i];
			for(int j=0 ; j<cfg.terminalCount ; j++)
			{
				{
					if(cfg.terminals[j] == '#' && error[make_pair(cfg.nonTerminals[i],'$')])
						cout << std::setw(10) << parsing_table[make_pair(cfg.nonTerminals[i],'$')].first << "->" << parsing_table[make_pair(cfg.nonTerminals[i],'$')].second;
					else if(error[make_pair(cfg.nonTerminals[i],cfg.terminals[j])])
						cout << std::setw(10) << parsing_table[make_pair(cfg.nonTerminals[i],cfg.terminals[j])].first << "->" << parsing_table[make_pair(cfg.nonTerminals[i],cfg.terminals[j])].second;
					else
						cout << setw(10) << "-";
				}
			}
			cout << endl;
		}
	}
};

int main()
{
	LL1_PT table;
	table.fill_table();
	table.display_table();
}