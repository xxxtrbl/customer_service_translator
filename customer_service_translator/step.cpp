#include"step.h"

Step::Step() {
	this->_silence = "";
	this->_default = "";
	this->_stepid = "";
	this->_terminate = false;
}
void Step::speakProcess(vector<Token>& tokens)
{
	Item _item;

	for (auto it = tokens.begin()+1; it < tokens.end(); it++)
	{
		if ((*it)[0] == '$')
		{
			_item.var = (*it)[0];
		}
		else if ((*it) == "+")
		{
			continue;
		}
		else
		{
			_item.out = (*it);
		}
		_speak.push_back(_item);
	}
}
void Step::listenProcess(vector<Token>& tokens)
{
	//把形如 b , e 的tokens转化成listen结构
	_listen.beginTimer = stoi(tokens[1]);
	_listen.endTimer = stoi(tokens[3]);
}
void Step::branchProcess(vector<string>& tokens)
{
	//把形如 "xxx" , stepid的tokens转化为map结构
	_answer.emplace(tokens[1], tokens[3]);
}
void Step::silenceProcess(Token silence_token)
{
	_silence = silence_token;
}
void Step::defaultProcess(Token default_token)
{
	_default = default_token;
}
void Step::exitProcess()
{
	this->_terminate = true;
}
void Step::initialStepid(StepId& _stepid)
{
	this->_stepid = _stepid;
}
void Step::executeSpeak()
{
	for (auto it = _speak.begin(); it != _speak.end(); it++)
	{
		if ((*it).out.length() > 0)
		{
			string s((*it).out.begin() + 1, (*it).out.end() - 1);
			cout << s<<" ";
		}
		else if ((*it).var.length() > 0)
		{
			/*变量输出真值*/
			if ((*it).var == "$name")
			{
				cout << "xxxtrbl";
			}
			else if ((*it).var == "$amount")
			{
				cout << "100";
			}
		}
	}
}
string Step::executeListen()
{
	int interval = this->_listen.endTimer - this->_listen.beginTimer;
	string str = NULL;
	cin >> str;
	if (str == "\n")
	{
		Sleep(interval * 100);
	}
	return str;
}
StepId Step::get_silence_id()
{
	return _silence;
}
StepId Step::get_default_id()
{
	return _default;
}
StepId Step::get_certain_id(Answer ans)
{
	if (_answer.count(ans) == 1)
	{
		return _answer[ans];
	}
	else
	{
		return NULL;
	}
}
StepId Step::getStepid()
{
	return this->_stepid;
}