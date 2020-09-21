/*
文件名: multiplechoiceproblem.h
版本: 1.0
目的与主要功能: 实现多选题类
创建日期: 2020.9.3
描述: 实现多选题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "multiplechoiceproblem.h"

MultipleChoiceProblem::MultipleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right):
    ChoiceProblem(MULTIPLE, _mark, _desc, _ansList), m_charVecRightAns(_right)
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

double MultipleChoiceProblem::checkAnswer(const QVariant & ans)
{
    // 转为QVector类型存储
    auto b_qVariantVecAns = ans.value<QVector<QVariant>>();
    // 每个选项的分数
    double b_doubleChoiceMark = m_doubleMark / m_charVecRightAns.size();
    // 获得的总分
    double b_doubleTotalMark = 0;
    // 每个选项遍历
    for (const auto& b_qVariantChoice : b_qVariantVecAns)
    {
        // 和正确选项核对
        for (const auto& b_charRightChoice : m_charVecRightAns)
        {
            if (b_qVariantChoice.toChar() == b_charRightChoice)
            {
                // 找到匹配选项时加分
                b_doubleTotalMark += b_doubleChoiceMark;
                break;
            }
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

rapidjson::Value MultipleChoiceProblem::toJsonValue(rapidjson::Document& doc) const
{
    // 先获得选则题转为的JSON节点
    auto problem = ChoiceProblem::toJsonValue(doc);
    // 存储多选正确选项组
    rapidjson::Value answer(rapidjson::kArrayType);
    // 添加多选选项,选项用char表示,应转为int存
    for (const auto& b_charEachRight: m_charVecRightAns)
    {
        // 某个正确选项
        rapidjson::Value choice;
        // 设置其数字
        choice.SetInt(b_charEachRight);
        // 正确选项组尾后附加
        answer.PushBack(choice, doc.GetAllocator());
    }
    // 节点尾后附加正确答案组
    problem.AddMember("right", answer, doc.GetAllocator());
    return problem;
}

/***************************
 * Name:
 *   getRightAns
 * Input:
 *   none
 * Return:
 *   const std::vector<char>&
 * Description:
 *   返回正确答案组
 ***************************/

const std::vector<char>& MultipleChoiceProblem::getRightAns() const
{
    return m_charVecRightAns;
}

/***************************
 * Name:
 *   setRightAns
 * Input:
 *   rightAns
 * Return:
 *   none
 * Description:
 *   设置正确答案组
 ***************************/

void MultipleChoiceProblem::setRightAns(const std::vector<char> &rightAns)
{
    m_charVecRightAns = rightAns;
}
