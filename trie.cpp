#include<bits/stdc++.h>

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
				// (p->tillNow) += i;
			}
		}
		p->isComplete = true;
	}

	void traverse()
	{
		map < trieNode*, char > cont;
		char conts = 'Z';
		trieNode *p = root, *cur;
		queue <trieNode* > q;
		q.push(p);
		cont[root] = conts;
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
	}

};

int main()
{
	Trie t;
	t.insert("abf");
	t.insert("abg");
	t.insert("ad");
	t.insert("e");
	// t.insert("ef");
	// t.insert("eg");
	t.traverse();

}