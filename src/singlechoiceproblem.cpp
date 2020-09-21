/*
文件名: singlechoiceproblem.h
版本: 1.0
目的与主要功能: 实现单选题类
创建日期: 2020.9.3
描述: 实现单选题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "singlechoiceproblem.h"

SingleChoiceProblem::SingleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right):
    ChoiceProblem(SINGLE, _mark, _desc, _ansList), m_charRightAns(_right)
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

double SingleChoiceProblem::checkAnswer(const QVariant& ans)
{
    // 判断选择的字符是否相符
    if (m_charRightAns == ans.toChar())
        return m_doubleMark;
    else
        return 0;
}

/***************************
 * Name:
 *   toJsonValue
 * Input:
 *   doc 提供Allocator的Document
 * Return:
 *   rapidjson::value
 * Description:
 *   将单选题转为JSON数据节点
 ***************************/

rapidjson::Value SingleChoiceProblem::toJsonValue(rapidjson::Document& doc) const
{
    // 获得已经构建的成果
    auto problem = ChoiceProblem::toJsonValue(doc);
    // 选项在JSON里会变成数字
    problem.AddMember("right",m_charRightAns,doc.GetAllocator());
    return problem;
}

/***************************
 * Name:
 *   getRightAns
 * Input:
 *   none
 * Return:
 *   char
 * Description:
 *   返回正确答案
 ***************************/

char SingleChoiceProblem::getRightAns() const
{
    // 返回正确答案
    return m_charRightAns;
}

/***************************
 * Name:
 *   setRightAns
 * Input:
 *   rightAns
 * Return:
 *   none
 * Description:
 *   设置正确答案
 ***************************/

void SingleChoiceProblem::setRightAns(char rightAns)
{
    // 设置正确答案
    m_charRightAns = rightAns;
}
