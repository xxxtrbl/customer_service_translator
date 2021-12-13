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
	//获取脚本语法树,将cur_step设置为entry_step
	Interpreter();
	//进行翻译
	void Interpret();

	~Interpreter();
};