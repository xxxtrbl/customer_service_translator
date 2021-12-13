#include"Parser.h"


//读文件到script_file中,以行为单位
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
	//读取脚本文件
	this->parseFile(script_file_name,script_file);
	//读取数据文件
	this->parseFile(data_file_name, data_file);
	//将变量存入var中
	this->parseVars();
	//建立脚本语法树
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