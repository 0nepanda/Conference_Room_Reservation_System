#pragma once
#include <iostream>
using namespace std;
#include "02identity.h"
#include <string>
#include <vector>

//教师子类设计
class Teacher : public Identity
{
public:
    //默认构造
    Teacher();

    //有参构造
    Teacher(int empid, string name, string pwd);

    //查看所有预约
    void showAllOrder();

    //操作界面
    virtual void operMenu();

    //审核预约
    void validOrder();
    
    //属性： 职工号
    int m_EmpId;
};