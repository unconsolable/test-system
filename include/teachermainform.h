/*
File Name: teachermainform.h
Description: Define class TeacherMainForm
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
    void onFileOpen();
    void onFileSave();
    void on_m_buttonRm_clicked();
    void on_m_buttonSelect_clicked();

    void on_m_buttonFinish_clicked();

private:
    Ui::TeacherMainForm *ui;
    ProblemListModel *m_problemListModel = nullptr;
    TeacherProblemWidget *m_teacherProblemWidget = nullptr;
    // 当前选择的题目的下标
    int m_intCurProblemIndex= 0;
};

#endif // TEACHERMAINFORM_H
