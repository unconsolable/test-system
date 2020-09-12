/*
File Name: loginwindow.h
Description: Header File for the Login Window
Author: unconsolable
*/

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "teachermainform.h"

#include "studentmainform.h"
#include "rootmainform.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginBtn_clicked();

private:
    Ui::LoginWindow *ui;
    TeacherMainForm *m_pTeacherFormTea = nullptr;
    StudentMainForm *m_pStudentFormStu = nullptr;
    RootMainForm *m_pRootFormRoot = nullptr;
};
#endif // LOGINWINDOW_H
