#pragma once
#include"dataStructure.h"
#include"Parser.h"
#include"step.h"

class Interpreter {
private:
	Parser _parser;
	Script _script;
	Step cur_step;

public:
	//��ȡ�ű��﷨��,��cur_step����Ϊentry_step
	Interpreter();
	//���з���
	void Interpret();

	~Interpreter();
};