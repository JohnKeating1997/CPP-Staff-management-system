#pragma once
#include<iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

template <typename T>class HeterList;

template <typename T>
class Node
{
	friend class HeterList<T>;
public:
	Node(T *data) :m_data(data), m_next(NULL) {}
private:
	T *m_data;
	Node<T> *m_next;
};

template <typename T>
class HeterList
{
public:
	HeterList() :m_head(NULL), m_tail(NULL) {}
	Node<T>* Search(int axis,string info);
	void Insert(T *newNode);
	void Delete(string ID);  //按照身份证进行查找
	void Print();
	void Truncate();
	void Save_file();
	void Load_file();
private:
	int m_length;
	Node<T> *m_head;
	Node<T> *m_tail;
};


template <typename T>
void HeterList<T>::Insert(T *newNode)
{
	Node<T> *tmp = new Node<T>(newNode);
	if (!m_head)
	{
		m_head = m_tail = tmp;
		m_length++;
	}
	else
	{
		m_tail->m_next = tmp;
		m_tail = tmp;
		m_length++;
	}
}

template <typename T>
Node<T>* HeterList<T>::Search(int axis, string info)
{
	if (!m_head)
	{
		cout << "链表为空..." << endl;
		return NULL;
	}
	Node<T>* tmp = NULL;
	switch (axis)
	{
	case 1:  // 按照姓名查找
		cout << "查找结果如下:" << endl;
		for (tmp = m_head; tmp; tmp = tmp->m_next)
		{
			if (tmp->m_data->m_Name == info) { tmp->m_data->Display();}
		}
		return tmp; // 后面的删除不会用到按照姓名查找，因此这里直接返回tmp以满足函数返回类型要求，没有实际意义。

	case 2:  // 按照性别查找
		cout << "查找结果如下:" << endl;
		for (tmp = m_head; tmp; tmp = tmp->m_next)
		{
			if (tmp->m_data->m_Gender == info) { tmp->m_data->Display(); }
		}
		return tmp; // 后面的删除不会用到按照性别查找，因此这里直接返回tmp以满足函数返回类型要求，没有实际意义。

	case 3:  // 按照年龄查找
	{
		cout << "查找结果如下:" << endl;
		int age = atoi(info.c_str());  //string型转成int型
		for (tmp = m_head; tmp; tmp = tmp->m_next)
		{
			if (tmp->m_data->m_Age == age) { tmp->m_data->Display(); }
		}
		return tmp; // 后面的删除不会用到按照年龄查找，因此这里直接返回tmp以满足函数返回类型要求，没有实际意义。
	}
	case 4:  // 按照身份证号查找
		cout << "查找结果如下:" << endl;
		for (tmp = m_head; tmp; tmp = tmp->m_next)
		{
			if (tmp->m_data->m_ID == info) { tmp->m_data->Display(); return tmp; }  // 身份证不会重复，只要查找到即可退出函数
		}
	default:
		return NULL;
	}


}

template <typename T>
void HeterList<T>::Delete(string ID)
{
	Node<T>* search = this->Search(4, ID);
	Node<T>*cur = NULL;
	Node<T>*pre = NULL;


	for (cur = m_head; cur; cur = cur->m_next)
	{
		if(cur==search)
		{
			if (pre == NULL) //如果删除的是头节点
			{
				m_head = m_head->m_next;
				delete cur;
				cur = NULL;
				break;

			}
			else
			{
				pre->m_next = cur->m_next;
				delete cur;
				cur = NULL;   // 非常关键，delete之后cur成了野指针(0x8123)，所以这时候应该给cur指定NULL或其他指针
				break;
			}
		}
		pre = cur;
	}
}

template <typename T>
void HeterList<T>::Print()
{
	if (!m_head)
	{
		cout << "链表为空..." << endl;
		return;
	}
	Node<T> *tmp;
	for (tmp = m_head; tmp; tmp = tmp->m_next)
	{
		tmp->m_data->Display();
		cout << endl;
	}
}

template <typename T>
void HeterList<T> ::Truncate()
{
	cout << "删除后不可恢复，您确定要继续吗？[Y/N]";
	char choice;
	cin >> choice;
	if (choice != 'Y'){return;}
	else
	{
		cout << "开始清空" << endl;
		Node<T>* cur = NULL;
		Node<T>* tmp = NULL;
		if (!m_head)
		{
			cout << "已经是空链表了！" << endl;
			return;
		}
		if (m_length == 1)
		{
			delete m_head;
			m_head =m_tail= NULL;
			cout << "清空成功" << endl;
			return;
		}
		cur = m_head;
		while (cur)
		{
			tmp = cur->m_next;
			delete cur;
			cur = tmp;
		}
		m_head = m_tail = NULL;
		cout << "清空成功" << endl;
		return;
	}
}

template <typename T> 
void HeterList<T> ::Save_file(){

	Node<T>* cur = this->m_head;
	if (!cur) return;

	ofstream ofs_Undergraduate;
	ofstream ofs_FullTimePostgraduate;
	ofstream ofs_OnJobPostgraduate;
	ofstream ofs_Worker;
	ofstream ofs_Teacher;

	ofs_Undergraduate.open("Undergraduate.txt", ios::out, ios::binary);
	ofs_FullTimePostgraduate.open("FullTimePostgraduate.txt", ios::out, ios::binary);
	ofs_OnJobPostgraduate.open("OnJobPostgraduate.txt", ios::out, ios::binary);
	ofs_Worker.open("Worker.txt", ios::out, ios::binary);
	ofs_Teacher.open("Teacher.txt", ios::out, ios::binary);

	
	while (cur) {
		if (typeid(*(cur->m_data->GetClassName())) == typeid(Undergraduate)) {
			int score = cur->m_data->ScoreGetter();
			Undergraduate tmp(*(cur->m_data));
			tmp.m_Score = score;
			ofs_Undergraduate.write(((const char*)&tmp), sizeof(tmp));
		}
		if (typeid(*(cur->m_data->GetClassName())) == typeid(FullTimePostgraduate)) {
			string major = cur->m_data->MajorGetter();
			FullTimePostgraduate tmp(*(cur->m_data));
			tmp.m_Major = major;
			ofs_FullTimePostgraduate.write(((const char*)&tmp), sizeof(tmp));
		}
		if (typeid(*(cur->m_data->GetClassName())) == typeid(OnJobPostgraduate)) {
			string studentNumber = cur->m_data->StudentNumberGetter();
			string major = cur->m_data->MajorGetter();
			int salary = cur->m_data->SalaryGetter();

			OnJobPostgraduate tmp(*(cur->m_data));
			tmp.m_StudentNumber = studentNumber;
			tmp.m_Major = major;
			tmp.m_Salary = salary;
			ofs_OnJobPostgraduate.write(((const char*)&tmp), sizeof(tmp));
		}
		if (typeid(*(cur->m_data->GetClassName())) == typeid(Worker)) {
			string position = cur->m_data->PositionGetter();
			int salary = cur->m_data->SalaryGetter();
			Worker tmp(*(cur->m_data));
			tmp.m_Position = position;
			tmp.m_Salary = salary;
			ofs_Worker.write(((const char*)&tmp), sizeof(tmp));
		}
		if (typeid(*(cur->m_data->GetClassName())) == typeid(Teacher)) {
			string major = cur->m_data->MajorGetter();
			int salary = cur->m_data->SalaryGetter();
			Teacher tmp(*(cur->m_data));
			tmp.m_Major = major;
			tmp.m_Salary = salary;
			ofs_Teacher.write(((const char*)&tmp), sizeof(tmp));
		}

		cur = cur->m_next;
	}
	ofs_Undergraduate.close();
	ofs_FullTimePostgraduate.close();
	ofs_OnJobPostgraduate.close();
	ofs_Worker.close();
	ofs_Teacher.close();
}

template <typename T>
void HeterList<T> ::Load_file() {
	ifstream ifs_Undergraduate;
	ifstream ifs_FullTimePostgraduate;
	ifstream ifs_OnJobPostgraduate;
	ifstream ifs_Worker;
	ifstream ifs_Teacher;

	ifs_Undergraduate.open("Undergraduate.txt", ios::in, ios::binary);
	ifs_FullTimePostgraduate.open("FullTimePostgraduate.txt", ios::in, ios::binary);
	ifs_OnJobPostgraduate.open("OnJobPostgraduate.txt", ios::in, ios::binary);
	ifs_Worker.open("Worker.txt", ios::in, ios::binary);
	ifs_Teacher.open("Teacher.txt", ios::in, ios::binary);

	while (!ifs_Undergraduate.eof()) {
		Undergraduate* tmp = new Undergraduate;
		ifs_Undergraduate.read(((char*)tmp), sizeof(*tmp));
		Undergraduate* write = new Undergraduate(*tmp);
		if (write->m_Age != -1) {
			this->Insert(write);
		}
	}
	while (!ifs_FullTimePostgraduate.eof()) {
		FullTimePostgraduate* tmp = new FullTimePostgraduate;
		ifs_FullTimePostgraduate.read((char*)tmp, sizeof(*tmp));
		FullTimePostgraduate* write = new FullTimePostgraduate(*tmp);
		if (write->m_Age != -1) {
			this->Insert(write);
		}
	}
	while (!ifs_OnJobPostgraduate.eof()) {
		OnJobPostgraduate* tmp = new OnJobPostgraduate;
		ifs_OnJobPostgraduate.read((char*)tmp, sizeof(*tmp));
		OnJobPostgraduate* write = new OnJobPostgraduate(*tmp);
		if (write->m_Age != -1) {
			this->Insert(write);
		}
	}
	while (!ifs_Worker.eof()) {
		Worker* tmp = new Worker;
		ifs_Worker.read((char*)tmp, sizeof(*tmp));
		Worker* write = new Worker(*tmp);
		if (write->m_Age != -1) {
			this->Insert(write);
		}
	}
	while (!ifs_Teacher.eof()) {
		Teacher* tmp = new Teacher;
		ifs_Teacher.read((char*)tmp, sizeof(*tmp));
		Teacher* write = new Teacher(*tmp);
		if (write->m_Age != -1) {
			this->Insert(write);
		}
	}

	ifs_Undergraduate.close();
	ifs_FullTimePostgraduate.close();
	ifs_OnJobPostgraduate.close();
	ifs_Worker.close();
	ifs_Teacher.close();
}

