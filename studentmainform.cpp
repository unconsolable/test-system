#include "studentmainform.h"
#include "ui_studentmainform.h"

StudentMainForm::StudentMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentMainForm)
{
    ui->setupUi(this);
}

StudentMainForm::~StudentMainForm()
{
    delete ui;
}
