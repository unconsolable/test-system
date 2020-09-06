/*
File Name: teachermainform.h
Description: Define class TeacherMainForm
Author: unconsolable
*/

#ifndef TEACHERMAINFORM_H
#define TEACHERMAINFORM_H

#include <QMainWindow>

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
public slots:
    void onFileOpen();
    void onFileSave();
private:
    Ui::TeacherMainForm *ui;
    ProblemListModel *m_problemListModel = nullptr;
};

#endif // TEACHERMAINFORM_H
