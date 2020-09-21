/*
文件名: rootmainform.h
版本: 1.0
目的与主要功能: 实现账号管理窗口类
创建日期: 2020.9.12
描述: 实现账号管理窗口类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/
#include "rootmainform.h"
#include "ui_rootmainform.h"
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include "rapidjson/prettywriter.h"

extern rapidjson::Document g_jsonDocumentAccount;

/***************************
 * Name:
 *   RootMainForm
 * Input:
 *   parent 父窗体指针
 * Return:
 *   none
 * Description:
 *   构造RootMainForm
 ***************************/

RootMainForm::RootMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootMainForm)
{
    ui->setupUi(this);
    // new并设置设置学生账号的对应model
    m_pListModelStudentAccount = new StudentAccountModel(&g_jsonDocumentAccount);
    ui->m_listViewStuAccount->setModel(m_pListModelStudentAccount);
    // new并设置设置老师账号的对应model
    m_pListModelTeacherAccount = new TeacherAccountModel(&g_jsonDocumentAccount);
    ui->m_listViewTeacherAccount->setModel(m_pListModelTeacherAccount);
    // studentView的双击信号与slot绑定
    connect(ui->m_listViewStuAccount, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_studentAccountItemDoubleClicked(const QModelIndex&)));
    // teacherView的双击信号与slot绑定
    connect(ui->m_listViewTeacherAccount, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_teacherAccountItemDoubleClicked(const QModelIndex&)));
}

/***************************
 * Name:
 *   ~RootMainForm
 * Input:
 *   parent 父窗体指针
 * Return:
 *   none
 * Description:
 *   析构RootMainForm
 ***************************/

RootMainForm::~RootMainForm()
{
    delete ui;
    // 检测是否为空再删除并置nullptr
    CheckDeleteSetNull(m_pListModelStudentAccount);
    CheckDeleteSetNull(m_pListModelTeacherAccount);
}

/***************************
 * Name:
 *   on_m_btnRmStu_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   学生账号删除功能
 ***************************/

void RootMainForm::on_m_btnRmStu_clicked()
{
    auto selectModel = ui->m_listViewStuAccount->selectionModel();
    if (selectModel)
    {
        // 获得对应下标
        QModelIndexList indexList = selectModel->selectedIndexes();
        // 需要检测大小,避免未选中便按确定的错误
        if (!indexList.size())
        {
            QMessageBox::information(this, tr("错误"), tr("未点击"));
            return;
        }
        // 逐个删除
        for (auto &i : indexList)
            m_pListModelStudentAccount->rmAccount(i.row());
    }
}

/***************************
 * Name:
 *   on_m_btnRmTea_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   老师账号删除功能
 ***************************/

void RootMainForm::on_m_btnRmTea_clicked()
{
    auto selectModel = ui->m_listViewTeacherAccount->selectionModel();
    if (selectModel)
    {
        // 获得对应下标
        QModelIndexList indexList = selectModel->selectedIndexes();
        // 需要检测大小,避免未点击的UB
        if (!indexList.size())
        {
            QMessageBox::information(this, tr("错误"), tr("未点击"));
            return;
        }
        for (auto &i : indexList)
            m_pListModelTeacherAccount->rmAccount(i.row());
    }
}

/***************************
 * Name:
 *   on_m_btnAddStu_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   学生账号中添加示例账户
 ***************************/

void RootMainForm::on_m_btnAddStu_clicked()
{
    m_pListModelStudentAccount->addAccount("示例", "修改账户和密码,不要直接保存");
}

/***************************
 * Name:
 *   on_m_btnAddTea_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   老师账号中添加示例账户
 ***************************/

void RootMainForm::on_m_btnAddTea_clicked()
{
    m_pListModelTeacherAccount->addAccount("示例", "修改账户和密码,不要直接保存");
}

/***************************
 * Name:
 *   on_m_studentAccountItemDoubleClicked
 * Input:
 *   index 点击的数据的坐标
 * Return:
 *   none
 * Description:
 *   选择学生账户
 ***************************/

void RootMainForm::on_m_studentAccountItemDoubleClicked(const QModelIndex& index)
{
    // 避免加载root账号后未保存，导致其他账号也无法修改
    ui->m_lineEditAccount->setReadOnly(false);
    // 记录选择的账户类型
    m_accountType = STUDENT;
    // 记录选择的账户位置
    m_intAccountChoiceIndex = index.row();
    // 获取账户密码
    auto accountAndPasswdPair = m_pListModelStudentAccount->getAccountAndPasswd(m_intAccountChoiceIndex);
    // 显示
    ui->m_lineEditAccount->setText(tr(accountAndPasswdPair.first.c_str()));
    ui->m_lineEditPasswd->setText(tr(accountAndPasswdPair.second.c_str()));
}

/***************************
 * Name:
 *   on_m_teacherAccountItemDoubleClicked
 * Input:
 *   index 点击的数据的坐标
 * Return:
 *   none
 * Description:
 *   选择教师账户
 ***************************/

void RootMainForm::on_m_teacherAccountItemDoubleClicked(const QModelIndex& index)
{
    // 避免加载root账号后未保存，导致其他账号也无法修改
    ui->m_lineEditAccount->setReadOnly(false);
    // 记录选择的账户类型
    m_accountType = FACULTY;
    // 记录选择的账户位置
    m_intAccountChoiceIndex = index.row();
    // 获取账户密码
    auto accountAndPasswdPair = m_pListModelTeacherAccount->getAccountAndPasswd(m_intAccountChoiceIndex);
    // 显示
    ui->m_lineEditAccount->setText(tr(accountAndPasswdPair.first.c_str()));
    ui->m_lineEditPasswd->setText(tr(accountAndPasswdPair.second.c_str()));
}

/***************************
 * Name:
 *   on_m_btnLoadRoot_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   加载管理员账号信息
 ***************************/

void RootMainForm::on_m_btnLoadRoot_clicked()
{
    // 记录选择的账户类型
    m_accountType = ROOT;
    ui->m_lineEditAccount->setReadOnly(true);
    // 显示
    ui->m_lineEditAccount->setText(tr("root"));
    ui->m_lineEditPasswd->setText(tr(g_jsonDocumentAccount["root"].GetString()));
}

/***************************
 * Name:
 *   on_m_btnSave_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   保存为文件
 ***************************/

void RootMainForm::on_m_btnSave_clicked()
{
    // 获得文件路径并打开
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open New File","/","JSON files(*.json)");
    std::ofstream b_ofStrmProblemList(b_qStrFileDir.toStdString());
    // 判断流是否成功打开
    if (!b_ofStrmProblemList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    // 转换为字符串,参考rapidjson文档
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    g_jsonDocumentAccount.Accept(writer);
    // 写入
    b_ofStrmProblemList << sb.GetString();
}

/***************************
 * Name:
 *   on_m_btnFinish_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   完成信息修改,记录信息
 ***************************/

void RootMainForm::on_m_btnFinish_clicked()
{
    // switch-case中不能定义并初始化变量,采用if
    if (m_accountType == ROOT)
    {
        // 变为可写
        ui->m_lineEditAccount->setReadOnly(false);
        // 删除原来
        g_jsonDocumentAccount.RemoveMember("root");
        // 增加新的
        std::string newPasswd = ui->m_lineEditPasswd->text().toStdString().c_str();
        // 用于存储转为JSON字符串的密码
        rapidjson::Value newPasswdJson;
        // 存储字符串
        newPasswdJson.SetString(newPasswd.c_str(), newPasswd.size(), g_jsonDocumentAccount.GetAllocator());
        // 添加账号与密码键值对
        g_jsonDocumentAccount.AddMember("root", newPasswdJson, g_jsonDocumentAccount.GetAllocator());
    }
    else if (m_accountType == FACULTY)
    {
        // 删除原来
        m_pListModelTeacherAccount->rmAccount(m_intAccountChoiceIndex);
        // 增加新的
        m_pListModelTeacherAccount->addAccount(ui->m_lineEditAccount->text().toStdString(), ui->m_lineEditPasswd->text().toStdString());
    }
    else if (m_accountType == STUDENT)
    {
        // 删除原来
        m_pListModelStudentAccount->rmAccount(m_intAccountChoiceIndex);
        // 增加新的
        m_pListModelStudentAccount->addAccount(ui->m_lineEditAccount->text().toStdString(), ui->m_lineEditPasswd->text().toStdString());
    }
}
