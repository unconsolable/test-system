/*
File Name: writeproblem.h
Description: Define the class of the write problem
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
    const std::vector<std::string>& getKeyWords() const;
    void setKeyWords(const std::vector<std::string> &keyWords);

private:
    std::vector<std::string> m_strVecKeyWords;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(WriteProblem);

#endif // WRITEPROBLEM_H
