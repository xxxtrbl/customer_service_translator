#pragma once
#include"dataStructure.h"
#include<ctime>
#include<string.h>

class Step {
private:
	Expression _speak;
	Listen _listen;
	map<Answer, StepId> _answer;
	StepId _silence;
	StepId _default;
	StepId _stepid;

	bool _terminate;

public:
	//将StepId初始设为""
	Step();
	//处理speak
	void speakProcess(vector<Token>& tokens);
	//处理listen
	void listenProcess(vector<string>& tokens);
	//处理branch
	void branchProcess(vector<string>& tokens);
	//处理silence
	void silenceProcess(Token token);
	//处理default
	void defaultProcess(Token token);
	//处理exit
	void exitProcess();
	//设置stepId
	void initialStepid(StepId& _stepid);
	//执行Speak
	void executeSpeak();
	//执行Listen
	string executeListen();
	//获取silence的StepId
	StepId get_silence_id();
	//根据用户意向获取Stepid
	StepId get_certain_id(Answer ans);
	//获取default的Step_id
	StepId get_default_id();
	//查看是否为终结步骤
	bool if_terminate();
	//获取stepID
	StepId getStepid();
	//拷贝step
	Step& operator = (const Step& s);
	//查询变量名
	bool checkVar(Varname var, string strnm);
	//创建用户
	bool addItem(string namem, double money);
	//查询
	string findVar(Varname svar, Varname ovar, string nm);
	//修改金额
	void changeMoney();
};