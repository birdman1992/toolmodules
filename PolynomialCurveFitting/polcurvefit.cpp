#include "polcurvefit.h"

struct point
{
    double x;
    double y;
};
vector<point> getFileInf(char *File);  //获取文件数据
doubleVector getCoeff(vector<point> sample, int n);   //矩阵方程

PolCurveFit::PolCurveFit()
{
    nFit=3;
}

doubleVector PolCurveFit::fitStart(vector<point> sample)
{
    return getCoeff(sample, nFit);
}

void PolCurveFit::test()
{
    int i, n;
    char *File = "样本.txt";
    vector<point> sample;
    doubleVector Coef;
    sample = getFileInf(File);
    printf("拟合阶数n：");
    scanf("%d", &n);

    Coef = getCoeff(sample, n);

    printf("\n拟合矩阵的系数为：\n");
    for(i=0; i<Coef.size(); i++)
        printf("a%d = %lf\n", i, Coef[i]);
}

//矩阵方程
doubleVector PolCurveFit::getCoeff(vector<point> sample, int n)
{
    vector<doubleVector> matFunX;  //矩阵方程
    vector<doubleVector> matFunY;  //矩阵方程
    doubleVector temp;
    double sum;
    int i, j, k;

    //正规方程X
    for(i=0; i<=n; i++)
    {
        temp.clear();
        for(j=0; j<=n; j++)
        {
            sum = 0;
            for(k=0; k<sample.size(); k++)
                sum += pow(sample[k].x, j+i);
            temp.push_back(sum);
        }

        matFunX.push_back(temp);
    }

    //正规方程Y
    for(i=0; i<=n; i++)
    {
        temp.clear();
        sum = 0;
        for(k=0; k<sample.size(); k++)
            sum += sample[k].y*pow(sample[k].x, i);
        temp.push_back(sum);

        matFunY.push_back(temp);
    }

    //矩阵行列式变换
    double num1, num2, ratio;

    for(i=0; i<matFunX.size()-1; i++)
    {
        num1 = matFunX[i][i];
        for(j=i+1; j<matFunX.size(); j++)
        {
            num2 = matFunX[j][i];
            ratio = num2/num1;
            for(k=0; k<matFunX.size(); k++)
                matFunX[j][k] = matFunX[j][k]-matFunX[i][k]*ratio;
            matFunY[j][0] = matFunY[j][0]-matFunY[i][0]*ratio;
        }
    }

    //计算拟合曲线的系数
    doubleVector coeff(matFunX.size(), 0);
    for(i=matFunX.size()-1; i>=0; i--)
    {
        if(i==matFunX.size()-1)
            coeff[i] = matFunY[i][0]/matFunX[i][i];
        else
        {
            for(j=i+1; j<matFunX.size(); j++)
                matFunY[i][0] = matFunY[i][0]-coeff[j]*matFunX[i][j];
            coeff[i] = matFunY[i][0]/matFunX[i][i];
        }
    }

    return coeff;
}




//获取文件数据
vector<point> PolCurveFit::getFileInf(char *File)
{
    int i=1;
    vector<point> dst;


    FILE *fp = fopen(File, "r");


    if(fp==NULL)
    {
        printf("Open file error!!!\n");
        exit(0);
    }


    point temp;
    double num;


    while(fscanf(fp, "%lf", &num)!=EOF)
    {
        if(i%2==0)
        {
            temp.y = num;
            dst.push_back(temp);
        }
        else
            temp.x = num;
        i++;
    }


    fclose(fp);


    return dst;
}
