//2016726028 이민재

#include <iostream>
#include <stack>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

char AtSign[3][3];
char HashTag[3][3];
char Ampersand[3][3];

char read_and_evaluate(istream& ins);
//precond: 입력스트림을 통해 a/b/c, @#& 와 괄호들을 입력받음 (이외의 문자들 무시)
//
//postcond: 입력된 요소들 이용하여 evaluate 한 number을 return
//EOI 문자열 입력되면 종료
//에러 발생시 에러메시지 출력
void evaluate_stack(stack<char>& numbers, stack<char>& operations);
//precond: numbers(a,b,c) stack 과 operations(@,#,& 과 괄호)
//postcond: 각 stack에 저장된 연산자들과 number을 이용하여 연산
//연산할 operand없으면 에러메시지 출력
void open_file();
//precond: 없음
//postcond: 동일 디렉토리 위치한 결과값txt파일 읽어 배열에 저장함.

int main()
{
	open_file();

	while (true) //main loop
	{


		try
		{
			cout << read_and_evaluate(cin) << endl;
			cin.ignore(); // '\n' 무시
		}
		catch (int expn) // 예외에 따라 처리한다
		{
		
			if (expn == -1) {
				cout << "Error!: unbalanced parenthesis" << endl;
			} // 올바르지 않은 괄호문일 때 예외 처리
			else if (expn == -2) {
				cout << "Error!: missing operands" << endl;
			} // 연산할 대상이 없을때 예외 처리

			while (cin.peek() != '\n') // 입력 스트림을 '\n' 전까지 무시한다
				cin.ignore();
			cin.ignore(); 
		}
	}
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
			string str(tmp1); //char 배열을 문자열로
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
char read_and_evaluate(istream& ins)
{
	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';
	const char RIGHT_CURLY_BRACKET = '}';
	const char RIGHT_SQUARE_BRACKET = ']';

	stack<char> numbers;
	stack<char> operations;
	stack<char> parenthesis; // 괄호 stack
	
	char number;
	char symbol;

	
	while (ins && ins.peek() != '\n')
	{
		if (ins.peek() == 'a' || ins.peek() == 'b' || ins.peek() == 'c' || (ins.peek() == DECIMAL)) //a,b,c 와 . 입력받음
		{
			ins >> number;
			numbers.push(number);
		}
		else if (strchr("@#", ins.peek()) != NULL) // 낮은 우선순위 경우
		{
			if (operations.empty() == false && strchr("@#&", operations.top()) != NULL)
				evaluate_stack(numbers, operations);
			ins >> symbol;
			operations.push(symbol);
		}
		else if (strchr("&", ins.peek()) != NULL) { // 높은 우선순위 경우
			ins >> symbol;
			if (operations.empty() == false && strchr("&", operations.top()) != NULL)
				evaluate_stack(numbers, operations);

			operations.push(symbol);
		}
		else if (strchr("([{", ins.peek()) != NULL) { // 왼쪽 괄호 push
			ins >> symbol;
			operations.push(symbol);
			parenthesis.push(symbol);
		}
		else if (ins.peek() == RIGHT_PARENTHESIS || ins.peek() == RIGHT_CURLY_BRACKET|| ins.peek() == RIGHT_SQUARE_BRACKET)
		{
			ins >> symbol;
			switch (symbol)
			{
			case RIGHT_PARENTHESIS: //오른쪽 소괄호 
				if (parenthesis.empty() == true)
					throw - 1;
				if (parenthesis.top() == '(') // 짝 맞는지 검사
				{
					parenthesis.pop();
					while (operations.top() != '(')
						evaluate_stack(numbers, operations); // 짝이 top 에올때까지 evalutae 
					operations.pop(); // 괄호 pop
				}
				else
					throw - 1;
				
				break;
			case RIGHT_CURLY_BRACKET:
				if (parenthesis.empty() == true)
					throw - 1;
				if (parenthesis.top() == '{')
				{
					parenthesis.pop();
					while (operations.top() != '{')
						evaluate_stack(numbers, operations);
					operations.pop();
				}
				else
					throw - 1;
				break;
			case RIGHT_SQUARE_BRACKET:
				if (parenthesis.empty() == true)
					throw - 1;
				if (parenthesis.top() == '[')
				{
					parenthesis.pop();
					while (operations.top() != '[')
						evaluate_stack(numbers, operations);
					operations.pop();
				}
				else
					throw - 1;
				break;
			default: throw - 1;
			}
			
			
			
		}

		else
		{
			if (ins.peek() == 'E') //EOI 입력시 종료
			{
				char tmp[3];
				char eoi[] = "EOI";
				ins >> tmp;
				if (strcmp(tmp, eoi) == 0)
					exit(0);
			}
			ins.ignore();
		}
		
	}

	while (!operations.empty()) // 괄호 없을경우 계산
		evaluate_stack(numbers, operations);
	
	return numbers.top();
}

void evaluate_stack(stack<char>& numbers, stack<char>& operations)
{
	char operand1, operand2;

	// 계산 할 대상이 없을 때 예외를 던진다
	if (numbers.empty()) throw - 2;
	operand2 = numbers.top();
	numbers.pop();

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