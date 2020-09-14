/*
File Name: problemlistmodel.cpp
Description: Implement the class ProblemListModel
Author: unconsolable
*/

#include "problemlistmodel.h"
#include "singlechoiceproblem.h"
#include "multiplechoiceproblem.h"
#include "judgementproblem.h"
#include "writeproblem.h"
#include "rapidjson/prettywriter.h"

ProblemListModel::ProblemListModel(QObject *parent) : QAbstractListModel(parent)
{
}

ProblemListModel::~ProblemListModel()
{
    // 析构函数,如下倒序释放内存会引起SIGSEGV
    // for (auto b_iter = m_pProblemVecProList.rbegin(); b_iter != m_pProblemVecProList.rend(); --b_iter)
    // {
    //     delete *b_iter;
    //    *b_iter = nullptr;
    // }
    for (auto i : m_pProblemVecProList)
    {
        if (i)
        {
            delete i;
            i = nullptr;
        }
    }
}
// 添加单选题
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new SingleChoiceProblem(_mark, _desc, _ansList, _right));
    // 发送Model已变化的信号
    endInsertRows();
}
// 添加多选题
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new MultipleChoiceProblem(_mark, _desc, _ansList, _right));
    // 发送Model已变化的信号
    endInsertRows();
}
// 添加判断题
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, bool _right)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new JudgementProblem(_mark, _desc, _right));
    // 发送Model已变化的信号
    endInsertRows();
}
// 添加简答题
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new WriteProblem(_mark, _desc, _keyWords));
    // 发送Model已变化的信号
    endInsertRows();
}
// 使用PrettyWriter转换成字符
std::string ProblemListModel::toJsonString() const
{
    rapidjson::Document b_jsonTestPaper(rapidjson::kObjectType);
    rapidjson::Value b_jsonProblemList(rapidjson::kArrayType);
    // 每个题目转为JSON结构
    for (const auto i : m_pProblemVecProList)
    {
        b_jsonProblemList.PushBack(i->toJsonValue(b_jsonTestPaper), b_jsonTestPaper.GetAllocator());
    }
    // 添加Key-Value
    b_jsonTestPaper.AddMember("problem", b_jsonProblemList, b_jsonTestPaper.GetAllocator());
    // 转换为字符串,参考rapidjson文档
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    b_jsonTestPaper.Accept(writer);
    return sb.GetString();
}
bool ProblemListModel::fromJsonDocument(const rapidjson::Document& doc)
{
    // 检查是否有为problem的key
    if (!doc.HasMember("problem") || !doc["problem"].IsArray())
    {
        return false;
    }
    for (auto& b_jsonValueEachProblem : doc["problem"].GetArray())
    {
        // 这个用于存选项或者关键词,两个不会同时出现
        std::vector<std::string> tmpAnsListOrKeyWords;
        // 这个用于存多选的选项字符
        std::vector<char> multipleChoice;
        // 根据类型对应构造
        // 分值类型变化为Double
        switch (b_jsonValueEachProblem["type"].GetInt())
        {
        case SINGLE:
            // 存入选项描述
            for (auto& i : b_jsonValueEachProblem["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 传入题目信息
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords, b_jsonValueEachProblem["right"].GetInt());
            break;
        case MULTIPLE:
            //存入选项描述
            for (auto& i : b_jsonValueEachProblem["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 存储选项用的是char,应转为int
            for (auto& i : b_jsonValueEachProblem["right"].GetArray())
            {
                multipleChoice.emplace_back(i.GetInt());
            }
            // 传入题目信息
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords, multipleChoice);
            break;
        case JUDGEMENT:
            // 直接传true/false即可
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()),b_jsonValueEachProblem["right"].GetBool());
            break;
        case WRITE:
            // 构造关键词列表
            for (auto& i: b_jsonValueEachProblem["right"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 传入题目信息
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords);
            break;
        default:
            return false;
        }
    }
    return true;
}

int ProblemListModel::rowCount(const QModelIndex &parent) const
{
    // 用于View显示使用,返回Model中条目
    Q_UNUSED(parent);
    return m_pProblemVecProList.size();
}

QVariant ProblemListModel::data(const QModelIndex& index, int role) const
{

    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>(m_pProblemVecProList.size()))
        return QVariant();
    // 返回题目类型
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        // 格式化返回字符串,类似sprintf
        return QString("第%1题,%2,%3分").arg(index.row() + 1).arg(tr(m_pProblemVecProList[index.row()]->convertType())).arg(m_pProblemVecProList[index.row()]->getMark(),0,'f',1);
    }
    return QVariant();
}

QVariant ProblemListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    // 返回表头
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return tr("题型");
    return QVariant();
}

Qt::ItemFlags ProblemListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    // 按位或ItemIsEditable,告知Controller能够修改显示的信息
    // 不是修改数据
    // return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    return QAbstractItemModel::flags(index);
}

bool ProblemListModel::rmProblem(int pos)
{
    // 向Model告知,便于Model中显示的变化
    beginRemoveRows(QModelIndex(), pos, pos);
    // 删除指针之前**释放**对应资源
    delete m_pProblemVecProList[pos];
    // 再删除指针(即一串对应虚拟地址空间的编号)
    m_pProblemVecProList.erase(m_pProblemVecProList.begin() + pos);
    endRemoveRows();
    return true;
}

Problem* ProblemListModel::operator[](size_t index)
{
    // 检查下标是否有效
    if (index >= m_pProblemVecProList.size())
        return nullptr;
    return m_pProblemVecProList[index];
}

double ProblemListModel::totalMark() const
{
    // 计算总分,便于判断是否是总分
    // 低于100分的试卷用于考试
    double totalmark = 0;
    for (auto& i : m_pProblemVecProList)
    {
        totalmark += i->getMark();
    }
    return totalmark;
}
