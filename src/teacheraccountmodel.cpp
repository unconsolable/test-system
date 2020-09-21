/*
文件名: studentaccountmodel.h
版本: 1.0
目的与主要功能: 实现教师账号模型
创建日期: 2020.9.13
描述: 实现教师账号模型
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "teacheraccountmodel.h"
#include <QDebug>

/***************************
 * Name:
 *   TeacherAccountModel
 * Input:
 *   parent 父级模型
 * Return:
 *   none
 * Description:
 *   教师账号模型构造函数
 ***************************/

TeacherAccountModel::TeacherAccountModel(rapidjson::Document *_jsonDocumentAcc, QObject *parent)
    :QAbstractListModel(parent), m_pJsonDocumentAccount(_jsonDocumentAcc)
{
}

/***************************
 * Name:
 *   addAccount
 * Input:
 *   account 账号名
 *   passwd 密码
 * Return:
 *   none
 * Description:
 *   添加教师账号
 ***************************/

void TeacherAccountModel::addAccount(const std::string &account, const std::string &passwd)
{
    // 开始添加数据
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // account建为jsonValue格式
    rapidjson::Value jsonValueAccount;
    jsonValueAccount.SetString(account.c_str(), account.size(), m_pJsonDocumentAccount->GetAllocator());
    // passwd建为jsonValue格式
    rapidjson::Value jsonValuePasswd;
    jsonValuePasswd.SetString(passwd.c_str(), passwd.size(), m_pJsonDocumentAccount->GetAllocator());
    // 尾后追加
    (*m_pJsonDocumentAccount)["faculty"].AddMember(jsonValueAccount, jsonValuePasswd, m_pJsonDocumentAccount->GetAllocator());
    // 数据添加结束
    endInsertRows();
}

/***************************
 * Name:
 *   rowCount
 * Input:
 *   parent 无用
 * Return:
 *   none
 * Description:
 *   返回数据数目
 ***************************/

int TeacherAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 返回model中元素个数
    return (*m_pJsonDocumentAccount)["faculty"].MemberCount();
}

/***************************
 * Name:
 *   rmAccount
 * Input:
 *   pos 数据位置
 * Return:
 *   void
 * Description:
 *   删除pos处账号
 ***************************/

void TeacherAccountModel::rmAccount(int pos)
{
    // 开始删除数据
    beginRemoveRows(QModelIndex(), pos, pos);
    // 传入对应key
    (*m_pJsonDocumentAccount)["faculty"].EraseMember((*m_pJsonDocumentAccount)["faculty"].MemberBegin() + pos);
    // 数据删除结束
    endRemoveRows();
}

/***************************
 * Name:
 *   data
 * Input:
 *   index 数据坐标
 *   role 数据类型
 * Return:
 *   QVariant
 * Description:
 *   输出用于显示的数据
 ***************************/

QVariant TeacherAccountModel::data(const QModelIndex &index, int role) const
{
    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>((*m_pJsonDocumentAccount)["faculty"].MemberCount()))
        return QVariant();
    // 返回账号
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return tr(((*m_pJsonDocumentAccount)["faculty"].MemberBegin()+index.row())->name.GetString());
    }
    return QVariant();
}

/***************************
 * Name:
 *   getAccountAndPasswd
 * Input:
 *   pos
 * Return:
 *   std::pair<std::string, std::string>
 * Description:
 *   返回账号密码对
 ***************************/

std::pair<std::string, std::string> TeacherAccountModel::getAccountAndPasswd(int pos)
{
    // 返回<账号,密码>对
    return std::make_pair(((*m_pJsonDocumentAccount)["faculty"].MemberBegin() + pos)->name.GetString(), ((*m_pJsonDocumentAccount)["faculty"].MemberBegin() + pos)->value.GetString());
}
