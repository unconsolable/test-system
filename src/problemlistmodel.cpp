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
std::string ProblemListModel::toJsonString() const
{
    rapidjson::Document b_jsonTestPaper;
    rapidjson::Value b_jsonProblemList;
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
    if (!doc.HasMember("problem") || !doc["problem"].IsArray())
    {
        return false;
    }
    for (auto& v : doc["problem"].GetArray())
    {
        std::vector<std::string> tmpAnsListOrKeyWords;
        std::vector<char> multipleChoice;
        switch (v["type"].GetInt())
        {
        case SINGLE:
            for (auto& i: doc["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            addSingleChoiceProblem(v["mark"].GetInt(), std::string(v["description"].GetString()), tmpAnsListOrKeyWords, v["right"].GetInt());
            break;
        case MULTIPLE:
            for (auto& i: doc["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            for (auto& i:doc["right"].GetArray())
            {
                multipleChoice.emplace_back(i.GetString());
            }
            addMultipleChoiceProblem(v["mark"].GetInt(), std::string(v["description"].GetString()), tmpAnsListOrKeyWords, multipleChoice);
            break;
        case JUDGEMENT:
            addJudgementProblem(v["mark"].GetInt(), std::string(v["description"].GetString()),v["right"].GetBool());
            break;
        case WRITE:
            for (auto& i:doc["right"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            addWriteProblem(v["mark"].GetInt(), std::string(v["description"].GetString()), tmpAnsListOrKeyWords);
            break;
        default:
            return false;
        }
    }
    return true;
}


