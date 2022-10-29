#include "05manager.h"

void studentPrint(Student &s)
{
    cout << " 学号为：  " << s.m_ID << "   姓名为：  " << s.m_Name << "   密码为：  " << s.m_Pwd << endl;   
}

class teacherPrint
{
public:
    void operator()(Teacher &t)
    {
        cout << " 职工编号为：  " << t.m_EmpId << "   姓名为：  " << t.m_Name << "   密码为：  " << t.m_Pwd << endl;   
    }
};

void comPrint(ConfRoom &com)
{
    cout << "会议室 " << com.m_RoomId << " 可容纳 " << com.m_MaxNum << "人。" << endl;
}

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;  //二阶段开发 更改密码

    // 初始化容器， 获取所有文件中老师 学生信息
    this->initVector();

    // 初始化会议室信息
    ifstream ifs;
    ifs.open(CONFFERENCE_FILE, ios::in);

    ConfRoom com;
    while (ifs >> com.m_RoomId && ifs >> com.m_MaxNum)
    {
        vRoom.push_back(com);
    }
    ifs.close();
    cout << "会议室的数量为：  " << vRoom.size() << endl;
    
}

//操作界面
void Manager::operMenu()
{
    cout << "  欢迎管理员： " << this->m_Name << " 登录 " << endl;
    cout << "=====================欢迎来到南邮会议室预约系统======================" << endl;
    cout << "\t\t------------------------------------------- \n";
    cout << "\t\t |                                           |\n";
    cout << "\t\t |                  1. 添加账号              |\n";
    cout << "\t\t |                                           |\n";
    cout << "\t\t |                  2. 查看账号              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  3. 查看机房              |\n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  4. 清空预约              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t |                  0. 注销登录              | \n";
    cout << "\t\t |                                           | \n";
    cout << "\t\t------------------------------------------- \n";
    cout << "请输入您的选择： ";
}

//添加账号
void Manager::addPerson()
{
    cout << "请输入要添加的账号类型：  " << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加老师" << endl;

    string fileName;  //要操作的文件名
    string tip;       //提示id号
    string errorTip;

    ofstream ofs;     //文件操作对象

    int select = 0;
    cin >> select;    //接受用户的选项

    if (select == 1)
    {
        /* 学生 */
        fileName = STUDENT_FILE;
        tip = "请输入学号： "; 
        errorTip = "学号重复，请输入学号： ";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工编号： ";
        errorTip = "职工编号重复， 请重新输入： ";
    }

    ofs.open(fileName, ios::out | ios::app);  //利用追加的方式些文件

    int id;
    string name;
    string pwd;

    cout << tip << endl;
    while (true)
    {
        cin >> id;
        bool ret = cheakRepeat(id, select);
        if (ret)
        {
            /* 有重复 */
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }
    
    cout << "请输入姓名：  " << endl;
    cin >> name;

    cout << "请输入密码：  " << endl;
    cin >> pwd;

    //向文件中添加数据
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功" << endl;

    ofs.close();

    // 调用初始化容器接口，从中获取文件中的数据
    this->initVector();  //因为打开程序添加的时候，是把信息添加到文件中，但是是用vector中的信息遍历，去确定重复与否
}

//查看账号
void Manager::showPerson()
{
    cout << "请选择要查看的内容： " << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有教师" << endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        /* 查看学生 */
        cout << "所有的学生信息如下： " << endl;
        for_each(this->vStu.begin(), this->vStu.end(), studentPrint);
    }
    else
    {
        // 查看教师
        cout << "所有的教师信息如下： " << endl;
        for_each(this->vTea.begin(), this->vTea.end(), teacherPrint());
    }
    
}

//查看机房消息
void Manager::showConfference()
{
    cout << "机房的信息为：  " << endl;
    for_each(this->vRoom.begin(), this->vRoom.end(), comPrint);
}

//清空预约
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功！" << endl;
    //清空判断
}

//初始化容器
void Manager::initVector()
{
    //确保容器清空状态
    vStu.clear();
    vTea.clear();

    //读取信息  教师
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);

    if (!ifs.is_open())
    {
        cout << "教师文件读取失败" << endl;
        return;
    }

    Student s;
    while (ifs >> s.m_ID, ifs >> s.m_Name, ifs >> s.m_Pwd)
    {
        vStu.push_back(s);
    }
    cout << "当前学生数量为：  " << vStu.size() << endl;
    ifs.close();


    // 2 读取学生信息
    ifs.open(TEACHER_FILE, ios::in);

    if (!ifs.is_open())
    {
        cout << "学生信息档案打开失败" << endl;
        return;
    }
    
    Teacher t;
    while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    cout << "当前教师数量为：  " << vTea.size() << endl;
    ifs.close();
    
}

//检测重复
bool Manager::cheakRepeat(int id, int type)  //参数1 学号职工号   |参数2:检测类型 教师或学生 
{
    if (type == 1)
    {
        /* 检测学生 */
        for (vector<Student>::iterator it = this->vStu.begin(); it != vStu.end(); it++)
        {
            if (id == it->m_ID)
            {
                return true;
            }          
        }
        
    }
    else
    {
        // 检测老师
        for (vector<Teacher>::iterator it = this->vTea.begin(); it != vTea.end(); it++)
        {
            if (id == it->m_EmpId)
            {
                return true;
            }          
        }
    }

    return false;
    
}