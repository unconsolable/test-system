#include "writeproblem.h"

WriteProblem::WriteProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords):
    Problem(WRITE, _mark, _desc), m_strVecKeyWords(_keyWords)
{

}

double WriteProblem::checkAnswer(const QVariant & ans)
{
    std::string b_stdStringWriteAns = ans.toString().toStdString();
    double b_doubleEveryKeyWordMark = m_doubleMark / m_strVecKeyWords.size();
    double b_doubleTotalMark = 0;
    for (const auto& b_strEachKeyWord : m_strVecKeyWords)
    {
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
    for (const auto& i : m_strVecKeyWords)
    {
        keyWord.PushBack(i, doc.GetAllocator());
    }
    problem.AddMember("right",keyWord,doc.GetAllocator());
    return problem;
}
