#include "08orderFile.h"

// 将find(：)封装成函数
void OredrFile::findKey(string kind)
{
    string key;
    string value;
    // this->m.clear();
    // map<string, string> m;

    int pos = kind.find(":");
    if (pos != -1)
    {
        key = kind.substr(0, pos);  //前面读了（pos-1-0）+1个数
        value = kind.substr(pos+1, kind.size() -1 - pos);  //后面剩下size()-1个减pos

        // cout << "key = " << key << endl;
        // cout << "value = " << value << endl;

        this->m.insert(make_pair(key, value));
    }
}

//构造函数
OredrFile::OredrFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    // string date;
    // string interval;
    // string stuId;
    // string stuName;
    // string roomId;
    // string status;

    this->m_Size = 0;  //记录条数

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs 
            >> stuName && ifs >> roomId && ifs >> status)
    {
        // cout << date << endl;
        // cout << interval << endl;
        // cout << "  -----" << endl;
        // cout << stuId << endl;
        // cout << stuName << endl;
        // cout << roomId << endl;
        // cout << status << endl;
        // cout << endl;

        // date : 1
        // string key;
        // string value;
        // map<string, string> m;

        // int pos = date.find(":");
        // if (pos != -1)
        // {
        //     key = date.substr(0, pos);  //前面读了（pos-1-0）+1个数
        //     value = date.substr(pos+1, date.size() -1 - pos);  //后面剩下size()-1个减pos

        //     // cout << "key = " << key << endl;
        //     // cout << "value = " << value << endl;

        //     m.insert(make_pair(key, value));
        // }
        // 截取日期
        findKey(this->date);
        // 截取时间段
        findKey(this->interval);
        // 截取学号
        findKey(this->stuId);
        // 截取姓名
        findKey(this->stuName);
        // 截取机房号
        findKey(this->roomId);
        // 截取状态
        findKey(this->status);

        // 将小容器放到大的容器中
        this->m_orderData.insert(make_pair(this->m_Size,this->m));
        this->m_Size++;
        this->m.clear();
    }
    ifs.close();

    // 测试最大容器
    // for (map<int, map<string, string>>::iterator it = this->m_orderData.begin(); it != this->m_orderData.end(); it++)
    // {
    //     cout << "条数为：  " << it->first << "   value = " << endl;
    //     for (map<string, string>::iterator vIt = (*it).second.begin(); vIt != (*it).second.end(); vIt++)
    //     {
    //         cout << "(key =  " << vIt->first << "   value =  " << vIt->second << ")" << endl;
    //     }
    //     cout << endl;
    // }
    
}

//更新预约记录
void OredrFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        /* 0条信息直接写 */
        return;
    }
    else
    {
        ofstream ofs;
        ofs.open(ORDER_FILE, ios::out | ios::trunc);
        for (int i = 0; i < this->m_Size; i++)
        {
            ofs << "date:" << this->m_orderData[i]["date"] << " ";
            ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
            ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
            ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
            ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
            ofs << "status:" << this->m_orderData[i]["status"] << endl;
        }
        
        ofs.close();
    }
}
