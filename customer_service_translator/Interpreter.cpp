#include"Interpreter.h"

extern string name;
extern double money;

Interpreter::Interpreter()
{
	StepId id;

	//parser创建执行环境，构建语法树存入_script中
	this->_parser.Parse();
	this->_script = this->_parser.getScript();

	//将当前Step置为entryStep
	id =this->_script.getEntry();
	this->cur_step = this->_script._step[id];
}
void Interpreter::Interpret()
{
	//从entryStep开始逐步执行，遇到终结步骤则跳出循环
	do
	{
		//记录cur_step的id
		StepId id = cur_step.getStepid();

		//先执行Speak
		cur_step.executeSpeak();

		//如果本步骤是终结步骤,则结束循环,断开通话
		if (cur_step.if_terminate())
		{
			break;
		}

		//执行listen
		string str = cur_step.executeListen();
		if (str == "" )
		{
			//用户无应答，cur_step跳转到silence step
			cur_step = _script._step[cur_step.get_silence_id()];
			continue;
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
			continue;
		}
		//如果本步骤是终结步骤,则结束循环,断开通话
		if (cur_step.if_terminate())
		{
			break;
		}
		//判断step是否有改变,如果没有则跳入default step中
		if (id == cur_step.getStepid())
		{
			cur_step = _script._step[ cur_step.get_default_id()];
		}

	} while (true);
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
}