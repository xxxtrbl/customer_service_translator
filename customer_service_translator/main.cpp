#include"dataStructure.h"
#include"Interpreter.h"
#include<winsock.h>

string script_file_name;
string data_file_name;
File data_file;
string name = "xxxtrbl";
double amount = 9.99;
int main()
{
	cout << "������Ҫ����Ľű��ļ���:" << endl;
	cin >> script_file_name;
	cout << "�������Ӧ�������ļ���:" << endl;
	cin >> data_file_name;
	Interpreter _interpreter;
	_interpreter.Interpret();
	
	system("PAUSE");
	return 0;
}