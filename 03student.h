#pragma once
#include <iostream>
using namespace std;
#include "02identity.h"
#include <vector>
#include "07conferenceRoom.h"
#include <fstream>
#include "06gloableFile.h"
#include "08orderFile.h"

//学生类
class Student : public Identity
{
   
public:
    //默认构造
    Student();

    //有参构造
    Student(int id, string name, string pwd);

    //菜单界面
    virtual void operMenu();   //有纯虚函数就是抽象类 抽象类不能实例化

    //申请预约
    void applyOrder();

    //查看自身预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生学号
    int m_ID;

    //会议室容器
    vector<ConfRoom> vCom;
};