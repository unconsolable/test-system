#include "teachermainform.h"
#include "ui_teachermainform.h"

TeacherMainForm::TeacherMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherMainForm)
{
    ui->setupUi(this);
}

TeacherMainForm::~TeacherMainForm()
{
    delete ui;
}
