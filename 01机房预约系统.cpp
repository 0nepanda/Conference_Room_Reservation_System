#include <iostream>
#include <string>
using namespace std;
#include "02identity.h"
#include <fstream>
#include "06gloableFile.h"
#include "03student.h"
#include "04teacher.h"
#include "05manager.h"


//进入管理员子菜单界面
void managerMenu(Identity * &manager)  //Identity * 用父类指针传入
{
    while (true)
    {
        //调用管理员子菜单
        manager->operMenu(); //实际上这是多态，即父类指针创建子类对象，然后调用共同接口  operMenu()是重写的纯虚函数 manager是父类指针智能调用公共重写的内容

        //将父类指针 转为子类指针， 调用子类里其他接口
        Manager * man = (Manager*)manager;  //(Manager*)强转


        int select;

        cin >> select;

        if (select ==1)
        {
            /* 添加账号 */
            man->addPerson();
        }
        else if (select == 2)
        {
            /* 查看账号 */
            man->showPerson();
        }
        else if (select == 3)
        {
            /* 查看会议室 */
            man->showConfference();
        }
        else if (select == 4)
        {
            /* 清空预约 */
            man->cleanFile();
        }
        else
        {
            // 注销
            delete manager;  //销毁掉堆区数据
            cout << "注销成功" << endl;
            // return;
        }
        
    }
    
}

//进入 学生子类 菜单界面
void studentMenu(Identity * &student)
{
    while(true)
    {
        //调用学生子菜单
        student->operMenu();

        //强转称子类指针，调用其他子类接口
        Student * stu = (Student*) student;

        //选择功能
        int select = 0;
        cin >> select;

        if (select == 1)
        {
            /* 申请预约 */
            stu->applyOrder();
        }
        else if (select == 2)
        {
            /* 查看自身预约 */
            stu->showMyOrder();
        }
        else if (select == 3)
        {
            /* 查看所有人预约 */
            stu->showAllOrder();
        }
        else if (select == 4)
        {
            /* 撤销预约 */
            stu->cancelOrder();  //结构或对象调用时用., 指针用->
        }
        else
        {
            //注销登录
            delete student;  //将传进来的删掉
            cout << "注销成功" << endl;
            return;

        }
        
    }
}

void teacherMenu(Identity * &teacher)
{
    while (true)  //注销出去
    {
        // 父类指针调用公共接口
        teacher->operMenu();

        // 强装父类指针
        Teacher* tea = (Teacher*) teacher;
        
        int select;
        cin >> select;

        if (select == 1)
        {
            // 查看所有预约
            tea->showAllOrder();
        }
        else if (select == 2)
        {
            // 审核预约
            tea->validOrder();
        }
        else
        {
            delete teacher;
            cout << "注销成功" << endl;
            return;
        }
    }
    
}

//登录功能
void LoginIN(string fileName, int type)  //1操作文件名  2操作身份类型
{
    //创建父类指针,等会指向子类对象
    Identity *person = NULL;

    //读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);

    //判断文件是否存在
    if (!ifs.is_open())
    {
        /* 不存在 */
        cout << " 文件不存在 " << endl;
        ifs.close();
        return;
    }
    
    //准备接收用户信息
    int id = 0;
    string name;
    string pwd;

    //判断身份
    if (type == 1)
    {
        /* 学生 */
        cout << "请输入您的学号：  " << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        /* 老师 */
        cout << "请输入您的职工号：  " << endl;
        cin >> id;
    }
    
    cout << "请输入用户名：  " << endl;
    cin >> name;

    cout << "请输入密码：  " << endl;
    cin >> pwd;

    if (type == 1)
    {
        /* 学生身份验证 */
        int fId;  //从文件中获取的id号
        string fName; //从文件中获取的姓名
        string fpwd;  //从文件获取的密码

        while (ifs >> fId && ifs >> fName && ifs >> fpwd)   //碰到空格读取结束一次
        {
            //与用户输入信息做对比
            if (fId == id && fName == name && fpwd == pwd)
            {
                cout << "学生登录验证成功！" << endl;
                person = new Student(id, name, pwd);

                //进入学生身份的子菜单
                studentMenu(person);

                return;
            }
            
        }
        

    }
    else if (type == 2)
    {
        /* 教师身份验证 */
        int fId;
        string fName;  //从文件中提取信息  准备对比
        string fpwd;

        while (ifs >> fId && ifs >> fName && ifs >> fpwd)
        {
            if (fId == id && fName == name && fpwd == pwd)
            {
                cout << "教师身份验证成功！" << endl;
                person = new Teacher(id, name, pwd);

                // 进入教师身份的子菜单
                teacherMenu(person);

                return;
            }
            
        }
        

    }
    else if (type == 3)
    {
        /* 管理员身份验证 */
        string fName;
        string fpwd;

        while (ifs >> fName && ifs >> fpwd)
        {
            if (fName == name && fpwd == pwd)
            {
                cout << "管理员身份登录成功！" << endl;
                person = new Manager(name, pwd);

                // 进入管理员的子菜单界面
                managerMenu(person);

                return;
            }
            
        }
        
    }

    cout << "验证登陆失败! " << endl;
    return;

}

int main() {
    int select = 0;       //用于接收用户的选择

    while (true)
    {
        cout << "=====================欢迎来到南邮会议室预约系统======================" << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t------------------------------------------- \n";
        cout << "\t\t |                                          |\n";
        cout << "\t\t |                  1. 学生代表             |\n";
        cout << "\t\t |                                          |\n";
        cout << "\t\t |                  2.老    师              | \n";
        cout << "\t\t |                                          | \n";
        cout << "\t\t |                  3.管 理 员              |\n";
        cout << "\t\t |                                          | \n";
        cout << "\t\t |                  0.退    出              | \n";
        cout << "\t\t |                                          | \n";
        cout << "\t\t------------------------------------------- \n";
        cout << "请输入您的选择： ";

        cin >> select; 

        switch (select)
        {
        case 1:
            /* 学生身份 */
            LoginIN(STUDENT_FILE, 1);
            break;
        case 2:
            /* 教师身份 */
            LoginIN(TEACHER_FILE, 2);
            break;
        case 3:
            /* 管理员身份 */
            LoginIN(ADMIN_FILE, 3);
            break;
        case 0:
            /* 退出系统 */
            break;
        default:
            cout << "输入有误， 请重新选择" << endl;
            break;
        }
    }
    

    return 0;
}
