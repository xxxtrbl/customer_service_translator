#pragma once
#include"dataStructure.h"
#include"Parser.h"
#include"step.h"

class Interpreter {

private:
	
	//Interpreterͨ������_parser���ɶ�Ӧ��script�﷨����_script��������õ����﷨��
	Parser _parser;
	Script _script;

	//��ʾInterpreter����ִ��ʱ�ĵ�ǰ����
	Step cur_step;

public:

	//��ȡ�ű��﷨��,��cur_step����Ϊentry_step
	Interpreter();

	//���з���
	void Interpret();

	//���½ű���Ӧ���û����ݱ�
	~Interpreter();
};