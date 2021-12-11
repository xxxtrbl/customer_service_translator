#include"Parser.h"
//���ļ���script_file��,����Ϊ��λ
void Parser:: parseFile()
{
	file.open("script.txt", ios::in);
	string strLine;
	vector<string> words;

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
		script_file.push_back(words);
	}
}
//Build grammer tree by building a script and other steps of the script structure.
void Parser::buildTree()
{
	
	Token token;

	//����Ϊ��λ����script,����ÿ�е�TOKENѡ����ʽ
	for (auto i = script_file.begin(); i != script_file.end(); i++)
	{
		processTokens(*i);
	}
}
void Parser::processTokens(vector<Token>& tokens)
{
	Token token = tokens[0];

	//���ݲ�ͬ��tokenѡ��ͬ�Ĺ�������
	if (token == "Step")
	{
		StepId id = cur_step.getStepid();

		if(id!="")
			/*��һ��step�������,�������Script��*/
			_script.addStep(id,cur_step);

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
		cur_step.silenceProcess(tokens[1]);
	else if (token == "Exit")
		cur_step.exitProcess();
}
void Parser::Parse()
{
	//��ȡ�ű��ļ�
	this->parseFile();
	//�����ű��﷨��
	this->buildTree();
}
Script& Parser::getScript()
{
	return this->_script;
}