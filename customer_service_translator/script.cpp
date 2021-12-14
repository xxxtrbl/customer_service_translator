#include"script.h"

//��ʼ������
Script::Script()
{
	this->_entry = "";
}

//����һ��Step
Step Script::processStep(StepId& id)
{
	Step _step;
	_step.initialStepid(id);
	return _step;
}

//���_step
void Script::addStep(StepId& id,Step& the_step)
{
	this->_step.emplace(id, the_step);
}

//����entry step
void Script::setEntry(StepId& id)
{
	this->_entry = id;
}

//���_vars();
void Script::addVars(Varname name)
{
	this->_vars.push_back(name);
}

//��ȡentry step
StepId Script::getEntry()
{
	return this->_entry;
}
