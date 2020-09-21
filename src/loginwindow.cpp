/*
文件名: loginwindow.h
版本: 1.0
目的与主要功能: 实现登录窗口类
创建日期: 2020.9.2
描述: 实现登录窗口类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <string>

extern rapidjson::Document g_jsonDocumentAccount;

/***************************
 * Name:
 *   LoginWindow
 * Input:
 *   parent 父窗体名称
 * Return:
 *   none
 * Description:
 *   构造登录窗口类
 ***************************/

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

/***************************
 * Name:
 *   LoginWindow
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   析构登录窗口类
 ***************************/

LoginWindow::~LoginWindow()
{
    delete ui;
    // 删除后，置nullptr，防止悬垂指针
    if (m_pTeacherFormTea)
    {
        delete m_pTeacherFormTea;
        m_pTeacherFormTea = nullptr;
    }
    if (m_pStudentFormStu)
    {
        delete m_pStudentFormStu;
        m_pStudentFormStu = nullptr;
    }
    if (m_pRootFormRoot)
    {
        delete m_pRootFormRoot;
        m_pRootFormRoot = nullptr;
    }
}

/***************************
 * Name:
 *   on_loginBtn_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   点击登录按钮后发生的事件
 *   主要负责判断密码正确性
 *   并切换到不同模块
 ***************************/

void LoginWindow::on_loginBtn_clicked()
{
    // 获得输入的账号和密码
    const char *idStrPtr = ui->idEdit->text().toStdString().c_str();
    std::string pwStr = ui->pwEdit->text().toStdString();
    std::string rootPwStr = g_jsonDocumentAccount["root"].GetString();
    if (g_jsonDocumentAccount["faculty"].HasMember(idStrPtr))
    {
        // 比较密码
        std::string rightPwStr = g_jsonDocumentAccount["faculty"][idStrPtr].GetString();
        if (rightPwStr == pwStr)
        {
            // 密码正确，切换窗口
            m_pTeacherFormTea = new TeacherMainForm();
            this->close();
            m_pTeacherFormTea->show();
        }
        else
        {
            // 密码错误，报错
            QMessageBox::information(this, "错误", "密码错误");
        }
    }
    else if (g_jsonDocumentAccount["student"].HasMember(idStrPtr))
    {
        // 学生界面
        std::string rightPwStr = g_jsonDocumentAccount["student"][idStrPtr].GetString();
        if (rightPwStr == pwStr)
        {
            // 密码正确，切换窗口
            m_pStudentFormStu = new StudentMainForm();
            this->close();
            m_pStudentFormStu->show();
        }
        else
        {
            // 密码错误，报错
            QMessageBox::information(this, "错误", "密码错误");
        }
    }
    else if (ui->idEdit->text() == QString("root"))
    {
        // 管理员界面
        if (rootPwStr == pwStr)
        {
            // 密码正确，切换窗口
            m_pRootFormRoot = new RootMainForm();
            this->close();
            m_pRootFormRoot->show();
        }
        else
            // 密码错误，报错
            QMessageBox::information(this, "错误", "密码错误");
    }
    else
    {
        // 不存在
        QMessageBox::information(this, "错误", "账号不存在, 请联系添加");
    }

}
