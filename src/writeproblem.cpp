/*
File Name: writeproblem.cpp
Description: Implement the class for WriteProblem
Author: unconsolable
*/
#include "writeproblem.h"

WriteProblem::WriteProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords):
    Problem(WRITE, _mark, _desc), m_strVecKeyWords(_keyWords)
{

}

double WriteProblem::checkAnswer(const QVariant & ans)
{
    std::string b_stdStringWriteAns = ans.toString().toStdString();
    // 计算每个选项的得分
    double b_doubleEveryKeyWordMark = m_doubleMark / m_strVecKeyWords.size();
    double b_doubleTotalMark = 0;
    for (const auto& b_strEachKeyWord : m_strVecKeyWords)
    {
        // 如果能够找到关键字则给分
        if (b_stdStringWriteAns.find(b_strEachKeyWord) != std::string::npos)
        {
            b_doubleTotalMark += b_doubleEveryKeyWordMark;
        }
    }
    return b_doubleTotalMark;
}

rapidjson::Value WriteProblem::toJsonValue(rapidjson::Document &doc) const
{
    auto problem = Problem::toJsonValue(doc);
    rapidjson::Value keyWord(rapidjson::kArrayType);
    // 将每个关键词写入JSON Array中
    for (const auto& b_strEachKeyWord : m_strVecKeyWords)
    {
        rapidjson::Value choice;
        // 存储关键词string
        choice.SetString(b_strEachKeyWord.c_str(), b_strEachKeyWord.size(), doc.GetAllocator());
        // 尾后附加
        keyWord.PushBack(choice, doc.GetAllocator());
    }
    // 将Array与对应Key写入JSON值中
    problem.AddMember("right", keyWord, doc.GetAllocator());
    return problem;
}

const std::vector<std::string> &WriteProblem::getKeyWords() const
{
    // 返回关键词
    return m_strVecKeyWords;
}

void WriteProblem::setKeyWords(const std::vector<std::string> &keyWords)
{
    // 设置关键词
    m_strVecKeyWords = keyWords;
}
