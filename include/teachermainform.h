/*
File Name: teachermainform.h
Description: Define class TeacherMainForm
Author: unconsolable
*/

#ifndef TEACHERMAINFORM_H
#define TEACHERMAINFORM_H

#include <QMainWindow>

namespace Ui {
class TeacherMainForm;
}

class TeacherMainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherMainForm(QWidget *parent = nullptr);
    ~TeacherMainForm();

private:
    Ui::TeacherMainForm *ui;
};

#endif // TEACHERMAINFORM_H
