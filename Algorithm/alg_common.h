#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define ALG_NAMESPACE_BEG namespace alg {
#define ALG_NAMESPACE_END };
#define ALG_NAMESPACE_USE using namespace alg;

#undef  TRUE
#define TRUE        1

#undef  FALSE
#define FALSE       0

#undef  OK
#define OK          1

#undef  ERROR
#define ERROR       0

#undef  INFEASIBLE
#define INFEASIBLE  -1

#undef  OVERFLOW
#define OVERFLOW    -2

typedef int Status;