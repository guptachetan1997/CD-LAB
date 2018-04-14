#include <bits/stdc++.h>
#define MAX 10

using namespace std;

struct trieNode
{
	map<char, pair<int, trieNode*> > children;
	bool isComplete;
	string tillNow;
};

trieNode *getNewNode()
{
	trieNode *p = new trieNode;
	p->isComplete = false;
	p->tillNow = "";
	return p;
}

class Trie
{
	trieNode *root;

public:

	Trie()
	{
		root = getNewNode();
	}

	void insert(string word)
	{
		trieNode *p = root;
		for(auto i: word)
		{
			if(p->children[i].second)
			{
				p->children[i].first++;
				p = p->children[i].second;
			}
			else
			{
				trieNode *newNode = getNewNode();
				newNode->tillNow = p->tillNow + i;
				p->children[i].second = newNode;
				p->children[i].first++;
				p = newNode;
			}
		}
		p->isComplete = true;
	}

	char traverse(char start, char CONTS)
	{
		map < trieNode*, char > cont;
		char conts = CONTS;
		trieNode *p = root, *cur;
		queue <trieNode* > q;
		q.push(p);
		cont[root] = start;
		while(!q.empty())
		{
			cur = q.front();
			q.pop();
			for(auto i : cur->children)
			{
				if(i.second.first > 1)
				{
					cout << cont[cur] << " -> " << i.first << (--conts) << endl;
					cont[i.second.second] = conts;
				}
				else
					cout << cont[cur] << " -> " << i.first << endl;
				q.push(i.second.second);
			}
		}
		return conts;
	}

};

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
};

class Grammar
{
	ProductionRule productions[MAX];
	char nonTerminals[MAX], terminals[MAX];
	int nonTerminalCount, terminalCount, productionsCount;

public:

	void setFromFile()
	{
		freopen("grammar.txt", "r", stdin);
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

	void leftFactor()
	{
		char CONTS = 'Z';
		for(int i=0 ; i<nonTerminalCount ; i++)
		{
			Trie t;
			for(int j=0 ; j<productionsCount ; j++)
			{
				if(productions[j].check(nonTerminals[i]))
				{
					t.insert(productions[j].TO());
				}
			}
			CONTS = t.traverse(nonTerminals[i], CONTS);
		}
	}

};

int main()
{
	Grammar cfg;
	cfg.setFromFile();
	cfg.leftFactor();
}