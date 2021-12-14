#include"step.h"

extern string name;
extern double amount;
extern File data_file;
extern string data_file_name;
extern ofstream test_stream;

//��ʼ��Step�ĳ�Ա����
Step::Step() {
	this->_silence = "";
	this->_default = "";
	this->_stepid = "";
	this->_listen = "";
	this->_terminate = false;
}

//����speak
void Step::speakProcess(vector<Token>& tokens)
{
	Item _item;

	for (auto it = tokens.begin()+1; it < tokens.end(); it++)
	{
		_item.answer = "";
		_item.var = "";

		//�������Ǳ��������ṹ���е�var,�Ӻ�����ԣ��������Ȼ���������ṹ���answer��
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
			_item.answer = (*it);
		}
		_speak.push_back(_item);
	}
}

//����listen
void Step::listenProcess(vector<Token>& tokens)
{
	if(tokens.size()>1)
		this->_listen = tokens[1];
}

//������ "xxx" , stepid��tokensת��Ϊmap�ṹ
void Step::branchProcess(vector<string>& tokens)
{
	_answer.emplace(tokens[1], tokens[3]);
}

//����silence
void Step::silenceProcess(Token silence_token)
{
	_silence = silence_token;
}

//����default
void Step::defaultProcess(Token default_token)
{
	_default = default_token;
}

//����exit
void Step::exitProcess()
{
	this->_terminate = true;
}

//����stepId
void Step::initialStepid(StepId& _stepid)
{
	this->_stepid = _stepid;
}

//ִ��Speak
void Step::executeSpeak()
{
	Answer outstr = "";

	//���������������Ȼ���
	for (auto it = _speak.begin(); it != _speak.end(); it++)
	{
		if ((*it).answer.length() > 0)
		{
			outstr = outstr + (*it).answer + " ";
		}
		else if ((*it).var.length() > 0)
		{
			/*���������ֵ*/
			if ((*it).var == "$name")
			{
				outstr += name;
			}
			else if ((*it).var == "$amount")
			{
				outstr += to_string(amount);
			}
		}
	}
	this->speak_API(outstr);
}
void Step::speak_API(Answer ans_str)
{
	test_stream << ans_str << endl;
}
//ִ��Listen
string Step::executeListen(string str)
{
	//����Ǵ�����������ݱ�����������������ݱ���޸��ļ�����������@tag����
	if (this->_listen == "$name")
	{
		if (this->_answer.size() > 0)
		{
			bool check = this->checkVar(this->_listen, str);
			if (check)
			{
				if (this->_listen == "$name")
				{
					name = str;
					amount = stof( this->findVar("$name", "$money", str));
				}
				else
				{
					amount = stof(str);
					name = this->checkVar("$name", to_string(amount));
				}
				return "True";
			}
			else
				return "False";
		}
		else
		{
			name = str;
			amount = 0;
			this->addItem(name,amount);
			return "@tag";
		}
	}
	else if (this->_listen == "$money")
	{
		amount += atof(str.c_str());
		//������data_file�ļ���
		this->changeMoney();
		return "@tag";
	}
	else if (this->_listen.size() > 0)
	{
		cout << _listen<<endl;
		return "@tag";
	}

	//����û������Ƿ���ź�Ҫ�󣬲�����תsilence
	if (this->_answer.size() > 0&&_answer.count(str)!=1)
	{
		cout<<"silence..."<<endl;
		str = "";
	}
	//�����ǰΪͶ�߽׶Σ�����û�Ͷ������
	else if (this->_answer.size() == 0)
	{
		//���û������������ļ�complaint.txt��
		ofstream complain;
		complain.open("complaint.txt", ios::app);
		complain<<"["<<name<<"]" << str << endl;
		//���Ϊtag
		str = "@tag";
		complain.close();
	}

	return str;
}

//��ȡsilence��StepId
StepId Step::get_silence_id()
{
	return _silence;
}

//��ȡdefault��Step_id
StepId Step::get_default_id()
{
	return _default;
}

//�����û������ȡStepid
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

//��ȡstepID
StepId Step::getStepid()
{
	return this->_stepid;
}

//�鿴�Ƿ�Ϊ�սᲽ��
bool Step::if_terminate()
{
	return this->_terminate;
}

//����step
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

//��ѯ�����Ƿ������ݿ��д���
bool Step::checkVar(Varname var, string strnm)
{
	int i;

	for (i = 0; i < data_file[0].size(); i++)
	{
		if (data_file[0][i] == var)
			break;
	}
	for (int j = 1; j < data_file.size(); j++)
	{
		if (data_file[j][i] == strnm)
		{
			return true;
		}
	}
	return false;
}

//�����û�
bool Step::addItem(string name, double money)
{
	ofstream create;
	create.open(data_file_name, ios::app);
	create << name << " " << money << endl;
	create.close();
	return true;
}

//�޸����
void Step::changeMoney()
{
	int index_money;
	int index_name;
	for (int k = 0; k < data_file[0].size(); k++)
	{
		if (data_file[0][k] == "$money")
		{
			index_money = k;
		}
		else if (data_file[0][k] == "$name")
		{
			index_name = k;
		}
	}
	for (int i = 0; i < data_file.size(); i++)
	{
		if (data_file[i][index_name] == name)
		{
			data_file[i][index_money] = to_string( amount);
			break;
		}
	}
}

//���ұ���
string Step::findVar(Varname svar, Varname ovar, string nm)
{
	int s, o;

	for (int i = 0; i < data_file[0].size(); i++)
	{
		if (data_file[0][i] == svar)
		{
			s = i;
		}
		else if (data_file[0][i] == ovar)
		{
			o = i;
		}
	}
	for (int j = 1; j < data_file.size(); j++)
	{
		if (data_file[j][s] == nm)
		{
			return data_file[j][o];
		}
	}
	return "-1";
}