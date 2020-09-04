/*
File Name: judgementproblem.cpp
Description: Implement the class JudgementProblem
Author: unconsolable
*/

#include "judgementproblem.h"

JudgementProblem::JudgementProblem(int _mark, const std::string& _desc, bool _right):
    Problem(JUDGEMENT, _mark, _desc), m_boolRightAns(_right)
{

}
