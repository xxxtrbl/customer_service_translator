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

	//���Խű��ļ�
	vector<string> test_script;

	//��¼�������Ľ���
	int index = 0;

public:

	//��ȡ�ű��﷨��,��cur_step����Ϊentry_step
	Interpreter();

	//���з���
	void Interpret();

	//Ӧ��ӿ�,��������0
	int answer_API();

	//���½ű���Ӧ���û����ݱ�
	~Interpreter();

	//����׮�����ݲ�ͬ��cur_step�����в���
	void testCur_step();

	//�������Խű��ļ�
	void make_test_script();
};