/*
File Name: main.cpp
Description: Where the program start
Author: unconsolable
*/
#include "loginwindow.h"

#include <QApplication>
#include <fstream>

rapidjson::Document g_jsonDocumentAccount;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 与account.json文件绑定的流
    std::fstream b_fstrmAccount("account.json", std::ios::in | std::ios::out);
    if (!b_fstrmAccount)
    {
        // 若文件打开失败报错退出
        QMessageBox::information(nullptr,"错误","账户文件打开错误");
        exit(1);
    }
    // 存储读入的文件字符串
    std::string b_strAccountInfoStr;
    // 存储一部分的字符串
    std::string t_strInput;
    while (b_fstrmAccount >> t_strInput)
    {
        // 每行读入结果连接组合
        b_strAccountInfoStr += t_strInput + ' ';
    }
    // 若解析有错误则报错退出
    if (g_jsonDocumentAccount.Parse(b_strAccountInfoStr.c_str()).HasParseError())
    {
        QMessageBox::information(nullptr, "错误", "解析账户文件错误");
        // 直接退出
        exit(1);
    }
    // 登录窗口初始化
    LoginWindow w;
    // 显示登录窗口
    w.show();
    // 进行消息循环
    return a.exec();
}
