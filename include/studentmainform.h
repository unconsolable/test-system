/*
File Name: studentmainform.h
Description: Define StudentMainForm
Author: unconsolable
*/

#ifndef STUDENTMAINFORM_H
#define STUDENTMAINFORM_H

#include <QMainWindow>
#include <QItemSelection>
#include "problemlistmodel.h"
#include "studentproblemwidget.h"

namespace Ui {
class StudentMainForm;
}

class StudentMainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentMainForm(QWidget *parent = nullptr);
    ~StudentMainForm();
private slots:
    // 导入试题文件
    void onFileOpen();
    // 提交结果
    void onFileSave();
    // 计算此题得分
//    void on_m_buttonFinish_clicked();
    // 选定并显示题目
    void on_m_problemListItemDoubleClicked(const QModelIndex &index);
    void on_m_buttonFinish_clicked();

    void on_m_buttonNext_clicked();

    void on_m_buttonPrev_clicked();

private:
    Ui::StudentMainForm *ui;
    ProblemListModel *m_problemListModel = nullptr;
    StudentProblemWidget *m_studentProblemWidget = nullptr;
    // 当前选的题目下标
    int m_intCurProblemIndex = 0;
    // 目前得到总分
    double *m_doubleArrayAnswerMark= nullptr;
};

#endif // STUDENTMAINFORM_H
