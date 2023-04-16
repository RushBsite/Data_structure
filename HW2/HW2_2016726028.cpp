//2016726028 �̹���

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
//precond: �Է½�Ʈ���� ���� a/b/c, @#& �� ��ȣ���� �Է¹��� (�̿��� ���ڵ� ����)
//
//postcond: �Էµ� ��ҵ� �̿��Ͽ� evaluate �� number�� return
//EOI ���ڿ� �ԷµǸ� ����
//���� �߻��� �����޽��� ���
void evaluate_stack(stack<char>& numbers, stack<char>& operations);
//precond: numbers(a,b,c) stack �� operations(@,#,& �� ��ȣ)
//postcond: �� stack�� ����� �����ڵ�� number�� �̿��Ͽ� ����
//������ operand������ �����޽��� ���
void open_file();
//precond: ����
//postcond: ���� ���丮 ��ġ�� �����txt���� �о� �迭�� ������.

int main()
{
	open_file();

	while (true) //main loop
	{


		try
		{
			cout << read_and_evaluate(cin) << endl;
			cin.ignore(); // '\n' ����
		}
		catch (int expn) // ���ܿ� ���� ó���Ѵ�
		{
		
			if (expn == -1) {
				cout << "Error!: unbalanced parenthesis" << endl;
			} // �ùٸ��� ���� ��ȣ���� �� ���� ó��
			else if (expn == -2) {
				cout << "Error!: missing operands" << endl;
			} // ������ ����� ������ ���� ó��

			while (cin.peek() != '\n') // �Է� ��Ʈ���� '\n' ������ �����Ѵ�
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
			string str(tmp1); //char �迭�� ���ڿ���
			str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // �о�� ���� ���� ����
			//���ڿ��� char �迭��
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
	stack<char> parenthesis; // ��ȣ stack
	
	char number;
	char symbol;

	
	while (ins && ins.peek() != '\n')
	{
		if (ins.peek() == 'a' || ins.peek() == 'b' || ins.peek() == 'c' || (ins.peek() == DECIMAL)) //a,b,c �� . �Է¹���
		{
			ins >> number;
			numbers.push(number);
		}
		else if (strchr("@#", ins.peek()) != NULL) // ���� �켱���� ���
		{
			if (operations.empty() == false && strchr("@#&", operations.top()) != NULL)
				evaluate_stack(numbers, operations);
			ins >> symbol;
			operations.push(symbol);
		}
		else if (strchr("&", ins.peek()) != NULL) { // ���� �켱���� ���
			ins >> symbol;
			if (operations.empty() == false && strchr("&", operations.top()) != NULL)
				evaluate_stack(numbers, operations);

			operations.push(symbol);
		}
		else if (strchr("([{", ins.peek()) != NULL) { // ���� ��ȣ push
			ins >> symbol;
			operations.push(symbol);
			parenthesis.push(symbol);
		}
		else if (ins.peek() == RIGHT_PARENTHESIS || ins.peek() == RIGHT_CURLY_BRACKET|| ins.peek() == RIGHT_SQUARE_BRACKET)
		{
			ins >> symbol;
			switch (symbol)
			{
			case RIGHT_PARENTHESIS: //������ �Ұ�ȣ 
				if (parenthesis.empty() == true)
					throw - 1;
				if (parenthesis.top() == '(') // ¦ �´��� �˻�
				{
					parenthesis.pop();
					while (operations.top() != '(')
						evaluate_stack(numbers, operations); // ¦�� top ���ö����� evalutae 
					operations.pop(); // ��ȣ pop
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
			if (ins.peek() == 'E') //EOI �Է½� ����
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

	while (!operations.empty()) // ��ȣ ������� ���
		evaluate_stack(numbers, operations);
	
	return numbers.top();
}

void evaluate_stack(stack<char>& numbers, stack<char>& operations)
{
	char operand1, operand2;

	// ��� �� ����� ���� �� ���ܸ� ������
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