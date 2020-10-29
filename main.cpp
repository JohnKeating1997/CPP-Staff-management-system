#include<iostream>
#include<string>
#include "Interface.h"
#include "Person.h"
#include "HeterList.h"

using namespace std;

void my_preset(HeterList<Person> &thelist)  //预设几个人
{
	Undergraduate* p1=new Undergraduate("Tom", "男", 20, "1", 542);
	thelist.Insert(p1);
	FullTimePostgraduate* p2=new FullTimePostgraduate("Jessy", "女", 23, "2", "计算机");
	thelist.Insert(p2);
	OnJobPostgraduate* p3=new OnJobPostgraduate("小飞侠", "女", 23, "3", "1321","土木工程",2000);
	thelist.Insert(p3);
	Worker* p4=new Worker("赵三", "男", 45, "4", 20000, "一把手");
	thelist.Insert(p4);
	Teacher* p5=new Teacher("李四", "男", 50, "5", 30000, "计算机");
	thelist.Insert(p5);
}
int main()
{
	//实例化管理者对象
	WorkerManager wm;
	int choice = 0;
	HeterList<Person> myList;
	my_preset(myList); //预设几个人
	string identity[] = { "本科生","脱产研究生","在职研究生","职工","教师" };
	string info[] = { "姓名","性别","年龄","身份证号" };
	//展示菜单
	wm.Show_Menu();
	while (true) 
	{
		cout << "请键入你的选择:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:  //新增职工信息
		{
			cout << "请输入要新增的人员类别：" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << i + 1 << identity[i] << endl;
			}
			int category = 0;
			cin >> category;
			Person* person = NULL;
			switch (category)
			{
			case 1:
				person = new Undergraduate;
				person->Create();
				myList.Insert(person);
				
				break;
			case 2:
				person = new FullTimePostgraduate;
				person->Create();
				myList.Insert(person);
				
				break;
			case 3:
				person = new OnJobPostgraduate;
				person->Create();
				myList.Insert(person);
				break;
			case 4:
				person = new Worker;
				person->Create();
				myList.Insert(person);
				break;
			case 5:
				person = new Teacher;
				person->Create();
				myList.Insert(person);
				break;
			default:
				break;
		}
	break; }

		case 2:  //删除离职职工
		{
			string ID;
			cout << "请输入需要删除的员工的身份证号码： " << endl;
			cin >> ID;
			myList.Delete(ID);
			break; 
		}

		case 3:  //查询职工信息
		{
			
			cout << "请输入需要按照何种信息进行查找： " << endl;
			for (int i = 0; i < 4; i++)
			{
				cout << i + 1 << info[i] << endl;
			}
			int axis;
			cin >> axis;
			string info;
			cout << "请输入查找的信息： " << endl;
			cin >> info;
			myList.Search(axis, info);

		}
			break;
		case 4:  //打印职工信息
			myList.Print();
			break;
		case 5:  //清空管理系统
			myList.Truncate();
			break;
		case 6:  //退出系统
			wm.exitSystem();
			break;
		case 7:
			myList.Save_file();
			break;
		case 8:
			myList.Load_file();
			break;
		default:
	/*		system("cls");*/
			break;
		}

		system("pause");

	}


	return 0;
}