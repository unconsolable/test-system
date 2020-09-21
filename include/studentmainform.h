/*
文件名: studentmainform.h
版本: 1.0
目的与主要功能: 定义考试系统窗体类
创建日期: 2020.9.3
描述: 定义考试系统窗体类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
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
    // 选定并显示题目
    void on_m_problemListItemDoubleClicked(const QModelIndex &index);
    // 计算此题得分
    void on_m_buttonFinish_clicked();
    // 切换至下一题
    void on_m_buttonNext_clicked();
    // 切换至上一题
    void on_m_buttonPrev_clicked();

private:
    Ui::StudentMainForm *ui;
    // 问题列表(试卷)的模型指针,类似CDoc
    ProblemListModel *m_pProblemListModel = nullptr;
    // 专门负责显示题目信息的子窗口
    StudentProblemWidget *m_studentProblemWidget = nullptr;
    // 当前选的题目下标
    int m_intCurProblemIndex = 0;
    // 目前每题得分
    double *m_doubleArrayAnswerMark= nullptr;
};

#endif // STUDENTMAINFORM_H
