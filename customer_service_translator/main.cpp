#include"dataStructure.h"
#include"Interpreter.h"
#include<winsock.h>

string script_file_name = "script.txt";
string data_file_name = "data.txt";
string test_out = "test_out.txt";
ofstream test_stream;
File data_file;
string name = "xxxtrbl";
double amount = 9;

int main()
{
	Interpreter _interpreter;
	_interpreter.Interpret();
	
	system("PAUSE");
	return 0;
}