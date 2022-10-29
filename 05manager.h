#pragma once
#include <iostream>
using namespace std;
#include "02identity.h"
#include <string>
#include "06gloableFile.h"
#include <fstream>
#include <vector>
#include "03student.h"
#include "04teacher.h"
#include <algorithm>
#include "07conferenceRoom.h"
//管理员类
class Manager : public Identity
{
public:
    //默认构造
    Manager();

    //有参构造
    Manager(string name, string pwd);

    //操作界面
    virtual void operMenu();  //有纯虚函数就是抽象类， 抽象类不能实例化对象。因此这里不能有 =0；virtual 可加可不加

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房消息
    void showConfference();

    //清空预约
    void cleanFile();

    //初始化容器
    void initVector();

    //检测重复
    bool cheakRepeat(int id, int type);   //参数1 学号职工号   |参数2:检测类型 教师或学生 

    //老师容器
    vector<Teacher> vTea;

    //学生容器
    vector<Student> vStu;

    //机房容器
    vector<ConfRoom> vRoom;
};