#include"Interpreter.h"

extern string name;
extern double money;
extern string test_out ;
extern ofstream test_stream;

//��ȡ�ű��﷨��,��cur_step����Ϊentry_step
Interpreter::Interpreter()
{
	StepId id;

	//parser����ִ�л����������﷨������_script��
	this->_parser.Parse();
	this->_script = this->_parser.getScript();

	//����ǰStep��ΪentryStep
	id =this->_script.getEntry();
	this->cur_step = this->_script._step[id];

	this->make_test_script();
	test_stream.open(test_out, ios::app);
}

//���з���
void Interpreter::Interpret()
{
	Step welcome_step = this->cur_step;
	int flag = 1;

	//��entryStep��ʼ��ִ�У������սᲽ��������ѭ��
	do
	{
		//��¼cur_step��id
		StepId id = cur_step.getStepid();
		
		//��ִ��Speak
		cur_step.executeSpeak();

		if (flag == 0)
		{
			break;
		}

		//������������սᲽ��,�����ѭ��,�Ͽ�ͨ��
		if (cur_step.if_terminate())
		{
			//break;
			//system("PAUSE");
			cur_step = welcome_step;
		}

		flag = this->answer_API();
		
		

		//������������սᲽ��,�����ѭ��,�Ͽ�ͨ��
		if (cur_step.if_terminate())
		{
			//break;
			//system("PAUSE");
			cur_step = welcome_step;
		}
		//�ж�step�Ƿ��иı�,���û��������default step��
		if (id == cur_step.getStepid())
		{
			cur_step = _script._step[ cur_step.get_default_id()];
		}
	} while (true);

}

//Ӧ��ӿ�
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
		cout<< "���Խ���..." << endl;
		return 0;
	}

	//ִ��listen
	string str = cur_step.executeListen(answer_str);
	if (str == "")
	{
		//�û���Ӧ��cur_step��ת��silence step
		cur_step = _script._step[cur_step.get_silence_id()];
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
	}
	return 1;
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

	test_stream.close();
}

//����׮�����ݲ�ͬ��cur_step�����в���
void Interpreter::testCur_step()
{
	for (auto it = this->_script._step.begin(); it != this->_script._step.end(); it++)
	{
		this->cur_step = it->second;
		this->Interpret();
	}
}

//�������Խű��ļ�
void Interpreter::make_test_script()
{
	ifstream file;
	file.open("test.txt", ios::in);
	string strLine;

	//���ж�ȡ�ű��ļ�,�ÿո�ָ�,����test_script��
	while (getline(file, strLine))
	{
		if (strLine.empty())
			continue;

		test_script.push_back(strLine);
	}
	file.close();
}