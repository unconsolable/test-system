/*
File Name: teachermainform.h
Description: Implement TeacherMainForm
Author: unconsolable
*/

#include "teachermainform.h"
#include "ui_teachermainform.h"
#include <QFileDialog>
#include "problemlistmodel.h"
#include <fstream>
#include <QMessageBox>

TeacherMainForm::TeacherMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherMainForm)
{
    ui->setupUi(this);
    connect(ui->m_actionOpenFile, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    connect(ui->m_actionSaveFile, SIGNAL(triggered()), this, SLOT(onFileSave()));
}

TeacherMainForm::~TeacherMainForm()
{
    delete ui;
    if (m_problemListModel)
        delete m_problemListModel;
}

void TeacherMainForm::onFileOpen()
{
    // 获得文件路径
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open Paper File","/","JSON files(*.json)");
    // 打开文件
    std::ifstream b_ifStrmProList(b_qStrFileDir.toStdString());
    if (!b_ifStrmProList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    std::string b_strProListInfo;
    std::string t_strInput;
    while (b_ifStrmProList >> t_strInput)
    {
        // 读入账户文件形成JSON字符串
        b_strProListInfo += t_strInput + ' ';
    }
    rapidjson::Document b_jsonDocProList;
    if (b_jsonDocProList.Parse(b_strProListInfo.c_str()).HasParseError())
    {
        QMessageBox::information(this, "Error", tr("试卷解析失败"));
        return;
    }
    m_problemListModel = new ProblemListModel();
    if (!m_problemListModel->fromJsonDocument(b_jsonDocProList))
        QMessageBox::information(this, "Error", tr("转为Model失败"));
//    ui->m_listViewProblem->setModel(m_problemListModel);
}


void TeacherMainForm::onFileSave()
{
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open Paper File","/","JSON files(*.json)");
    std::ofstream b_ofStrmProList(b_qStrFileDir.toStdString());
    if (!b_ofStrmProList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    std::string res = m_problemListModel->toJsonString();
    b_ofStrmProList << res;
}
