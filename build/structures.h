#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

struct Var
{
    Var(){};
    Var(std::string id,int size):id(id),size(size){};
    std::string id;
    int size;
};

struct Const
{
    Const(){};
    Const(std::string value):value(value){};
    std::string value;
};

union Expression
{
    char* str;
    int i;
};

struct Equation
{
    Equation(){};
    Equation(int type,std::string left,std::vector<Expression> right):type(type),left(left),right(right){};
    int type;
    std::string left;
    std::vector<Expression> right;
};

struct Program
{
    std::vector<Var> var;
    std::vector<std::string> input;
    std::vector<std::string> output;
    std::vector<Equation> equations;
    std::vector<Const> constants;
    std::map<std::string,int> var_dict;
};

Program* parse(char* filename);

#endif