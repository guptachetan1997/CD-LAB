#include <bits/stdc++.h>

using namespace std;

class Parser{
	string buffer;
	int error_flag;
	int pointer;
	char l;
public:
	Parser()
	{
		cin >> buffer;
		buffer += "$";
		pointer = 0;
		l = buffer[pointer];
		error_flag = 0;
	}

	void advance(char c)
	{
		if(l == c)
			l = buffer[++pointer];
		else
			error_flag = 1;
	}

	void C()
	{
		cout << "C->";
		if(l == '1')
		{
			advance('1');
		}
		else
		{
			error_flag = 1;
		}
	}

	void B()
	{
		cout << "B->";
		if(l == '0')
		{
			advance('0');
			S();
		}
		else
		{
			error_flag = 1;
		}
	}

	void A()
	{
		cout << "A->";
		if(l == '1')
		{
			advance('1');
			A();
			C();
		}
		else if(l == '0')
		{
			advance('0');
			C();
		}
		else
		{
			error_flag = 1;
		}
	}

	void S()
	{
		cout << "S->";
		if(l == '1')
		{
			advance('1');
			A();
			B();
		}
		else
		{
			return;
		}
	}

	int parser_main()
	{
		S();
		if(error_flag)
			cout << "\nRejected\n";
		else if(l == '$')
			cout << "\nAccepted\n";
		else
			cout << "\nRejected\n";
	}
};

int main()
{
	Parser p;
	p.parser_main();
}