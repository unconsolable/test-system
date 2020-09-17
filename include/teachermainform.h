/*
File Name: teachermainform.h
Description: Define the class of the form for teachers to generate test problems
Author: unconsolable
*/

#ifndef TEACHERMAINFORM_H
#define TEACHERMAINFORM_H

#include <QMainWindow>
#include <QItemSelection>
#include "problemlistmodel.h"
#include "teacherproblemwidget.h"

class ProblemListModel;

namespace Ui {
class TeacherMainForm;
}

class TeacherMainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherMainForm(QWidget *parent = nullptr);
    ~TeacherMainForm();
private slots:
    // 新建文件的slot
    void onFileNew();
    // 导入文件的slot
    void onFileOpen();
    // 保存文件的slot
    void onFileSave();
    // 删除题目的slot
    void on_m_buttonRm_clicked();
    // 完成修改的slot
    void on_m_buttonFinish_clicked();
    // 添加题目的slot
    void on_m_buttonAdd_clicked();
    // 双击选中题目
    void on_m_problemListItemDoubleClicked(const QModelIndex &index);

private:
    Ui::TeacherMainForm *ui;
    // 问题列表(试卷)的模型指针,类似CDoc
    ProblemListModel *m_pProblemListModel = nullptr;
    // 专门负责显示题目信息的子窗口
    TeacherProblemWidget *m_teacherProblemWidget = nullptr;
    // 当前选择的题目的下标
    int m_intCurProblemIndex = 0;
};

#endif // TEACHERMAINFORM_H
