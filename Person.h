#pragma once
#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
	Person() {}
	Person(string Name, string Gender, int Age, string ID)
	{	
		m_Name = Name;
		m_Gender = Gender;
		m_Age = Age;
		m_ID = ID;
	}
	string m_Name;
	string m_Gender;
	int m_Age = -1;
	string m_ID;
	virtual void Create() = 0; // 纯虚函数
	virtual void Display()=0; // 纯虚函数
	virtual Person* GetClassName() {
		return this;
	}
	virtual int ScoreGetter() = 0;
	virtual string MajorGetter() = 0;
	virtual string StudentNumberGetter() = 0;
	virtual int SalaryGetter() = 0;
	virtual string PositionGetter() = 0;

};

class Undergraduate : public Person
{
public:
	Undergraduate() {}  //默认构造函数
	Undergraduate(string Name, string Gender, int Age, string ID,int Score):Person(Name,Gender,Age,ID),m_Score(Score){}
	Undergraduate(const Person&p) {
		this->m_Name = p.m_Name;
		this->m_Age = p.m_Age;
		this->m_Gender = p.m_Gender;
		this->m_ID = p.m_ID;
	}

	void Create()
	{
		cout << "请输入姓名:" << endl;
		cin >> m_Name;
		cout << "请输入性别，男或女:" << endl;
		cin >> m_Gender;
		cout << "请输入年龄:" << endl;
		cin >> m_Age;
		cout << "请输入身份证号:" << endl;
		cin >> m_ID;
		cout << "高考成绩:" << endl;
		cin >> m_Score;
	}
	void Display()
	{
		cout << "姓名: " << m_Name << " 身份:本科生 " << " 性别: " << m_Gender << " 年龄: " << m_Age << " 身份证号: " << m_ID << " 高考成绩: " << m_Score << endl;
	}
	Undergraduate* GetClassName() {
		return this;
	}
	int ScoreGetter() {
		return this->m_Score;
	}
	string MajorGetter() { return " ";}
	string StudentNumberGetter() { return " "; }
	int SalaryGetter() { return 0; }
	string PositionGetter() { return " "; }
	int m_Score;
};

class FullTimePostgraduate : public Person
{
public:
	FullTimePostgraduate() {}  //默认构造函数
	FullTimePostgraduate(string Name, string Gender, int Age, string ID, string Major) :Person(Name, Gender, Age, ID), m_Major(Major) {}
	FullTimePostgraduate(const Person&p) {
		this->m_Name = p.m_Name;
		this->m_Age = p.m_Age;
		this->m_Gender = p.m_Gender;
		this->m_ID = p.m_ID;
	}
	void Create()
	{
		cout << "请输入姓名:" << endl;
		cin >> m_Name;
		cout << "请输入性别，男或女:" << endl;
		cin >> m_Gender;
		cout << "请输入年龄:" << endl;
		cin >> m_Age;
		cout << "请输入身份证号:" << endl;
		cin >> m_ID;
		cout << "请输入专业:" << endl;
		cin >> m_Major;
	}

	void Display()
	{
		cout << "姓名: " << m_Name << " 身份:脱产研究生 " << " 性别: " << m_Gender << " 年龄: " << m_Age << " 身份证号: " << m_ID << " 专业: " << m_Major << endl;
	}
	FullTimePostgraduate* GetClassName() {
		return this;
	}
	string MajorGetter() {
		return m_Major;
	}
	int ScoreGetter() { return 0; }
	string StudentNumberGetter() { return " "; }
	int SalaryGetter() { return 0; }
	string PositionGetter() { return " "; }

	string m_Major;
};

class OnJobPostgraduate : public Person
{
public:
	OnJobPostgraduate() {}  //默认构造函数
	OnJobPostgraduate(string Name, string Gender, int Age, string ID, string StudentNumber,string Major,int Salary)\
		:Person(Name, Gender, Age, ID), m_Major(Major),m_Salary(Salary) {}
	OnJobPostgraduate(const Person&p) {
		this->m_Name = p.m_Name;
		this->m_Age = p.m_Age;
		this->m_Gender = p.m_Gender;
		this->m_ID = p.m_ID;
	}
	void Create()
	{
		cout << "请输入姓名:" << endl;
		cin >> m_Name;
		cout << "请输入性别，男或女:" << endl;
		cin >> m_Gender;
		cout << "请输入年龄:" << endl;
		cin >> m_Age;
		cout << "请输入身份证号:" << endl;
		cin >> m_ID;
		cout << "请输入学号:" << endl;
		cin >> m_StudentNumber;
		cout << "请输入专业:" << endl;
		cin >> m_Major;
		cout << "请输入薪资:" << endl;
		cin >> m_Salary;
	}

	void Display()
	{
		cout << "姓名: " << m_Name << " 身份:在职研究生 " << " 性别: " << m_Gender << " 年龄: " << m_Age << " 身份证号: " << m_ID << " 学号: "\
			<< m_StudentNumber << " 专业: " << m_Major << " 工资： " << m_Salary << endl;
	}
	OnJobPostgraduate* GetClassName() {
		return this;
	}

	string StudentNumberGetter() {
		return this->m_StudentNumber;
	}
	string MajorGetter() {
		return this->m_Major;
	}
	int SalaryGetter() {
		return this->m_Salary;
	}
	int ScoreGetter() { return 0; }
	string PositionGetter() { return " "; }

	string m_StudentNumber;
	string m_Major;
	int m_Salary;
};

class Worker : public Person
{
public:
	Worker() {}  //默认构造函数
	Worker(string Name, string Gender, int Age, string ID,int Salary,string Position)\
		: Person(Name, Gender, Age, ID), m_Salary(Salary),m_Position(Position) {}
	Worker(const Person&p) {
		this->m_Name = p.m_Name;
		this->m_Age = p.m_Age;
		this->m_Gender = p.m_Gender;
		this->m_ID = p.m_ID;
	}
	void Create()
	{
		cout << "请输入姓名:" << endl;
		cin >> m_Name;
		cout << "请输入性别，男或女:" << endl;
		cin >> m_Gender;
		cout << "请输入年龄:" << endl;
		cin >> m_Age;
		cout << "请输入身份证号:" << endl;
		cin >> m_ID;
		cout << "请输入薪资:" << endl;
		cin >> m_Salary;
		cout << "请输入岗位:" << endl;
		cin >> m_Position;
	}
	void Display()
	{
		cout << "姓名: " << m_Name <<" 身份:职工 "<< " 性别: " << m_Gender << " 年龄: " << m_Age << " 身份证号: " << m_ID << " 薪资: "\
			<< m_Salary << " 岗位: " << m_Position << endl;
	}
	Worker* GetClassName() {
		return this;
	}
	int SalaryGetter() {
		return this->m_Salary;
	}
	string PositionGetter() {
		return this->m_Position;
	}
	int ScoreGetter() { return 0; }
	string MajorGetter() { return " "; }
	string StudentNumberGetter() { return " "; }

	int m_Salary;
	string m_Position;
};

class Teacher : public Person
{
public:
	Teacher() {}  //默认构造函数
	Teacher(string Name, string Gender, int Age, string ID, int Salary, string Major)\
		: Person(Name, Gender, Age, ID), m_Salary(Salary), m_Major(Major) {}
	Teacher(const Person&p) {
		this->m_Name = p.m_Name;
		this->m_Age = p.m_Age;
		this->m_Gender = p.m_Gender;
		this->m_ID = p.m_ID;
	}
	void Create()
	{
		cout << "请输入姓名:" << endl;
		cin >> m_Name;
		cout << "请输入性别，男或女:" << endl;
		cin >> m_Gender;
		cout << "请输入年龄:" << endl;
		cin >> m_Age;
		cout << "请输入身份证号:" << endl;
		cin >> m_ID;
		cout << "请输入薪资:" << endl;
		cin >> m_Salary;
		cout << "请输入专业:" << endl;
		cin >> m_Major;
	}
	void Display()
	{
		cout << "姓名: " << m_Name << " 身份:教师 " << " 性别: " << m_Gender << " 年龄: " << m_Age << " 身份证号: " << m_ID << " 薪资: "\
			<< m_Salary << " 专业: " << m_Major << endl;
	}
	Teacher* GetClassName() {
		return this;
	}
	int SalaryGetter() {
		return m_Salary;
	}
	string MajorGetter() {
		return m_Major;
	}
	int ScoreGetter() { return 0; }
	string StudentNumberGetter() { return " "; }
	string PositionGetter() { return " "; }

	int m_Salary;
	string m_Major;
};

