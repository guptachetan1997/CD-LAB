#include <bits/stdc++.h>
#define MAX 10
#define NULL_SYMBOL "#"

using namespace std;

class ProductionRule
{
public:
	char origin;
	vector<string> expansion;

	bool set(char LHS, string RHS)
	{
		bool nullable;
		string temp = "";
		origin = LHS;
		for(int i=0 ; i<RHS.length() ; i++)
		{
			if(RHS[i] == '|')
			{
				expansion.push_back(temp);
				if(temp == "#")
					nullable = true;
				temp = "";
			}
			else
			{
				temp.push_back(RHS[i]);
			}
		}
		expansion.push_back(temp);
		temp = "";
		return nullable;
	}
	void display()
	{
		cout << origin << " -> ";
		for(int i=0 ; i<expansion.size() ; i++)
			cout << expansion[i] << "|";
		cout << endl;
	}
};

class Grammar
{
	ProductionRule productions[MAX];
	char terminals[MAX], nonTerminals[MAX], start;
	int nonTerminalCount, terminalCount, productionsCount;
	map<char, vector<char> > first;
	map<char, vector<char> > follow;
	map<char, bool> nullable;

public:

	void setFromFile()
	{
		freopen("grammar3.txt", "r", stdin);
		cin >> nonTerminalCount;
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			cin >> nonTerminals[i];
		}
		cin >> start;
		cin >> terminalCount;
		for(int i=0 ; i<terminalCount ; i++)
		{
			cin >> terminals[i];
		}
		cin >> productionsCount;
		for(int i=0 ; i<productionsCount ; i++)
		{
			char LHS;
			string RHS;
			cin >> LHS >> RHS;
			if(productions[i].set(LHS, RHS))
				nullable[LHS] = true;
		}
	}

	void display()
	{
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			cout << nonTerminals[i] << " ";
		}
		cout << "\n";
		for(int i=0 ; i<terminalCount ; i++)
		{
			cout << terminals[i] << " ";
		}
		cout << "\n";
		for(int i=0 ; i<productionsCount ; i++)
		{
			productions[i].display();
		}
	}

	bool isTerminal(char c)
	{
		for(int i=0 ; i<terminalCount ; i++)
			if(terminals[i] == c)
				return true;
		return false;
	}

	bool isNULL(char c)
	{
		return (c == '#');
	}

	bool inFirst(char c, char key)
	{
		for(int i=0 ; i<first[c].size() ; i++)
			if(first[c][i] == key)
				return true;
		return false;
	}

	bool inFollow(char c, char key)
	{
		for(int i=0 ; i<follow[c].size() ; i++)
			if(follow[c][i] == key)
				return true;
		return false;
	}

	void DFS_first(char NT, char papa)
	{
		if(isTerminal(NT) || isNULL(NT)){
			first[papa].push_back(NT);
			return; 
		}
		for(int i=0 ; i<productionsCount ; i++)
		{
			if(productions[i].origin == NT)
			{
				for(int j=0 ; j<productions[i].expansion.size() ; j++)
				{
					string prod = productions[i].expansion[j];
					for(int k=0 ; k<prod.length() ; k++)
					{
						DFS_first(prod[k], NT);
						for(int l=0 ; l<first[prod[k]].size() ; l++){
							if(!inFirst(NT, first[prod[k]][l]))
								first[NT].push_back(first[prod[k]][l]);
						}
						if(!inFirst(prod[k], '#'))
						{
							break;
						}
					}
				}
			}
		}
	}

	void calculate_first()
	{
		for(int i=0 ; i<terminalCount ; i++)
			first[terminals[i]].push_back(terminals[i]);
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			char NT = nonTerminals[i];
			if(first[NT].empty())
			{
				DFS_first(NT, NT);
			}
		}
	}

	void DFS_follow(char NT)
	{
		for(int j=0 ; j<productionsCount ; j++)
			{
				for(int k=0 ; k<productions[j].expansion.size() ; k++)
				{
					string prod = productions[j].expansion[k];
					bool first_occ = false, null_flag;
					int pos;
					for(pos = 0 ; pos<prod.length() && prod[pos]!=NT ; pos++);
					if(pos < prod.length()-1)
					{
						while(true)
						{
							null_flag = false;
							for(int l=0 ; l<first[prod[pos+1]].size() ; l++)
							{
								if(first[prod[pos+1]][l] != '#'){
									if(!inFollow(NT, first[prod[pos+1]][l])){
										follow[NT].push_back(first[prod[pos+1]][l]);
									}
								}
								else
									null_flag=true;
							}
							if(null_flag && pos<prod.length()-1)
								pos++;
							else
								break;
						}
					}
					if(pos == prod.length()-1 && NT != productions[j].origin)
					{
						DFS_follow(productions[j].origin);
						for(int l=0 ; l<follow[productions[j].origin].size() ; l++)
						{
							if(!inFollow(NT, follow[productions[j].origin][l]))
								follow[NT].push_back(follow[productions[j].origin][l]);
						}
					}
				}
				
			}
	}

	void calculate_follow()
	{
		follow[start].push_back('$');
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			char NT = nonTerminals[i];
			// if(follow[NT].empty())
			DFS_follow(NT);
		}
	}

	void print_first_follow()
	{
		cout << "--------FIRST--------\n";
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			cout << nonTerminals[i] << " : { ";
			for(int j=0 ; j<first[nonTerminals[i]].size() ; j++)
				cout << first[nonTerminals[i]][j] << " ,";
			cout << " }\n";
		}
		cout << "-------FOLLOW-------\n";
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			cout << nonTerminals[i] << " : { ";
			for(int j=0 ; j<follow[nonTerminals[i]].size() ; j++)
				cout << follow[nonTerminals[i]][j] << " ,";
			cout << " }\n";
		}
	}
};

int main()
{
	Grammar cfg;
	cfg.setFromFile();
	cfg.display();
	cfg.calculate_first();
	cfg.calculate_follow();
	cfg.print_first_follow();

}