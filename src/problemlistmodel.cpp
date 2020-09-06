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
    // 析构函数,倒序释放内存
    for (auto b_iter = m_pProblemVecProList.rbegin(); b_iter != m_pProblemVecProList.rend(); --b_iter)
    {
        delete *b_iter;
        *b_iter = nullptr;
    }
}
// 添加单选题
void ProblemListModel::addSingleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right)
{
    m_pProblemVecProList.push_back(new SingleChoiceProblem(_mark, _desc, _ansList, _right));
}
// 添加多选题
void ProblemListModel::addMultipleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right)
{
    m_pProblemVecProList.push_back(new MultipleChoiceProblem(_mark, _desc, _ansList, _right));
}
// 添加判断题
void ProblemListModel::addJudgementProblem(double _mark, const std::string& _desc, bool _right)
{
    m_pProblemVecProList.push_back(new JudgementProblem(_mark, _desc, _right));
}
// 添加简答题
void ProblemListModel::addWriteProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords)
{
    m_pProblemVecProList.push_back(new WriteProblem(_mark, _desc, _keyWords));
}
// 使用PrettyWriter转换成字符
std::string ProblemListModel::toJsonString() const
{
    rapidjson::Document b_jsonTestPaper(rapidjson::kObjectType);
    rapidjson::Value b_jsonProblemList(rapidjson::kArrayType);
    for (const auto i : m_pProblemVecProList)
    {
        b_jsonProblemList.PushBack(i->toJsonValue(b_jsonTestPaper),b_jsonTestPaper.GetAllocator());
    }
    b_jsonTestPaper.AddMember("problem", b_jsonProblemList,b_jsonTestPaper.GetAllocator());
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    b_jsonTestPaper.Accept(writer);
    return sb.GetString();
}
bool ProblemListModel::fromJsonDocument(const rapidjson::Document& doc)
{
    // 检查是否有key:problem
    if (!doc.HasMember("problem") || !doc["problem"].IsArray())
    {
        return false;
    }
    for (auto& b_jsonValueEachProblem : doc["problem"].GetArray())
    {
        std::vector<std::string> tmpAnsListOrKeyWords;
        std::vector<char> multipleChoice;
        // 根据类型对应构造
        switch (b_jsonValueEachProblem["type"].GetInt())
        {
        case SINGLE:
            for (auto& i : b_jsonValueEachProblem["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            addSingleChoiceProblem(b_jsonValueEachProblem["mark"].GetInt(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords, b_jsonValueEachProblem["right"].GetInt());
            break;
        case MULTIPLE:
            for (auto& i : b_jsonValueEachProblem["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 存储选项用的是INT
            for (auto& i : b_jsonValueEachProblem["right"].GetArray())
            {
                multipleChoice.emplace_back(i.GetInt());
            }
            addMultipleChoiceProblem(b_jsonValueEachProblem["mark"].GetInt(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords, multipleChoice);
            break;
        case JUDGEMENT:
            addJudgementProblem(b_jsonValueEachProblem["mark"].GetInt(), std::string(b_jsonValueEachProblem["description"].GetString()),b_jsonValueEachProblem["right"].GetBool());
            break;
        case WRITE:
            for (auto& i: b_jsonValueEachProblem["right"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            addWriteProblem(b_jsonValueEachProblem["mark"].GetInt(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords);
            break;
        default:
            return false;
        }
    }
    return true;
}

int ProblemListModel::rowCount(const QModelIndex &parent) const
{
    return m_pProblemVecProList.size();
}

QVariant ProblemListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
//    if (role == Qt::DisplayRole)
//    {
        switch (m_pProblemVecProList[index.row()]->getType())
        {
        case SINGLE:
            return QString("单选题");
            break;
        case MULTIPLE:
            return QString("多选题");
            break;
        case JUDGEMENT:
            return QString("判断题");
            break;
        case WRITE:
            return QString("简答题");
            break;
        default:
            return QVariant();
        }
//    }
}

//QVariant ProblemListModel::headerData(int section,  Qt::Orientation orientation, int role) const
//{
//    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
//    {
//        return QString("题型");
//    }
//    return QAbstractListModel::headerData(section,orientation,role);

//}
