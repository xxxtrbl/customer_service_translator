#include"Interpreter.h"

extern string name;
extern double money;

Interpreter::Interpreter()
{
	StepId id;

	//parser����ִ�л����������﷨������_script��
	this->_parser.Parse();
	this->_script = this->_parser.getScript();

	//����ǰStep��ΪentryStep
	id =this->_script.getEntry();
	this->cur_step = this->_script._step[id];
}
void Interpreter::Interpret()
{
	//��entryStep��ʼ��ִ�У������սᲽ��������ѭ��
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
			//�û���Ӧ��cur_step��ת��silence step
			cur_step = _script._step[cur_step.get_silence_id()];
			continue;
		}
		else if (str == "@tag")
		{
			//@tagΪRobotֻ��ȡ�û��������������Ӧ��Ӧ���������ʱ�Զ�����default_step��
			cur_step = _script._step[cur_step.get_default_id()];
		}
		else
		{
			//�����û��������ҵ�RobotӦ����ת�ĵط�
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

//�����û��ļ�
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