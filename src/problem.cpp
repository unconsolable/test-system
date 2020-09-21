/*
文件名: problem.h
版本: 1.0
目的与主要功能: 实现问题类
创建日期: 2020.9.2
描述: 实现问题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "problem.h"

/***************************
 * Name:
 *   Problem
 * Input:
 *   _ty 题目类型
 *   _mark 题目分值
 *   _desc 题目描述
 * Return:
 *   none
 * Description:
 *   构造问题类
 ***************************/

Problem::Problem(problemType _ty, double _mark, const std::string& _desc)
    :m_problemTy(_ty), m_doubleMark(_mark), m_strDescription(_desc)
{

}

/***************************
 * Name:
 *   toJsonValue
 * Input:
 *   doc 提供Allocator的Document
 * Return:
 *   rapidjson::value
 * Description:
 *   将通用信息转为JSON数据节点
 ***************************/

rapidjson::Value Problem::toJsonValue(rapidjson::Document& doc) const
{
    // 定义用于返回的JSON节点
    rapidjson::Value problem(rapidjson::kObjectType);
    // 序列化基类的数据成员:题目类型,
    problem.AddMember("type",static_cast<int>(m_problemTy),doc.GetAllocator());
    // 分数,
    problem.AddMember("mark",m_doubleMark,doc.GetAllocator());
    // 用于存储题干
    rapidjson::Value b_jsonValueDescription;
    // 设置字符串
    b_jsonValueDescription.SetString(m_strDescription.c_str(),m_strDescription.size(), doc.GetAllocator());
    // 添加描述
    problem.AddMember("description",b_jsonValueDescription, doc.GetAllocator());
    return problem;
}

/***************************
 * Name:
 *   getMark
 * Input:
 *   none
 * Return:
 *   double
 * Description:
 *   返回分值
 ***************************/

double Problem::getMark() const
{
    return m_doubleMark;
}

/***************************
 * Name:
 *   setMark
 * Input:
 *   doubleMark 分值
 * Return:
 *   none
 * Description:
 *   设置分值
 ***************************/

void Problem::setMark(double doubleMark)
{
    m_doubleMark = doubleMark;
}

/***************************
 * Name:
 *   setType
 * Input:
 *   ty
 * Return:
 *   none
 * Description:
 *   设置题目类型
 ***************************/

void Problem::setType(problemType ty)
{
    m_problemTy = ty;
}

/***************************
 * Name:
 *   setType
 * Input:
 *   none
 * Return:
 *   problemType
 * Description:
 *   获取题目类型
 ***************************/

problemType Problem::getType() const
{
    return m_problemTy;
}

/***************************
 * Name:
 *   getType
 * Input:
 *   none
 * Return:
 *   const std::string&
 * Description:
 *   获取题干
 ***************************/

const std::string &Problem::getDescription() const
{
    return m_strDescription;
}

/***************************
 * Name:
 *   setType
 * Input:
 *   Description 题干
 * Return:
 *   none
 * Description:
 *   获取题干
 ***************************/

void Problem::setDescription(const std::string &Description)
{
    m_strDescription = Description;
}

/***************************
 * Name:
 *   convertType
 * Input:
 *   none
 * Return:
 *   const char*
 * Description:
 *   根据题目类型返回为对应字符串
 ***************************/

const char* Problem::convertType() const
{
    // 根据类型转换为对应字符串
    switch (m_problemTy)
    {
    case SINGLE:
        return "单选题";
        break;
    case MULTIPLE:
        return "多选题";
        break;
    case JUDGEMENT:
        return "判断题";
        break;
    case WRITE:
        return "简答题";
        break;
    default:
        return "(题目类型解析错误)";
    }
}

