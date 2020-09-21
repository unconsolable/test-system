/*
文件名: writeproblem.h
版本: 1.0
目的与主要功能: 实现简答题类
创建日期: 2020.9.4
描述: 实现简答题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/
#include "writeproblem.h"

/***************************
 * Name:
 *   WriteProblem
 * Input:
 *   _mark 分值
 *   _desc 题干
 *   _keyWords 关键词组
 * Return:
 *   none
 * Description:
 *   构造简答题
 ***************************/

/***************************
 * Name:
 *   WriteProblem
 * Input:
 *   _mark 分值
 *   _desc 题干
 *   _keyWords 所有关键词
 * Return:
 *   none
 * Description:
 *   构造简答题
 ***************************/

WriteProblem::WriteProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords):
    Problem(WRITE, _mark, _desc), m_strVecKeyWords(_keyWords)
{

}

/***************************
 * Name:
 *   checkAnswer
 * Input:
 *   ans 存储答案的QVariant
 * Return:
 *   double
 * Description:
 *   计算得分
 ***************************/

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

/***************************
 * Name:
 *   toJsonValue
 * Input:
 *   doc 提供Allocator的Document
 * Return:
 *   rapidjson::value
 * Description:
 *   将判断题转为JSON数据节点
 ***************************/

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

/***************************
 * Name:
 *   getKeyWords
 * Input:
 *   keyWords
 * Return:
 *   none
 * Description:
 *   返回关键词组
 ***************************/

const std::vector<std::string> &WriteProblem::getKeyWords() const
{
    // 返回关键词
    return m_strVecKeyWords;
}

/***************************
 * Name:
 *   setKeyWords
 * Input:
 *   keyWords
 * Return:
 *   none
 * Description:
 *   设置关键词组
 ***************************/

void WriteProblem::setKeyWords(const std::vector<std::string> &keyWords)
{
    // 设置关键词
    m_strVecKeyWords = keyWords;
}
