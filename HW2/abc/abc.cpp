#include <iostream>
#include <fstream>
#include <stack>
#include <cctype>
#include <cstring>
#include <string>
#include <algorithm> //for remove

using namespace std;

char AtSign[3][3] = { NULL };
char HashTag[3][3] = { NULL };
char Ampersand[3][3] = { NULL };


char read_and_evaluate(istream& ins);
void evaluate_stack(stack<char>& numbers, stack<char>& operations);

void open_file();
int main()
{
	open_file();

	while(1)
	{
		try
		{
			cout << read_and_evaluate(cin) << endl;
			cin.ignore(); // '\n' 무시
		}
		
		catch (int expn) // 예외에 따라 처리한다
		{
			cout << "Error!" << endl;

			while (cin.peek() != '\n') // 예외를 처리한 뒤, 입력 스트림을 '\n' 전까지 무시한다
				cin.ignore();
			cin.ignore(); // '\n' 무시
		}
	}
	return 0;
}

void open_file()
{
	ifstream fd;
	int count = 0;
	fd.open("operations.txt");

	if (fd.is_open())
	{
		while (!fd.eof())
		{
			char tmp1[256];
			char tmp[256];
			fd.getline(tmp1, 256);
			string str(tmp1);
			str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // 읽어온 라인 공백 제거
			//문자열을 char 배열로
			strcpy_s(tmp, str.c_str());
			switch (count)
			{
			case 1:
				AtSign[0][0] = tmp[0];
				AtSign[0][1] = tmp[1];
				AtSign[0][2] = tmp[2];
				break;
			case 2:
				AtSign[1][0] = tmp[0];
				AtSign[1][1] = tmp[1];
				AtSign[1][2] = tmp[2];
				break;
			case 3:
				AtSign[2][0] = tmp[0];
				AtSign[2][1] = tmp[1];
				AtSign[2][2] = tmp[2];
				break;
			case 5:
				HashTag[0][0] = tmp[0];
				HashTag[0][1] = tmp[1];
				HashTag[0][2] = tmp[2];
				break;
			case 6:
				HashTag[1][0] = tmp[0];
				HashTag[1][1] = tmp[1];
				HashTag[1][2] = tmp[2];
				break;
			case 7:
				HashTag[2][0] = tmp[0];
				HashTag[2][1] = tmp[1];
				HashTag[2][2] = tmp[2];
				break;
			case 9:
				Ampersand[0][0] = tmp[0];
				Ampersand[0][1] = tmp[1];
				Ampersand[0][2] = tmp[2];
				break;
			case 10:
				Ampersand[1][0] = tmp[0];
				Ampersand[1][1] = tmp[1];
				Ampersand[1][2] = tmp[2];
				break;
			case 11:
				Ampersand[2][0] = tmp[0];
				Ampersand[2][1] = tmp[1];
				Ampersand[2][2] = tmp[2];
				break;
			}
			count++;

		}
		fd.close();
	}
}

void deleteBlank(char[])
{
	
}

char read_and_evaluate(istream& ins)
{
	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';
	const char RIGHT_CURLY_BRACKET = '}';
	const char RIGHT_SQUARE_BRACKET = ']';

	stack<char> numbers;
	stack<char> operations;
	
	char number;
	char symbol;

	// Loop continues while istream is not "bad" (tested by ins) an next character isn't newline.
	while (ins && ins.peek() != '\n')
	{
		if (ins.peek() == 'a'|| ins.peek() == 'b' || ins.peek() == 'c' || (ins.peek() == DECIMAL))
		{
			ins >> number;
			numbers.push(number);
		}
		else if (strchr("@#&", ins.peek()) != NULL)
		{
			while (!operations.empty()) {
				if (strchr("@#", ins.peek()) != NULL && strchr("([{", operations.top()) == NULL) {
					
					evaluate_stack(numbers, operations);
				}
				else if(strchr("&", ins.peek()) != NULL && strchr("([{", operations.top()) == NULL){
					
					if (strchr("&", operations.top()) != NULL) {
						evaluate_stack(numbers, operations);
					}
					
					else break;
				}
			}
			ins >> symbol;
			operations.push(symbol);
		}
		else if (ins.peek() == RIGHT_PARENTHESIS)
		{
			ins.ignore();
			evaluate_stack(numbers, operations);
		}
		
		else
		{
			if(ins.peek() == 'E')
			{
				char tmp[3];
				char eoi[] = "EOI";
				ins >> tmp;
				if (strcmp(tmp, eoi) == 0)
					exit(0);
			}
		}
			ins.ignore();
	}
	

	return numbers.top();
}

void evaluate_stack(stack<char>& numbers, stack<char>& operations)
{
	char operand1, operand2;

	// 계산 할 실수가 없을 때 예외를 던진다
	if (numbers.empty()) throw - 2;
	operand2 = numbers.top();
	numbers.pop();

	// 계산할 실수가 없을 때 예외를 던진다
	if (numbers.empty()) throw - 2;
	operand1 = numbers.top();
	numbers.pop();

	switch (operations.top())
	{
	case '@':
		if (operand1 == 'a' && operand2 == 'a')
			numbers.push(AtSign[0][0]);
		else if (operand1 == 'a' && operand2 == 'b')
			numbers.push(AtSign[0][1]);
		else if (operand1 == 'a' && operand2 == 'c')
			numbers.push(AtSign[0][2]);
		else if (operand1 == 'b' && operand2 == 'a')
			numbers.push(AtSign[1][0]);
		else if (operand1 == 'b' && operand2 == 'b')
			numbers.push(AtSign[1][1]);
		else if (operand1 == 'b' && operand2 == 'c')
			numbers.push(AtSign[1][2]);
		else if (operand1 == 'c' && operand2 == 'a')
			numbers.push(AtSign[2][0]);
		else if (operand1 == 'c' && operand2 == 'b')
			numbers.push(AtSign[2][1]);
		else if (operand1 == 'c' && operand2 == 'c')
			numbers.push(AtSign[2][2]);
		
		break;
	case '#':
		if (operand1 == 'a' && operand2 == 'a')
			numbers.push(HashTag[0][0]);
		else if (operand1 == 'a' && operand2 == 'b')
			numbers.push(HashTag[0][1]);
		else if (operand1 == 'a' && operand2 == 'c')
			numbers.push(HashTag[0][2]);
		else if (operand1 == 'b' && operand2 == 'a')
			numbers.push(HashTag[1][0]);
		else if (operand1 == 'b' && operand2 == 'b')
			numbers.push(HashTag[1][1]);
		else if (operand1 == 'b' && operand2 == 'c')
			numbers.push(HashTag[1][2]);
		else if (operand1 == 'c' && operand2 == 'a')
			numbers.push(HashTag[2][0]);
		else if (operand1 == 'c' && operand2 == 'b')
			numbers.push(HashTag[2][1]);
		else if (operand1 == 'c' && operand2 == 'c')
			numbers.push(HashTag[2][2]);
		break;
	case '&':
		if (operand1 == 'a' && operand2 == 'a')
			numbers.push(Ampersand[0][0]);
		else if (operand1 == 'a' && operand2 == 'b')
			numbers.push(Ampersand[0][1]);
		else if (operand1 == 'a' && operand2 == 'c')
			numbers.push(Ampersand[0][2]);
		else if (operand1 == 'b' && operand2 == 'a')
			numbers.push(Ampersand[1][0]);
		else if (operand1 == 'b' && operand2 == 'b')
			numbers.push(Ampersand[1][1]);
		else if (operand1 == 'b' && operand2 == 'c')
			numbers.push(Ampersand[1][2]);
		else if (operand1 == 'c' && operand2 == 'a')
			numbers.push(Ampersand[2][0]);
		else if (operand1 == 'c' && operand2 == 'b')
			numbers.push(Ampersand[2][1]);
		else if (operand1 == 'c' && operand2 == 'c')
			numbers.push(Ampersand[2][2]);
		break;
	}
	operations.pop();
}




