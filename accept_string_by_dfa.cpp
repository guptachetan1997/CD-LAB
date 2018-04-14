#include <iostream>
#define MAX 10

using namespace std;

class DFA
{
	int transition_table[MAX][MAX];
	int start_state;
	int num_of_end_states;
	int end_states[MAX];

public:

	DFA()
	{
		transition_table[0][1] = 2;
		transition_table[0][0] = 1;
		transition_table[1][0] = 3;
		transition_table[1][1] = 2;
		transition_table[2][0] = 1;
		transition_table[2][1] = 4;
		transition_table[3][0] = 3;
		transition_table[3][1] = 4;
		transition_table[4][0] = 3;
		transition_table[4][1] = 4;
		start_state = 0;
		num_of_end_states = 2;
		end_states[0] = 3;
		end_states[1] = 4;
	}

	bool check_accept(string input)
	{
		int now=start_state;
		for(int i=0 ; i<input.length() ; i++)
		{
			now = transition_table[now][input[i] - '0'];
		}
		for(int i=0 ; i<num_of_end_states ; i++)
		{
			if(end_states[i] == now)
			{
				return true;
			}
		}
		return false;
	}
};

int main()
{
	DFA dfa;
	string input;
	cin >> input;
	if(dfa.check_accept(input))
		cout << "Accepted\n";
	else
		cout << "Not Accepted\n";
}