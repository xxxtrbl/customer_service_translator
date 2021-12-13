#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<sstream>
#include<fstream>
using namespace std;

typedef string Varname;
typedef string StepId;
typedef string Answer;

typedef string Token;

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
typedef list<Item> Expression;
typedef vector<string> Line;
typedef vector<vector<string>> File;