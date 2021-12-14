#pragma once
#include"dataStructure.h"
#include"step.h"

class Script {
private:
	StepId _entry;
	list<Varname> _vars;

public:
	map<StepId, Step> _step;

	//初始化变量
	Script();
	//创建一个Step
	Step processStep(StepId& id);
	//添加_step
	void addStep(StepId& id,Step& the_step);
	//设置entry step
	void setEntry(StepId& id);
	//获取entry step
	StepId getEntry();
	//添加_vars();
	void addVars(Varname name);

};