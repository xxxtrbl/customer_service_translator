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
		//如果本步骤是中介步骤,则结束循环,断开通话
		if (cur_step.if_terminate())
		{
			break;
		}
		//执行listen
		string str = cur_step.executeListen();


	} while (true);
}