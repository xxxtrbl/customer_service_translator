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

//Token��ʾ���ڷ����ű��ľ��
typedef string Token;

//Item��ʾRobot˵������Ȼ���Ժ��õ��ı���
struct item {
	string answer;
	Varname var;
}typedef Item;

typedef list<Item> Expression;
typedef vector<string> Line;
typedef vector<Line> File;

//listen��ʾ�����洢�û�����ı���
typedef Varname Listen;