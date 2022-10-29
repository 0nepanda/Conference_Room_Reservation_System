#include "04teacher.h"
#include "08orderFile.h"

//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empid, string name, string pwd)
{
    //初始化属性
    this->m_EmpId = empid;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//查看所有预约
void Teacher::showAllOrder()
{
    OredrFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i+1 << "、 ";
        cout << "预约日期： 周" << of.m_orderData[i]["date"] << "  ";
        cout << " 时间段：  " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
        cout << " 学号：  " << of.m_orderData[i]["stuId"] << "  ";
        cout << " 姓名： " << of.m_orderData[i]["stuName"] << "  ";
        cout << " 会议室编号： " << of.m_orderData[i]["roomId"] << "  ";
        string status = "状态： ";
        // 1、审核中 2、已预约 -1预约失败 0取消预约
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中····" ;
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "预约失败， 审核未通过";
        }
        else
        {
            status += "预约已取消";
        }
        cout << status << endl;
    }
    
}

//操作界面
void Teacher::operMenu()   //省去virtual
{
    cout << "  欢迎教师： " << this->m_Name << " 登录 " << endl;
    cout << "=====================欢迎来到南邮会议室预约系统======================" << endl;
    cout << "\t\t------------------------------------------- \n";
    cout << "\t\t |                                           |\n";
    cout << "\t\t |                  1. 所有预约              |\n";
    cout << "\t\t |                                           |\n";
    cout << "\t\t |                  2. 审核预约              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  0. 注销登录              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t------------------------------------------- \n";
    cout << "请输入您的选择： " << endl;
}

//审核预约
void Teacher::validOrder()
{
    cout << "进入审核" << endl;
    OredrFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }

    vector<int> v;
    int index = 0;
    cout << "待审核的预约记录如下： " << endl;

    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << ++index << "、  ";
            cout << "预约日期：  周" << of.m_orderData[i]["date"] << "  ";
            cout << " 时间段： " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
            cout << " 学生学号： "  <<of.m_orderData[i]["stuId"] << "  ";
            cout << "学生姓名：" << of.m_orderData[i]["stuName"] << "  ";
            cout << " 会议室编号： " << of.m_orderData[i]["roomId"] << "  ";
            cout << " 状态： 审核中····" << endl;
        }
        
    }

    cout << "请输入本次要审核的记录： " << endl;
    int select = 0;
    int ret = 0;  //接收预约结果

    while (true)
    {
        cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                cout << "请输入审核结果： " << endl;
                cout << "1、 通过" << endl;
                cout << "2、 不通过" << endl;
                cin >> ret;
                if (ret == 1)
                {
                    /* 通过 */
                    of.m_orderData[ v[select-1] ]["status"] = "2";  //v是装入显示出来的待审核编号i、的i， select-1是因为所用从0开始
                }
                else
                {
                    of.m_orderData[ v[select-1] ]["status"] = "-1";
                }
                of.updateOrder();  //更新文件
                cout << "本次审核完毕！" << endl;
                break;
            }
        }
        cout << "输入有误， 请再次输入： " << endl;
        
    }
    

}