#include"Parser.h"


//����Ϊ��λ, ���ļ���script_file��
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

//�����﷨��
void Parser::buildTree()
{
	
	Token token;
	
	//����Ϊ��λ����script,����ÿ�е�TOKENѡ����ʽ
	for (auto i = script_file.begin(); i != script_file.end(); i++)
	{
		processTokens(*i);
	}

	//������һ��step����ֹ��©
	StepId id = cur_step.getStepid();
	_script.addStep(id, cur_step);

}

//����tokens
void Parser::processTokens(vector<Token>& tokens)
{
	//��ȡ�ؼ���
	Token token = tokens[0];

	//���ݲ�ͬ�Ĺؼ���ѡ��ͬ�Ĺ�������
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

//�������
void Parser::parseVars()
{
	auto it = data_file.begin();
	for (auto i = (*it).begin(); i != (*it).end(); i++)
	{
		this->_script.addVars((*i));
	}
}

//�﷨����
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

//��ȡ�﷨��
Script& Parser::getScript()
{
	return this->_script;
}

//����׮�����Բ�ͬtokens�Ĵ����������
void Parser::test_processTokens()
{
	vector<vector<Token>> tokens = {
		{"Step" , "test"},
		{"Speak", "$name","+","test"},
		{"Listen"},
		{"Branch","Ͷ��" , "complainProc"},
		{"Branch","�˵�" , "billProc"},
		{"Branch" ,"��ҳ" , "defaultProc"},
		{"Silence", "silenceProc"},
		{"Default","defaultProc"},
		{"Exit"}
	};

	for (int i = 0; i < tokens.size(); i++)
	{
		this->processTokens(tokens[i]);
	}
}