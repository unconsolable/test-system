#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <string>

extern rapidjson::Document accountDocument;

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    if (teaForm)
        delete teaForm;
    if (stuForm)
        delete stuForm;
}

void LoginWindow::on_loginBtn_clicked()
{
    // 获得输入的账号和密码
    const char *idStrPtr = ui->idEdit->text().toStdString().c_str();
    std::string pwStr = ui->pwEdit->text().toStdString();
    std::string rootPwStr = accountDocument["root"].GetString();
    if (accountDocument["faculty"].HasMember(idStrPtr))
    {
        // 教师界面
        std::string rightPwStr = accountDocument["faculty"][idStrPtr].GetString();
        if (rightPwStr == pwStr)
        {
            teaForm = new TeacherMainForm();
            this->close();
            teaForm->show();
        }
        else
        {
            QMessageBox::information(this, "错误", "密码错误");
        }
    }
    else if (accountDocument["student"].HasMember(idStrPtr))
    {
        // 学生界面
        std::string rightPwStr = accountDocument["student"][idStrPtr].GetString();
        if (rightPwStr == pwStr)
        {
            stuForm = new StudentMainForm();
            this->close();
            stuForm->show();
        }
        else
        {
            QMessageBox::information(this, "错误", "密码错误");
        }
    }
    else if (rootPwStr == pwStr)
    {
        // 管理员界面
    }
    else
    {
        // 不存在
        QMessageBox::information(this, "错误", "账号不存在, 请联系添加");
    }

}
