/*
File Name: teacheraccountmodel.cpp
Description: A Model for Teacher Account
Author: unconsolable
*/
#include "teacheraccountmodel.h"
#include <QDebug>

TeacherAccountModel::TeacherAccountModel(rapidjson::Document *_jsonDocumentAcc, QObject *parent)
    :QAbstractListModel(parent), m_jsonDocumentAccount(_jsonDocumentAcc)
{
}

void TeacherAccountModel::addAccount(const std::string &account, const std::string &passwd)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // account建为jsonValue格式
    rapidjson::Value jsonValueAccount;
    jsonValueAccount.SetString(account.c_str(), account.size(), m_jsonDocumentAccount->GetAllocator());
    // passwd建为jsonValue格式
    rapidjson::Value jsonValuePasswd;
    jsonValuePasswd.SetString(passwd.c_str(), passwd.size(), m_jsonDocumentAccount->GetAllocator());
    // 尾后追加
    (*m_jsonDocumentAccount)["faculty"].AddMember(jsonValueAccount, jsonValuePasswd, m_jsonDocumentAccount->GetAllocator());
    endInsertRows();
}

int TeacherAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 返回model中元素个数
    return (*m_jsonDocumentAccount)["faculty"].MemberCount();
}

void TeacherAccountModel::rmAccount(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    // 传入对应key
    (*m_jsonDocumentAccount)["faculty"].EraseMember((*m_jsonDocumentAccount)["faculty"].MemberBegin() + pos);
    endRemoveRows();
}

QVariant TeacherAccountModel::data(const QModelIndex &index, int role) const
{
    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>((*m_jsonDocumentAccount)["faculty"].MemberCount()))
        return QVariant();
    // 返回账号
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return tr(((*m_jsonDocumentAccount)["faculty"].MemberBegin()+index.row())->name.GetString());
    }
    return QVariant();
}

std::pair<std::string, std::string> TeacherAccountModel::getAccountAndPasswd(int pos)
{
    return std::make_pair(((*m_jsonDocumentAccount)["faculty"].MemberBegin() + pos)->name.GetString(), ((*m_jsonDocumentAccount)["faculty"].MemberBegin() + pos)->value.GetString());
}
