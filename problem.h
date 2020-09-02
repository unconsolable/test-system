#ifndef PROBLEM_H
#define PROBLEM_H

enum problemType
{
    SINGLE,
    MULTIPLE,
    TORF,
    WRITE,
};

class Problem
{
public:
    Problem(problemType _ty):ty(_ty) {}
private:
    problemType ty;
};

#endif // PROBLEM_H
