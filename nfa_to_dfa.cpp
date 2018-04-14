#include <bits/stdc++.h>
#define MAX 100
#define BITSET_SIZE 4

using namespace std;

class NFA_state
{
	int max_states;
	int max_symbols;

public:
	int transition_table[MAX][MAX];
	bool is_start;
	bool is_finish;

	void set(int MAX_states, int MAX_symbols)
	{
		max_states = MAX_states;
		max_symbols = MAX_symbols;
		for (int i = 0; i < max_states; ++i)
		{
			for (int j = 0; j < max_symbols; ++j)
			{
				transition_table[i][j] = -1;
			}
		}
	}

	void set_as_finish()
	{
		is_finish = true;
	}

	void set_as_start()
	{
		is_start = true;
	}

	void print_trns()
	{
		for (int i = 0; i < max_states; ++i)
		{
			for (int j = 0; j < max_symbols; ++j)
			{
				cout << transition_table[i][j] << " ";
			}
			cout << endl;
		}	
	}

	bitset<BITSET_SIZE> find(int symbol)
	{

		std::bitset<BITSET_SIZE> goes_to;
		for (int j = 0; j < max_states; ++j)
		{
			if(transition_table[j][symbol] == 1)
				goes_to.set(j);
		}
		return goes_to;
	}
};

struct dfa_move
{
	bitset<BITSET_SIZE> from;
	bitset<BITSET_SIZE> to;
	int symbol;
};

class DFA_state
{
public:
	int transition_table[MAX];
	int max_symbols;
	bitset<BITSET_SIZE> name;
	bool is_start;
	bool is_finish;

	void init(int MAX_symbols, int index)
	{
		is_start = false;
		is_finish = false;
		max_symbols = MAX_symbols;
		for(int i=0 ; i<max_symbols ; i++)
		{
			transition_table[i] = 0;
		}
		bitset<BITSET_SIZE> a(index);
		name = a;
	}

	void set_as_start()
	{
		is_start = true;
	}

	void set_as_finish()
	{
		is_finish = true;
	}

	void set(dfa_move move)
	{
		name = move.from;
		transition_table[move.symbol] = move.to.to_ulong();
	}

	void print()
	{
		if(is_start)
			cout << "(S)";
		if(is_finish)
			cout << "(F)";
		if (!is_finish && !is_start)
			cout << "   ";
		cout << setw(10);
		cout << name.to_ulong() << " ";
		for(int i=0 ; i<max_symbols ; i++)
		{
			cout << setw(10);
			cout << transition_table[i] << " ";
		}
		cout << endl;
	}

};

void convert(int max_states, int max_symbols, NFA_state NFA[])
{
	DFA_state DFA[BITSET_SIZE*BITSET_SIZE];
	int k=1;
	bitset<BITSET_SIZE> start;
	start.set(0);
	for(int jj=0 ; jj<BITSET_SIZE*BITSET_SIZE ; jj++)
		DFA[jj].init(max_symbols, jj);

	queue<int> q;
	map<int, int> visited;
	// 0 -> NOT DISCOVERED
	// 1 -> IN QUEUE
	// 2 -> EXHAUSTED
	visited[0] = 2;
	for (int i = 0; i < max_symbols; ++i)
	{
		dfa_move move;
		move.from = start;
		move.to = NFA[0].find(i);
		move.symbol = i;
		DFA[0].set(move);
		q.push(move.to.to_ulong());
		visited[move.to.to_ulong()] = 1;
	}
	DFA[0].set_as_start();
	int index;
	while(!q.empty())
	{
		index = q.front();
		visited[index] = 2;
		bitset<BITSET_SIZE> index_to_bitset(index);
		for(int j=0 ; j<max_symbols ; j++)
		{
			bitset<BITSET_SIZE> now;
			bool flag_finish = false;
			for(int i=0 ; i<BITSET_SIZE ; i++)
			{
				if(index_to_bitset[i] == 1)
				{
					now |= NFA[i].find(j);
					if(NFA[i].is_finish)
						flag_finish = true;
				}
			}
			if(visited[now.to_ulong()] == 0){
				visited[now.to_ulong()] = 1;
				q.push(now.to_ulong());
			}
			dfa_move move;
			move.from = index_to_bitset;
			move.to = now;
			move.symbol = j;
			DFA[k].set(move);
			if(flag_finish)
				DFA[k].set_as_finish();
		}
		k++;
		q.pop();
	}
	cout << "Equivalent DFA\n";
	cout << "Max States : " << k << endl;
	cout << "Max Symbols : " << max_symbols <<  endl;
	cout << "S/F";
	cout << setw(10);
	cout << "$";
	for(int jj=0 ; jj<max_symbols ; jj++)
	{
		cout << setw(10);
		cout << jj << " ";
	}
	cout << endl;
	for(int z=0 ; z<k ; z++)
		DFA[z].print();

}



int main()
{
	freopen("input.txt", "r", stdin);
	int max_states, max_symbols;
	// cout << "MAX STATES : ";
	cin >> max_states;
	// cout << "MAX SYMBOLS : ";
	cin >> max_symbols;
	NFA_state NFA[max_states];
	for(int i=0 ; i<max_states ; i++)
	{
		NFA[i].set(max_states, max_symbols);
	}
	int entries;
	cin >> entries;
	int q1,q2, symb;
	for (int i = 0; i < entries; ++i)
	{
		cin >> q1 >> q2 >> symb;
		NFA[q1].transition_table[q2][symb] = 1;
	}
	int no_of_finish_states, temp;
	cin >> no_of_finish_states;
	for(int i=0 ; i<no_of_finish_states ; i++)
	{
		cin >> temp;
		NFA[temp].set_as_finish();
	}
	convert(max_states, max_symbols, NFA);
}