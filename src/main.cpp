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
    std::fstream b_fstrmAccount("account.json", std::ios::in | std::ios::out);
    if (!b_fstrmAccount)
    {
        // 若文件打开失败报错退出
        QMessageBox::information(nullptr,"错误","账户文件打开错误");
        exit(1);
    }
    std::string b_strAccountInfoStr;
    std::string t_strInput;
    while (b_fstrmAccount >> t_strInput)
    {
        // 读入账户文件形成JSON字符串
        b_strAccountInfoStr += t_strInput + ' ';
    }
    // 若解析有错误则报错退出
    if (g_jsonDocumentAccount.Parse(b_strAccountInfoStr.c_str()).HasParseError())
    {
        QMessageBox::information(nullptr, "错误", "解析账户文件错误");
        exit(1);
    }
    LoginWindow w;
    w.show();
    return a.exec();
}
