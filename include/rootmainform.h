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
    void on_m_btnRmStu_clicked();

    void on_m_btnRmTea_clicked();

    void on_m_btnAddStu_clicked();

    void on_m_btnAddTea_clicked();
    void on_m_studentAccountItemDoubleClicked(const QModelIndex& index);
    void on_m_teacherAccountItemDoubleClicked(const QModelIndex& index);
    void on_m_btnLoadRoot_clicked();

private:
    Ui::RootMainForm *ui;
    StudentAccountModel *m_listModelStudentAccount = nullptr;
    TeacherAccountModel *m_listModelTeacherAccount = nullptr;
    AccountType m_accountType = STUDENT;
    int m_intAccountChoiceIndex = 0;
};

#endif // ROOTMAINFORM_H
