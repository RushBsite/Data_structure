//2016726028 이민재
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int numberN; //pw 의 길이 최소 3 최대 30
int counter = 0; // 패턴 반복수


string decoder(istream& ins);
//precond : 입력스트림통해 긴 소문자 알파벳으로 이루어진문자열 입력받음
//postcond : 가장 많이 중복된 패턴을 반환

void printProgress(int count, int EOS);
//pre 없음
//postcond : 진행도를 출력


int main()
{
	cin.tie(NULL); // 입출력속도 늘리기
	ios::sync_with_stdio(false); // 출력속도 빠르게
	cin >> numberN; // pw 길이
	cin.ignore();

	cout << decoder(cin) << endl;
	
}

string decoder(istream& ins)
{
	unordered_map<string, int> m;
	unordered_map<string, int> ::iterator it;

	string buf; //입력 스트링
	
	string ans; //최다 빈출 패스워드 스트링

	getline(cin, buf);
	vector<char> inputCode(buf.begin(), buf.end());
	
	int EOS = inputCode.size() - numberN + 1;

	
	cout << "\r"<< "Loading target code";
	cout.flush();
	for(int i = 0; i< EOS; i++) // numberN =3 이고 aabbccddeeff 입력시 마지막 문자열은 'eff' 
	{
		string pwd; // 페스워드 패턴 저장할 스트링
		for (int j = i; j < i+numberN; j++)
			pwd += inputCode[j];
		
		m[pwd]++; //없으면 set 생성, 있으면 키값 증가
		//printProgress(i + 1, EOS);
	}

	int index;
	int max_index = std::distance(m.begin(), m.end());
	cout << "\r" <<"find pattern in "<< max_index << endl;;
	for(it = m.begin(); it !=m.end();it++) 
	{
		//index = std::distance(m.begin(), it);
		if((it->second) > counter) // iterator 탐색 최대 빈도수 갱신시
		{
			counter = it->second;
			ans = it->first; // 해당키값의 문자열
		}
		//cout <<"\r"<< "[" << index+1 << "/" << max_index << "]"; 로깅 오버헤드
	}
	cout << endl;
	return ans;
}

void printProgress(int count , int EOS)
{ //count 현재 진행된 작업 // EOS 최대값
	char bar = '=';
	char blank = ' ';
	int LEN = 20; //프로그래스 바 길이

	int bar_count; // 바 갯수 저장
	float percent; // 퍼센트 저장
	
	float tick = (float)100 / LEN; //1틱의 백분율

	if (count <= EOS)
	{
		cout << "\r" << count << "/" << EOS << "[";
		percent = (float)count / EOS * 100; // 퍼센트 연산
		bar_count = percent / tick; // 프로그래스 바 갯수 계산
		for(int i=0; i<LEN; i++)
		{
			if (bar_count > i) cout << bar;
			else			   cout << blank;
		}
		cout << "]";
		cout.flush();
	}
	
}


