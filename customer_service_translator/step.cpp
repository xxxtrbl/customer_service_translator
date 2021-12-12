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
		_item.out = "";
		_item.var = "";
		if ((*it)[0] == '$')
		{
			_item.var = (*it);
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
			cout << (*it).out<< " ";
		}
		else if ((*it).var.length() > 0)
		{
			/*变量输出真值*/
			if ((*it).var == "$name")
			{
				cout << "xxxtrbl ";
			}
			else if ((*it).var == "$amount")
			{
				cout << "100 ";
			}
		}
	}
	cout << endl;
}
string Step::executeListen()
{
	int interval = this->_listen.endTimer - this->_listen.beginTimer;
	string str = "";
	cin >> str;

	if (this->_answer.size() > 0&&_answer.count(str)!=1)
	{
		cout<<"silence..."<<endl;
		//Sleep(100);
		str = "";
	}
	else if (this->_answer.size() == 0)
	{
		//将用户的意见输出到文件中
		ofstream complain;
		complain.open("complaint.txt", ios::app);
		complain << str << endl;
		//标记为commit
		str = "@commit";
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
		return "";
	}
}
StepId Step::getStepid()
{
	return this->_stepid;
}
bool Step::if_terminate()
{
	return this->_terminate;
}
Step& Step:: operator = (const Step& s) {
	if (this == &s) {
		return *this;
	}

	this->_speak = s._speak;
	this->_listen = s._listen;
	this->_answer = s._answer;
	this->_silence = s._silence;
	this->_default = s._default;
	this->_stepid = s._stepid;
	this->_terminate = s._terminate;
	return *this;
}