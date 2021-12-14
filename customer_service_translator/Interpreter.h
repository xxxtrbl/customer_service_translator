#pragma once
#include"dataStructure.h"
#include"Parser.h"
#include"step.h"

class Interpreter {

private:
	
	//Interpreter通过调用_parser生成对应的script语法树，_script用来存放用到的语法树
	Parser _parser;
	Script _script;

	//表示Interpreter解释执行时的当前步骤
	Step cur_step;

public:

	//获取脚本语法树,将cur_step设置为entry_step
	Interpreter();

	//进行翻译
	void Interpret();

	//更新脚本对应的用户数据表
	~Interpreter();
};