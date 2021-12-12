#include"Parser.h"
//读文件到script_file中,以行为单位
void Parser:: parseFile()
{
	file.open("script1.txt", ios::in);
	string strLine;
	vector<string> words;

	//逐行读取脚本文件,用空格分割,存入script_file中
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

	auto i = script_file.begin();
	//以行为单位处理script,根据每行的TOKEN选择处理方式
	for (; i != script_file.end(); i++)
	{
		processTokens(*i);
	}

	//添加最后一个step
	StepId id = cur_step.getStepid();
	_script.addStep(id, cur_step);
}
void Parser::processTokens(vector<Token>& tokens)
{
	Token token = tokens[0];

	//根据不同的token选择不同的构建方法
	if (token == "Step")
	{
		StepId id = cur_step.getStepid();

		
		if (id != "")
		{
			
			if (_script._step.size() == 0)
				_script.setEntry(id);

			/*上一个step处理完毕,将其插入Script中*/
			_script.addStep(id, cur_step);
			
		}
			

		/*进入到新创建的step*/
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
void Parser::Parse()
{
	//读取脚本文件
	this->parseFile();
	//建立脚本语法树
	this->buildTree();
}
Script& Parser::getScript()
{
	return this->_script;
}