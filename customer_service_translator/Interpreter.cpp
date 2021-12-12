#include"Interpreter.h"

Interpreter::Interpreter()
{
	StepId si;

	//parser创建执行环境
	this->_parser.Parse();
	//存入语法树
	this->_script = this->_parser.getScript();
	//将当前Step置为entryStep
	si =this->_script.getEntry();
	this->cur_step = this->_script._step[si];
}
void Interpreter::Interpret()
{
	//终结步骤则跳出循环
	do
	{
		//先执行Speak
		cur_step.executeSpeak();
		//如果本步骤是终结步骤,则结束循环,断开通话
		if (cur_step.if_terminate())
		{
			break;
		}
		//执行listen
		string str = cur_step.executeListen();
		if (str == "\n" )
		{
			//cur_step跳转到silence step里
			cur_step = _script._step[cur_step.get_silence_id()];
			continue;
		}
		else
		{
			//根据用户的输入找到想要跳转的地方
			StepId next_id;
			next_id = cur_step.get_certain_id(str);
			if (_script._step.count(next_id) != 1)
			{
				next_id = cur_step.get_default_id();
			}
			cur_step = _script._step[next_id];
			continue;
		}

	} while (true);
}