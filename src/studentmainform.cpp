/*
File Name: studentmainform.h
Description: Implement StudentMainForm
Author: unconsolable
*/

#include "studentmainform.h"
#include "ui_studentmainform.h"

StudentMainForm::StudentMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentMainForm)
{
    ui->setupUi(this);
}

StudentMainForm::~StudentMainForm()
{
    delete ui;
}
