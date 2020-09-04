/*
File Name: studentmainform.h
Description: Define StudentMainForm
Author: unconsolable
*/

#ifndef STUDENTMAINFORM_H
#define STUDENTMAINFORM_H

#include <QMainWindow>

namespace Ui {
class StudentMainForm;
}

class StudentMainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentMainForm(QWidget *parent = nullptr);
    ~StudentMainForm();

private:
    Ui::StudentMainForm *ui;
};

#endif // STUDENTMAINFORM_H
