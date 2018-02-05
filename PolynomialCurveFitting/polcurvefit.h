#ifndef POLCURVEFIT_H
#define POLCURVEFIT_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct point;
typedef vector<double> doubleVector;

class PolCurveFit
{
public:
    explicit PolCurveFit();
    doubleVector fitStart(vector<point> sample);//开始拟合

private:
    int nFit;//拟合阶数
    doubleVector Coef;

    void test();
    doubleVector getCoeff(vector<point> sample, int n);
    vector<point> getFileInf(char *File);
};

#endif // POLCURVEFIT_H
