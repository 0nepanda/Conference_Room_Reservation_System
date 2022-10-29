#include "03student.h"

//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{

    //初始化属性
    this->m_Name = name;
    this->m_ID = id;
    this->m_Pwd = pwd;

    ifstream ifs;
    ifs.open(CONFFERENCE_FILE, ios::in);

    ConfRoom com;
    while (ifs >> com.m_RoomId && ifs >> com.m_MaxNum)
    {
        //将读取到的会议室信息放到容器
        this->vCom.push_back(com);
    }
    
    ifs.close();
}

//菜单界面
void Student::operMenu() //子类继承虚父类， 重写重新实现否则不能实例化  //virtual可以不写
{
    cout << "  欢迎学生： " << this->m_Name << " 登录 " << endl;
    cout << "=====================欢迎来到南邮会议室预约系统======================" << endl;
    cout << "\t\t------------------------------------------- \n";
    cout << "\t\t |                                           |\n";
    cout << "\t\t |                  1. 申请预约              |\n";
    cout << "\t\t |                                           |\n";
    cout << "\t\t |                  2. 我的预约              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  3. 所有预约              |\n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  4. 撤销预约              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  0. 注销登录              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t------------------------------------------- \n";
    cout << "请输入您的选择： ";
}

//申请预约
void Student::applyOrder()
{
    cout << "会议室开放时间为： 周一至周五" << endl;
    cout << "请选择要预约的时间： " << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;

    int date = 0;   //接收预约日期
    int interval;   //接收预约上下午
    int room = 0;   //接收预约编号

    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        else
        {
            cout << "输入有误， 请重新输入。" << endl;
        }
    }
    
    cout << "请输入想要预约的时间段：  " << endl;
    cout << "1、    上午" << endl;
    cout << "2、    下午" << endl;

    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        else
        {
            cout << "输入有误，请重新输入！" << endl;
            cout << "1、    上午" << endl;
            cout << "2、    下午" << endl;
        }
    }
    
    cout << "请输入想要预约的会议室编号：  " << endl;
    // cout << vCom[0].m_RoomId << "号机房的容量为： " << vCom[0].m_MaxNum << endl;
    // cout << vCom[1].m_RoomId << "号机房的容量为： " << vCom[1].m_MaxNum << endl;
    // cout << vCom[2].m_RoomId << "号机房的容量为： " << vCom[2].m_MaxNum << endl;
    for (int i = 0; i < vCom.size(); i++)
    {
        cout << vCom[i].m_RoomId << "号机房的容量为： " << vCom[i].m_MaxNum << endl;
    }

    while (true)
    {
        cout << "请输入想要预约的会议室编号： " << endl;
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        else
        {
            cout << "输入有误，请重新输入！" << endl;
        }
    }

    cout << "预约成功， 审核中········" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);  //app 和 Out 好像没有什么区别

    ofs << "date:" << date << " ";
    ofs << "Interval:" << interval << " ";
    ofs << "stuId:" << this->m_ID << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;  //1审核中

    ofs.close();

}

//查看自身预约
void Student::showMyOrder()
{
    OredrFile of;

    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    // cout << of.m_Size << endl;
    // for (auto kv : of.m_orderData) {
    //     cout << kv.first << endl;
    //     for (auto kv1 : kv.second) {
    //         cout << kv1.first << " " << kv1.second << endl;
    //     }
    //     cout << endl;
    // }
    
    for (int i = 0; i < of.m_Size; i++)
    {
        // cout << "进入循环" << endl;

        /* 展示预约 */
        //实现string 转为 int
        //string利用.c_char转 const char*
        // 再利用atoi（const char*)转 int
        // cout << this->m_ID << endl;
        // cout << of.m_orderData[i]["stuId"] << endl;
        if (this->m_ID == atoi(of.m_orderData[i]["stuId"].c_str()))  //遍历找到自身预约
        {
            cout << "（预约时期：  周" << of.m_orderData[i]["date"] << "  " ;
            cout << "时间段：  " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
            cout << "会议室号：  " << of.m_orderData[i]["roomId"] << "  ";
            string status = "  状态：  ";
            // 1、审核中 2、已预约 -1预约失败 0取消预约
            if (atoi(of.m_orderData[i]["status"].c_str()) == 1)
            {
                status += "审核中····";
            }
            else if (atoi(of.m_orderData[i]["status"].c_str()) == 2)
            {
                status += "已成功预约！";
            }
            else if (atoi(of.m_orderData[i]["status"].c_str()) == -1)
            {
                status += "预约失败！审核未通过！";
            }
            else
            {
                status += "预约已取消";
            }
            cout << "预约状态： " << status << ")" << endl;
            
        }
        
    }
    
    
}

//查看所有预约
void Student::showAllOrder()
{
    OredrFile of;  //创建对象
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i+1 << "、 ";
        cout << "(预约日期： 周" << of.m_orderData[i]["date"] << "  ";
        cout << "时间段： " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
        cout << "学生学号： " << of.m_orderData[i]["stuId"] << "  ";
        cout << "学生姓名： " << of.m_orderData[i]["stuName"] << "  ";
        cout << "会议室号： " << of.m_orderData[i]["roomId"] << "  ";
        string status = "处理状态： ";
        // 1、审核中 2、已预约 -1预约失败 0取消预约
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中····)";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "已预约成功)";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "预约失败，审核未通过)";
        }
        else
        {
            status += "预约已取消)"; 
        }
        cout << status << endl;
    }
    
}

//取消预约
void Student::cancelOrder()
{
    OredrFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    
    cout << "审核中或以成功预约的会议室可被取消， 请输入要取消的记录" << endl;
    vector<int> v;  //存放在最大容器中的下标编号
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
        //先判断是自身学号
        if (this->m_ID == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            /* 再筛选状态 */
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                /* 审核中或成功预约的 */
                v.push_back( i );
                cout << index++ << "、 ";
                cout << "预约日期：  周" << of.m_orderData[i]["date"] << "  "; 
                cout << "时间段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
                cout << "会议室编号： " << of.m_orderData[i]["roomId"] << "  ";
                cout << "处理状态： " ;
                string status = "预约状态： ";
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "审核中····";
                }
                else if(of.m_orderData[i]["status"] == "2")
                {
                    status += "审核已通过";
                }
                cout << status << endl;
            }
            
        }
        
    }

    cout << "请输入要取消的记录， 0代表返回" << endl;
    int select = 0;

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
                of.m_orderData[ v[select-1] ]["status"] = "0";  //更新程序中的状态值

                of.updateOrder();   //更新文件中的状态值

                cout << "已取消预约！" << endl;
                break;
            }
        }
        
    }
    
     
}
