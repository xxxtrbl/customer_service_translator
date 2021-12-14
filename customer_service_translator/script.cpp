#include"script.h"

//初始化变量
Script::Script()
{
	this->_entry = "";
}

//创建一个Step
Step Script::processStep(StepId& id)
{
	Step _step;
	_step.initialStepid(id);
	return _step;
}

//添加_step
void Script::addStep(StepId& id,Step& the_step)
{
	this->_step.emplace(id, the_step);
}

//设置entry step
void Script::setEntry(StepId& id)
{
	this->_entry = id;
}

//添加_vars();
void Script::addVars(Varname name)
{
	this->_vars.push_back(name);
}

//获取entry step
StepId Script::getEntry()
{
	return this->_entry;
}
