#include <bits/stdc++.h>

#define MAX 10

using namespace std;

class ProductionRule
{
	char from;
	string to;

public:

	void set(char LHS, string RHS)
	{
		from = LHS;
		to = RHS;
	}
	void display()
	{
		cout << from << " -> " << to << endl;
	}
	bool check(char f)
	{
		if(from == f)
			return true;
		else
			return false;
	}
	string TO()
	{
		return to;
	}
	string TO_cut()
	{
		return to.substr(1, to.length()-1);
	}
	bool check_left()
	{
		if(to[0] == from)
			return true;
		else
			return false;
	}
};

class Grammar
{
	ProductionRule productions[MAX];
	char nonTerminals[MAX], terminals[MAX];
	int nonTerminalCount, terminalCount, productionsCount;

public:

	void setFromFile()
	{
		freopen("grammar2.txt", "r", stdin);
		cin >> nonTerminalCount;
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			cin >> nonTerminals[i];
		}
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
			productions[i].set(LHS, RHS);
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

	void leftRecursion()
	{
		char conts = 'Z';
		map<char, char> baap;
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			for(int j=0 ; j<productionsCount ; j++)
			{
				if(productions[j].check(nonTerminals[i]))
				{
					if(productions[j].check_left())
					{
						baap[nonTerminals[i]] = conts--;
						cout << baap[nonTerminals[i]] << " -> " << productions[j].TO_cut() << endl;
					}
					else
					{
						cout << nonTerminals[i] << " -> " << productions[j].TO() << baap[nonTerminals[i]] << endl;
					}
				}
			}
		}
	}

};

int main()
{
	Grammar cfg;
	cfg.setFromFile();
	cfg.leftRecursion();
}