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
	cout << "请输入要编译的脚本文件名:" << endl;
	cin >> script_file_name;
	cout << "请输入对应的数据文件名:" << endl;
	cin >> data_file_name;
	Interpreter _interpreter;
	_interpreter.Interpret();
	
	system("PAUSE");
	return 0;
}