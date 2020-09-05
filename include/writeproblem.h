/*
File Name: writeproblem.h
Description:
Author: unconsolable
*/

#ifndef WRITEPROBLEM_H
#define WRITEPROBLEM_H

#include "problem.h"
#include <vector>
#include <string>

class WriteProblem : public Problem
{
public:
    WriteProblem(double = 0, const std::string& = "", const std::vector<std::string>& = {});
    virtual double checkAnswer(const QVariant&) override;
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    virtual ~WriteProblem() = default;
private:
    std::vector<std::string> m_strVecKeyWords;
};

#endif // WRITEPROBLEM_H
