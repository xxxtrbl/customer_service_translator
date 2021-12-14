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

//Token表示正在分析脚本的句柄
typedef string Token;

//Item表示Robot说出的自然语言和用到的变量
struct item {
	string answer;
	Varname var;
}typedef Item;

typedef list<Item> Expression;
typedef vector<string> Line;
typedef vector<Line> File;

//listen表示用来存储用户输入的变量
typedef Varname Listen;