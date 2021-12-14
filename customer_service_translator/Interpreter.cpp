#include"Interpreter.h"

extern string name;
extern double money;
extern string test_out ;
extern ofstream test_stream;

//获取脚本语法树,将cur_step设置为entry_step
Interpreter::Interpreter()
{
	StepId id;

	//parser创建执行环境，构建语法树存入_script中
	this->_parser.Parse();
	this->_script = this->_parser.getScript();

	//将当前Step置为entryStep
	id =this->_script.getEntry();
	this->cur_step = this->_script._step[id];

	this->make_test_script();
	test_stream.open(test_out, ios::app);
}

//进行翻译
void Interpreter::Interpret()
{
	Step welcome_step = this->cur_step;
	int flag = 1;

	//从entryStep开始逐步执行，遇到终结步骤则跳出循环
	do
	{
		//记录cur_step的id
		StepId id = cur_step.getStepid();
		
		//先执行Speak
		cur_step.executeSpeak();

		if (flag == 0)
		{
			break;
		}

		//如果本步骤是终结步骤,则结束循环,断开通话
		if (cur_step.if_terminate())
		{
			//break;
			//system("PAUSE");
			cur_step = welcome_step;
		}

		flag = this->answer_API();
		
		

		//如果本步骤是终结步骤,则结束循环,断开通话
		if (cur_step.if_terminate())
		{
			//break;
			//system("PAUSE");
			cur_step = welcome_step;
		}
		//判断step是否有改变,如果没有则跳入default step中
		if (id == cur_step.getStepid())
		{
			cur_step = _script._step[ cur_step.get_default_id()];
		}
	} while (true);

}

//应答接口
int Interpreter::answer_API()
{
	string answer_str = "";
	if (index < test_script.size())
	{
		answer_str = this->test_script[index++];
		test_stream << answer_str << endl;
	}
	else
	{
		cout<< "测试结束..." << endl;
		return 0;
	}

	//执行listen
	string str = cur_step.executeListen(answer_str);
	if (str == "")
	{
		//用户无应答，cur_step跳转到silence step
		cur_step = _script._step[cur_step.get_silence_id()];
	}
	else if (str == "@tag")
	{
		//@tag为Robot只听取用户输入而不做出响应回应的情况，此时自动跳到default_step中
		cur_step = _script._step[cur_step.get_default_id()];
	}
	else
	{
		//根据用户的输入找到Robot应该跳转的地方
		StepId next_id;
		next_id = cur_step.get_certain_id(str);
		if (_script._step.count(next_id) != 1)
		{
			next_id = cur_step.get_default_id();
		}
		cur_step = _script._step[next_id];
	}
	return 1;
}

//更新用户文件
Interpreter::~Interpreter()
{
	ofstream out(data_file_name);
	for (auto it = data_file.begin(); it != data_file.end(); it++)
	{
		for (int i = 0; i < (*it).size(); i++)
		{
			out << (*it)[i] << " ";
		}
		out << endl;
	}
	out.close();

	test_stream.close();
}

//测试桩，根据不同的cur_step来进行测试
void Interpreter::testCur_step()
{
	for (auto it = this->_script._step.begin(); it != this->_script._step.end(); it++)
	{
		this->cur_step = it->second;
		this->Interpret();
	}
}

//构建测试脚本文件
void Interpreter::make_test_script()
{
	ifstream file;
	file.open("test.txt", ios::in);
	string strLine;

	//逐行读取脚本文件,用空格分割,存入test_script中
	while (getline(file, strLine))
	{
		if (strLine.empty())
			continue;

		test_script.push_back(strLine);
	}
	file.close();
}