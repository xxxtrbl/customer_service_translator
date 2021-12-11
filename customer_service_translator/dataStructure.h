#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<sstream>
#include<fstream>
using namespace std;

//The interval of listening time.
struct interval {
	int beginTimer;
	int endTimer;
}typedef Listen;
//Store the item ROBOT would say.
struct item {
	string out;
	Varname var;
}typedef Item;

typedef string Varname;
typedef string StepId;
typedef string Answer;
typedef list<Item> Expression;
typedef string Token;