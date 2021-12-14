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

	//测试脚本文件
	vector<string> test_script;

	//记录测试例的进度
	int index = 0;

public:

	//获取脚本语法树,将cur_step设置为entry_step
	Interpreter();

	//进行翻译
	void Interpret();

	//应答接口,结束返回0
	int answer_API();

	//更新脚本对应的用户数据表
	~Interpreter();

	//测试桩，根据不同的cur_step来进行测试
	void testCur_step();

	//构建测试脚本文件
	void make_test_script();
};