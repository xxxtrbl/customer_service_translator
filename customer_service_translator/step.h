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
	//��StepId��ʼ��Ϊ""
	Step();
	//����speak
	void speakProcess(vector<Token>& tokens);
	//����listen
	void listenProcess(vector<string>& tokens);
	//����branch
	void branchProcess(vector<string>& tokens);
	//����silence
	void silenceProcess(Token token);
	//����default
	void defaultProcess(Token token);
	//����exit
	void exitProcess();
	//����stepId
	void initialStepid(StepId& _stepid);
	//ִ��Speak
	void executeSpeak();
	//ִ��Listen
	string executeListen();
	//��ȡsilence��StepId
	StepId get_silence_id();
	//�����û������ȡStepid
	StepId get_certain_id(Answer ans);
	//��ȡdefault��Step_id
	StepId get_default_id();
	//�鿴�Ƿ�Ϊ�սᲽ��
	bool if_terminate();
	//��ȡstepID
	StepId getStepid();
	//����step
	Step& operator = (const Step& s);
	//��ѯ������
	bool checkVar(Varname var, string strnm);
	//�����û�
	bool addItem(string namem, double money);
	//��ѯ
	string findVar(Varname svar, Varname ovar, string nm);
	//�޸Ľ��
	void changeMoney();
};