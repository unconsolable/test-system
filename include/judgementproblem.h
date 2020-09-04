/*
File Name: judgementproblem.h
Description: Define the Class JudgementProblem
Author: unconsolable
*/
#ifndef JUDGEMENTPROBLEM_H
#define JUDGEMENTPROBLEM_H

#include "problem.h"

class JudgementProblem : public Problem
{
public:
    JudgementProblem(int = 0, const std::string& = "", bool = true);
private:
    bool m_boolRightAns;
};

#endif // JUDGEMENTPROBLEM_H
