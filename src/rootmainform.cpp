#include "rootmainform.h"
#include "ui_rootmainform.h"

RootMainForm::RootMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootMainForm)
{
    ui->setupUi(this);
}

RootMainForm::~RootMainForm()
{
    delete ui;
}
