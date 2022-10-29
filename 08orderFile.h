#pragma once
using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include "06gloableFile.h"
#include <string>

class OredrFile
{
public:
    //构造函数
    OredrFile();

    //更新预约记录
    void updateOrder();

    //记录预约条数
    map<int, map<string,string>> m_orderData;  //记录所有预约信息的容器，key条数， value具体记录键值对信息

    //读取每条预约的信息
    map<string, string> m;

    //查找类内不同的接收信息 date、 interval
    void findKey(string kind);

    int m_Size;

    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;
};
