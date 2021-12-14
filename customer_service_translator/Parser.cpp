#include"Parser.h"


//以行为单位, 读文件到script_file中
void Parser:: parseFile(string sfname,File& ofname)
{
	ifstream file;
	file.open(sfname, ios::in);
	string strLine;
	Line words;

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
		ofname.push_back(words);
	}
	file.close();
}

//建立语法树
void Parser::buildTree()
{
	
	Token token;
	
	//以行为单位处理script,根据每行的TOKEN选择处理方式
	for (auto i = script_file.begin(); i != script_file.end(); i++)
	{
		processTokens(*i);
	}

	//添加最后一个step，防止遗漏
	StepId id = cur_step.getStepid();
	_script.addStep(id, cur_step);

}

//处理tokens
void Parser::processTokens(vector<Token>& tokens)
{
	//获取关键字
	Token token = tokens[0];

	//根据不同的关键字选择不同的构建方法
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

//处理变量
void Parser::parseVars()
{
	auto it = data_file.begin();
	for (auto i = (*it).begin(); i != (*it).end(); i++)
	{
		this->_script.addVars((*i));
	}
}

//语法分析
void Parser::Parse()
{
	//读取脚本文件
	this->parseFile(script_file_name,script_file);
	//读取数据文件
	this->parseFile(data_file_name, data_file);
	//将变量存入var中
	this->parseVars();
	//建立脚本语法树
	this->buildTree();
}

//获取语法树
Script& Parser::getScript()
{
	return this->_script;
}

//测试桩：测试不同tokens的处理结果并输出
void Parser::test_processTokens()
{
	vector<vector<Token>> tokens = {
		{"Step" , "test"},
		{"Speak", "$name","+","test"},
		{"Listen"},
		{"Branch","投诉" , "complainProc"},
		{"Branch","账单" , "billProc"},
		{"Branch" ,"主页" , "defaultProc"},
		{"Silence", "silenceProc"},
		{"Default","defaultProc"},
		{"Exit"}
	};

	for (int i = 0; i < tokens.size(); i++)
	{
		this->processTokens(tokens[i]);
	}
}