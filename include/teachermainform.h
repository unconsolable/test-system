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

private:
    Ui::TeacherMainForm *ui;
    ProblemListModel *m_problemListModel = nullptr;
};

#endif // TEACHERMAINFORM_H
