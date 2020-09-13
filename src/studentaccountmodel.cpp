/*
File Name:
Description:
Author: unconsolable
*/
#include "studentaccountmodel.h"

StudentAccountModel::StudentAccountModel(rapidjson::Document *_jsonDocumentAcc, QObject *parent)
    :QAbstractListModel(parent), m_jsonDocumentAccount(_jsonDocumentAcc)
{
    int curIndex = 0;
    auto& studentData = (*m_jsonDocumentAccount)["student"];
    // 构造映射关系
    for (auto cur = studentData.MemberBegin(); cur != studentData.MemberEnd(); ++cur)
    {
        m_mapListIndexToAccount[curIndex++] = std::string(cur->name.GetString());
    }
}

void StudentAccountModel::addAccount(const std::string &account, const std::string &passwd)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // 建立映射
    m_mapListIndexToAccount[rowCount()] = account;
    // account建为jsonValue格式
    rapidjson::Value jsonValueAccount;
    jsonValueAccount.SetString(account.c_str(), account.size(), m_jsonDocumentAccount->GetAllocator());
    // passwd建为jsonValue格式
    rapidjson::Value jsonValuePasswd;
    jsonValueAccount.SetString(passwd.c_str(), passwd.size(), m_jsonDocumentAccount->GetAllocator());
    // 尾后追加
    (*m_jsonDocumentAccount)["student"].AddMember(jsonValueAccount, jsonValuePasswd, m_jsonDocumentAccount->GetAllocator());
    endInsertRows();
}

int StudentAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 返回model中元素个数
    return (*m_jsonDocumentAccount)["student"].MemberCount();
}

void StudentAccountModel::rmAccount(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    // 传入对应key
    (*m_jsonDocumentAccount)["student"].RemoveMember(m_mapListIndexToAccount[pos].c_str());
    endRemoveRows();
}

QVariant StudentAccountModel::data(const QModelIndex &index, int role) const
{
    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>((*m_jsonDocumentAccount)["student"].MemberCount()))
        return QVariant();
    // 返回账号
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr(m_mapListIndexToAccount.at(index.row()).c_str());
    return QVariant();
}

std::pair<std::string, std::string> StudentAccountModel::getAccountAndPasswd(int pos)
{
    return std::make_pair(m_mapListIndexToAccount[pos], (*m_jsonDocumentAccount)["student"][m_mapListIndexToAccount[pos].c_str()].GetString());
}
