# 简介
纪念一下人生第一个C++程序，浙江大学2020春学期《C++与数据结构》期末作业：用异质链表实现一个职工管理系统，并可以将链表以二进制文件的形式储存在本地

# 人事管理系统
用所学过的知识编写一个简单的人事管理系统，要求功能如下
用链表存储、文件输入、输出。
具有建立、插入、删除、查询和打印功能。
平台不限、链表可用公共模板类（最好自己写）。
管理的人员有：
本科生：姓名、性别、年龄、身份证号码、高考总分
脱产研究生：姓名、性别、年龄、身份证号码、专业
在职研究生：姓名、性别、年龄、身份证号码、学号、专业、工资
职工：姓名、性别、年龄、身份证号码、工资、岗位
教师：姓名、性别、年龄、身份证号码、工资、专业

## 一、作业概况简述
参考了老师提供了两篇文档：异质链表1.doc和异质链表2.doc
异质链表1.doc的思路是，先定义好Person基类和各种派生类，然后定义一个抽象的节点和链表类，这样做的好处是存储的内容（人的信息）和存储方式（链表）相互独立，便于后期维护。
异质链表2.doc则将每个Person都定义为一个节点，这样如果链表出错了或者需要变更功能，可能会影响到Person类的实现；或者如果我不想用链表了，想换个储存方式，那写在Person里的有关节点的东西就没有用处了，降低了代码的存储效率和可读性，这种情况下代码就略显冗余。
写到后面发现如果要追求链表类和Person及其派生类完全独立，就涉及到类访问权限、模板类友元、声明的问题，写起来很繁琐，所以也没有做到二者完全独立。
另外文件读写方面用到是二进制的读写，牵扯出一系列麻烦事儿，在3.6节有详细叙述。

## 二、系统概述
本系统分为四个部分：

1.Interface.h与Interface.cpp

主界面的声明与实现

2.Person.h

定义并实现了Person基类，Undergraduate本科生子类，FullTimePostgraduate脱产研究生子类，OnJobPostgraduate在职研究生子类，Worker职工子类，Teacher教师子类。

3.HeterList.h

定义并实现了基于模板的Node类和HeterList类，拥有建立（构造函数）、插入（Insert）、删除（Delete）、查询（Search）和打印（Display）功能。

4.Main.cpp

和用户交互的主程序，为了便于测试，系统设计了一个test02()函数，并默认在main()中调用，作用是给系统初始化5个人物：
 

## 三、功能概述

### 3.1 建立新表并查看默认的5个人物：

### 3.2 插入一个人物：

### 3.3 删除一个人物：

由于只有身份证不会重复，因此只提供搜寻身份证删除功能。如果需要删除叫“张三”的人，需要先搜索所有叫“张三”的人，然后决定删除哪一个，输入他的身份证号即可。

### 3.4 查找一个人物：

提供了按姓名、性别、年龄批量查找，和按身份证号精确查找

### 3.5 清空链表：
 
### 3.6 保存和读取：
这里采用二进制文件读写，直接保存Person的几个子类。

这里有个大坑：

由于二进制读写是直接读写对象，因此：

1. 保存的时候不能直接用异质链表里的节点储存的对象，因为异质链表里的是Person类型而不是子类，最终保存的对象是不含有子类独有的成员函数的；
2. 读取的时候就要确定是哪一个子类，否则无法读取。同时读取的是含有虚函数的子类，此时虚表指针无法指向虚函数表，强行调用读取后的子类的函数会引起访问权限冲突。

基于以上两点：
1. 在储存的时候，按照不同的子类分文件储存，如下：
 
2. 在储存的时候，栈区创建一个子类X，将链表上的Person类的值赋给子类X（C++默认的构造函数是不支持父类直接拷贝给子类的，因此我在每一个子类里都写了一个父类赋值给子类的构造函数），向文件中写入X。
3. 在读取的时候，为了解决虚函数表的问题，我又用拷贝构造重新new了一个新的子类，新的子类的虚函数表是没有问题的，可以接入链表中。
