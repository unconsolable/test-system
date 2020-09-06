/*
File Name: problem.cpp
Description: Implement class Problem
Author: unconsolable
*/

#include "problem.h"

Problem::Problem(problemType _ty, double _mark, const std::string& _desc)
    :m_problemTy(_ty), m_doubleMark(_mark), m_strDescription(_desc)
{

}

rapidjson::Value Problem::toJsonValue(rapidjson::Document& doc) const
{
    rapidjson::Value problem(rapidjson::kObjectType);
    // 序列化基类的数据成员:题目类型,分数,描述
    problem.AddMember("type",static_cast<int>(m_problemTy),doc.GetAllocator());
    problem.AddMember("mark",m_doubleMark,doc.GetAllocator());
    rapidjson::Value b_jsonValueDescription;
    b_jsonValueDescription.SetString(m_strDescription.c_str(),m_strDescription.size(), doc.GetAllocator());
    problem.AddMember("description",b_jsonValueDescription, doc.GetAllocator());
    return problem;
}

double Problem::getMark() const
{
    return m_doubleMark;
}

void Problem::setMark(double doubleMark)
{
    m_doubleMark = doubleMark;
}

void Problem::setType(problemType ty)
{
    m_problemTy = ty;
}

problemType Problem::getType() const
{
    return m_problemTy;
}

std::string Problem::getDescription() const
{
    return m_strDescription;
}

void Problem::setDescription(const std::string &Description)
{
    m_strDescription = Description;
}

const char* Problem::convertType() const
{
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

