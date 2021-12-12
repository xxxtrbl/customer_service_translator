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
		//��¼cur_step��id
		StepId id = cur_step.getStepid();

		//��ִ��Speak
		cur_step.executeSpeak();

		//������������սᲽ��,�����ѭ��,�Ͽ�ͨ��
		if (cur_step.if_terminate())
		{
			break;
		}
		//ִ��listen
		string str = cur_step.executeListen();
		if (str == "" )
		{
			//cur_step��ת��silence step��
			cur_step = _script._step[cur_step.get_silence_id()];
			continue;
		}
		else if (str == "@commit")
		{

		}
		else
		{
			//�����û��������ҵ���Ҫ��ת�ĵط�
			StepId next_id;
			next_id = cur_step.get_certain_id(str);
			if (_script._step.count(next_id) != 1)
			{
				next_id = cur_step.get_default_id();
			}
			cur_step = _script._step[next_id];
			continue;
		}
		//������������սᲽ��,�����ѭ��,�Ͽ�ͨ��
		if (cur_step.if_terminate())
		{
			break;
		}
		//�ж�step�Ƿ��иı�,���û��������default step��
		if (id == cur_step.getStepid())
		{
			cur_step = _script._step[ cur_step.get_default_id()];
		}
	} while (true);
}