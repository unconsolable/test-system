#include "rootmainform.h"
#include "ui_rootmainform.h"
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include "rapidjson/prettywriter.h"

extern rapidjson::Document g_jsonDocumentAccount;

RootMainForm::RootMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootMainForm)
{
    ui->setupUi(this);
    // new并设置设置学生的对应model
    m_listModelStudentAccount = new StudentAccountModel(&g_jsonDocumentAccount);
    ui->m_listViewStuAccount->setModel(m_listModelStudentAccount);
    // new并设置设置老师的对应model
    m_listModelTeacherAccount = new TeacherAccountModel(&g_jsonDocumentAccount);
    ui->m_listViewTeacherAccount->setModel(m_listModelTeacherAccount);
    // studentView与slot绑定
    connect(ui->m_listViewStuAccount, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_studentAccountItemDoubleClicked(const QModelIndex&)));
    // teacherView与slot绑定
    connect(ui->m_listViewTeacherAccount, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_teacherAccountItemDoubleClicked(const QModelIndex&)));
}

RootMainForm::~RootMainForm()
{
    delete ui;
    // 检测是否为空再删除并置nullptr
    CheckDeleteSetNull(m_listModelStudentAccount);
    CheckDeleteSetNull(m_listModelTeacherAccount);
}
// 学生账号删除功能
void RootMainForm::on_m_btnRmStu_clicked()
{
    auto selectModel = ui->m_listViewStuAccount->selectionModel();
    if (selectModel)
    {
        // 获得对应下标
        QModelIndexList indexList = selectModel->selectedIndexes();
        // 需要检测大小,避免未选中便按确定的UB
        if (!indexList.size())
        {
            QMessageBox::information(this, tr("错误"), tr("未点击"));
            return;
        }
        for (auto &i : indexList)
            m_listModelStudentAccount->rmAccount(i.row());
    }
}
// 老师账号删除功能
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
            m_listModelTeacherAccount->rmAccount(i.row());
    }
}
// 添加示例账户
void RootMainForm::on_m_btnAddStu_clicked()
{
    m_listModelStudentAccount->addAccount("示例", "修改账户和密码,不要直接保存");
}
// 添加示例账户
void RootMainForm::on_m_btnAddTea_clicked()
{
    m_listModelTeacherAccount->addAccount("示例", "修改账户和密码,不要直接保存");
}
// 选择学生账户
void RootMainForm::on_m_studentAccountItemDoubleClicked(const QModelIndex& index)
{
    // 避免加载root账号后未保存，导致其他账号也无法修改
    ui->m_lineEditAccount->setReadOnly(false);
    // 记录选择的账户类型
    m_accountType = STUDENT;
    // 记录选择的账户位置
    m_intAccountChoiceIndex = index.row();
    // 获取账户密码
    auto accountAndPasswdPair = m_listModelStudentAccount->getAccountAndPasswd(m_intAccountChoiceIndex);
    // 显示
    ui->m_lineEditAccount->setText(tr(accountAndPasswdPair.first.c_str()));
    ui->m_lineEditPasswd->setText(tr(accountAndPasswdPair.second.c_str()));
}
// 选择教师账户
void RootMainForm::on_m_teacherAccountItemDoubleClicked(const QModelIndex& index)
{
    // 避免加载root账号后未保存，导致其他账号也无法修改
    ui->m_lineEditAccount->setReadOnly(false);
    // 记录选择的账户类型
    m_accountType = FACULTY;
    // 记录选择的账户位置
    m_intAccountChoiceIndex = index.row();
    // 获取账户密码
    auto accountAndPasswdPair = m_listModelTeacherAccount->getAccountAndPasswd(m_intAccountChoiceIndex);
    // 显示
    ui->m_lineEditAccount->setText(tr(accountAndPasswdPair.first.c_str()));
    ui->m_lineEditPasswd->setText(tr(accountAndPasswdPair.second.c_str()));
}
// 加载管理员账号信息
void RootMainForm::on_m_btnLoadRoot_clicked()
{
    // 记录选择的账户类型
    m_accountType = ROOT;
    ui->m_lineEditAccount->setReadOnly(true);
    // 显示
    ui->m_lineEditAccount->setText(tr("root"));
    ui->m_lineEditPasswd->setText(tr(g_jsonDocumentAccount["root"].GetString()));
}

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
        rapidjson::Value newPasswdJson;
        newPasswdJson.SetString(newPasswd.c_str(), newPasswd.size(), g_jsonDocumentAccount.GetAllocator());
        g_jsonDocumentAccount.AddMember("root", newPasswdJson, g_jsonDocumentAccount.GetAllocator());
    }
    else if (m_accountType == FACULTY)
    {
        // 删除原来
        m_listModelTeacherAccount->rmAccount(m_intAccountChoiceIndex);
        // 增加新的
        m_listModelTeacherAccount->addAccount(ui->m_lineEditAccount->text().toStdString(), ui->m_lineEditPasswd->text().toStdString());
    }
    else if (m_accountType == STUDENT)
    {
        // 删除原来
        m_listModelStudentAccount->rmAccount(m_intAccountChoiceIndex);
        // 增加新的
        m_listModelStudentAccount->addAccount(ui->m_lineEditAccount->text().toStdString(), ui->m_lineEditPasswd->text().toStdString());
    }
}
