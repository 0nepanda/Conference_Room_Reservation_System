#pragma once
using namespace std;
#include <iostream>


// 抽象身份基类
class Identity
{
public:
    //操作菜单--多态技术
    virtual void operMenu() = 0;  //纯虚函数

    string m_Name;   //用户名
    string m_Pwd;       //密码
};


//抽象虚基类只有.h
//   在子类中.cpp具体实现