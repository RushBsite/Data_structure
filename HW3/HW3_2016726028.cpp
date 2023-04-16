//2016726028 �̹���
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int numberN; //pw �� ���� �ּ� 3 �ִ� 30
int counter = 0; // ���� �ݺ���


string decoder(istream& ins);
//precond : �Է½�Ʈ������ �� �ҹ��� ���ĺ����� �̷�������ڿ� �Է¹���
//postcond : ���� ���� �ߺ��� ������ ��ȯ

void printProgress(int count, int EOS);
//pre ����
//postcond : ���൵�� ���


int main()
{
	cin.tie(NULL); // ����¼ӵ� �ø���
	ios::sync_with_stdio(false); // ��¼ӵ� ������
	cin >> numberN; // pw ����
	cin.ignore();

	cout << decoder(cin) << endl;
	
}

string decoder(istream& ins)
{
	unordered_map<string, int> m;
	unordered_map<string, int> ::iterator it;

	string buf; //�Է� ��Ʈ��
	
	string ans; //�ִ� ���� �н����� ��Ʈ��

	getline(cin, buf);
	vector<char> inputCode(buf.begin(), buf.end());
	
	int EOS = inputCode.size() - numberN + 1;

	
	cout << "\r"<< "Loading target code";
	cout.flush();
	for(int i = 0; i< EOS; i++) // numberN =3 �̰� aabbccddeeff �Է½� ������ ���ڿ��� 'eff' 
	{
		string pwd; // �佺���� ���� ������ ��Ʈ��
		for (int j = i; j < i+numberN; j++)
			pwd += inputCode[j];
		
		m[pwd]++; //������ set ����, ������ Ű�� ����
		//printProgress(i + 1, EOS);
	}

	int index;
	int max_index = std::distance(m.begin(), m.end());
	cout << "\r" <<"find pattern in "<< max_index << endl;;
	for(it = m.begin(); it !=m.end();it++) 
	{
		//index = std::distance(m.begin(), it);
		if((it->second) > counter) // iterator Ž�� �ִ� �󵵼� ���Ž�
		{
			counter = it->second;
			ans = it->first; // �ش�Ű���� ���ڿ�
		}
		//cout <<"\r"<< "[" << index+1 << "/" << max_index << "]"; �α� �������
	}
	cout << endl;
	return ans;
}

void printProgress(int count , int EOS)
{ //count ���� ����� �۾� // EOS �ִ밪
	char bar = '=';
	char blank = ' ';
	int LEN = 20; //���α׷��� �� ����

	int bar_count; // �� ���� ����
	float percent; // �ۼ�Ʈ ����
	
	float tick = (float)100 / LEN; //1ƽ�� �����

	if (count <= EOS)
	{
		cout << "\r" << count << "/" << EOS << "[";
		percent = (float)count / EOS * 100; // �ۼ�Ʈ ����
		bar_count = percent / tick; // ���α׷��� �� ���� ���
		for(int i=0; i<LEN; i++)
		{
			if (bar_count > i) cout << bar;
			else			   cout << blank;
		}
		cout << "]";
		cout.flush();
	}
	
}


