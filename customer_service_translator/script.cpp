#include"script.h"

Script::Script()
{
	this->_entry = "";
}
Step Script::processStep(StepId& id)
{
	Step _step;
	_step.initialStepid(id);
	return _step;
}
void Script::addStep(StepId& id,Step& the_step)
{
	this->_step.emplace(id, the_step);
}
void Script::setEntry(StepId& id)
{
	this->_entry = id;
}
void Script::addVars(Varname name)
{
	this->_vars.push_back(name);
}
StepId Script::getEntry()
{
	return this->_entry;
}