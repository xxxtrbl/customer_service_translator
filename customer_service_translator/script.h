#pragma once
#include"dataStructure.h"
#include"step.h"

class Script {
private:
	StepId _entry;
	list<Varname> _vars;

public:
	map<StepId, Step> _step;

	//��ʼ������
	Script();
	//����һ��Step
	Step processStep(StepId& id);
	//���_step
	void addStep(StepId& id,Step& the_step);
	//����entry step
	void setEntry(StepId& id);
	//��ȡentry step
	StepId getEntry();
	//���_vars();
	void addVars(Varname name);

};