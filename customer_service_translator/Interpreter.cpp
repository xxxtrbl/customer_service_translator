#include"Interpreter.h"

Interpreter::Interpreter()
{
	StepId si;

	//parser����ִ�л���
	this->_parser.Parse();
	//�����﷨��
	this->_script = this->_parser.getScript();
	//����ǰStep��ΪentryStep
	si =this->_script.getEntry();
	this->cur_step = this->_script._step[si];
}
void Interpreter::Interpret()
{
	//�սᲽ��������ѭ��
	do
	{
		//��ִ��Speak
		cur_step.executeSpeak();
		//������������н鲽��,�����ѭ��,�Ͽ�ͨ��
		if (cur_step.if_terminate())
		{
			break;
		}
		//ִ��listen
		string str = cur_step.executeListen();


	} while (true);
}