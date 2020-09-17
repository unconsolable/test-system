/*
File Name: rootmainform.h
Description: Define class RootMainForm
Author: unconsolable
*/

#ifndef ROOTMAINFORM_H
#define ROOTMAINFORM_H

#include <QWidget>
#include "studentaccountmodel.h"
#include "teacheraccountmodel.h"

// 释放非空指针
#define CheckDeleteSetNull(Ptr) \
    do                          \
    {                           \
        if ((Ptr))              \
        {                       \
            delete (Ptr);       \
            (Ptr) = nullptr;    \
        }                       \
    }while(0)

enum AccountType
{
    ROOT,
    FACULTY,
    STUDENT
};

namespace Ui {
class RootMainForm;
}

class RootMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit RootMainForm(QWidget *parent = nullptr);
    ~RootMainForm();

private slots:
    // 学生列表点击删除时触发事件
    void on_m_btnRmStu_clicked();
    // 教师列表点击删除时触发事件
    void on_m_btnRmTea_clicked();
    // 学生列表点击增加时触发事件
    void on_m_btnAddStu_clicked();
    // 教师列表点击增加时触发事件
    void on_m_btnAddTea_clicked();
    // 学生列表双击时触发事件
    void on_m_studentAccountItemDoubleClicked(const QModelIndex& index);
    // 教师列表双击时触发事件
    void on_m_teacherAccountItemDoubleClicked(const QModelIndex& index);
    // 加载root账号和密码
    void on_m_btnLoadRoot_clicked();
    // 转为json文件保存
    void on_m_btnSave_clicked();
    // 根据不同账号类别保存数据
    void on_m_btnFinish_clicked();

private:
    Ui::RootMainForm *ui;
    // 学生账号列表的指针
    StudentAccountModel *m_pListModelStudentAccount = nullptr;
    // 教师账号列表的指针
    TeacherAccountModel *m_pListModelTeacherAccount = nullptr;
    // 记录当前双击的账号类型
    AccountType m_accountType = STUDENT;
    // 记录下标
    int m_intAccountChoiceIndex = 0;
};

#endif // ROOTMAINFORM_H
