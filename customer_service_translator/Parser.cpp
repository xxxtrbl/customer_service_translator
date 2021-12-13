#include"Parser.h"


//���ļ���script_file��,����Ϊ��λ
void Parser:: parseFile(string sfname,File& ofname)
{
	ifstream file;
	file.open(sfname, ios::in);
	string strLine;
	Line words;

	//���ж�ȡ�ű��ļ�,�ÿո�ָ�,����script_file��
	while (getline(file, strLine))
	{
		words.clear();
		if (strLine.empty())
			continue;

		istringstream is(strLine);
		string word;
		while (is >> word)
			words.push_back(word);
		ofname.push_back(words);
	}
	file.close();
}
//Build grammer tree by building a script and other steps of the script structure.
void Parser::buildTree()
{
	
	Token token;

	auto i = script_file.begin();
	//����Ϊ��λ����script,����ÿ�е�TOKENѡ����ʽ
	for (; i != script_file.end(); i++)
	{
		processTokens(*i);
	}

	//������һ��step
	StepId id = cur_step.getStepid();
	_script.addStep(id, cur_step);
}
void Parser::processTokens(vector<Token>& tokens)
{
	Token token = tokens[0];

	//���ݲ�ͬ��tokenѡ��ͬ�Ĺ�������
	if (token == "Step")
	{
		StepId id = cur_step.getStepid();

		
		if (id != "")
		{
			
			if (_script._step.size() == 0)
				_script.setEntry(id);

			/*��һ��step�������,�������Script��*/
			_script.addStep(id, cur_step);
			
		}
		/*���뵽�´�����step*/
		cur_step = _script.processStep(tokens[1]);
	}
	else if (token == "Speak")
	{
		cur_step.speakProcess(tokens);
	}
	else if (token == "Listen")
		cur_step.listenProcess(tokens);
	else if (token == "Branch")
		cur_step.branchProcess(tokens);
	else if (token == "Silence")
		cur_step.silenceProcess(tokens[1]);
	else if (token == "Default")
		cur_step.defaultProcess(tokens[1]);
	else if (token == "Exit")
		cur_step.exitProcess();
}
void Parser::parseVars()
{
	auto it = this->data_file.begin();
	for (auto i = (*it).begin(); i != (*it).end(); i++)
	{
		this->_script.addVars((*i));
	}
}
void Parser::Parse()
{
	//��ȡ�ű��ļ�
	this->parseFile(script_file_name,script_file);
	//��ȡ�����ļ�
	this->parseFile(data_file_name, data_file);
	//����������var��
	this->parseVars();
	//�����ű��﷨��
	this->buildTree();
}
Script& Parser::getScript()
{
	return this->_script;
}
string Parser::checkVar(Varname var,string strnm)
{
	int i;

	for (i = 0; i < this->data_file[0].size(); i++)
	{
		if (data_file[0][i] == var)
			break;
	}
	for (int j = 1; j < data_file.size(); j++)
	{
		if (data_file[j][i] == strnm)
		{
			return strnm;
		}
	}
	return "";
}
bool Parser::addItem(string name,double money)
{
	ofstream create;
	create.open("complaint.txt", ios::app);
	create << name << " "<<money<<endl;
	create.close();
	return true;
}