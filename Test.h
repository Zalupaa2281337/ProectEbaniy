//
// Created by 1 on 20.11.2021.
//

#ifndef HELLOSFML_TEST_H
#define HELLOSFML_TEST_H

#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

//аннуитетный платеж
double AnP(double x, int n, double k)
{
    return x * (k/(1- pow(1+k,-n)));
}

//Вывод аннуитетного платежа
void OutAnP(double x, int n, double k)
{
    k = k/(12*100);

    double p = AnP(x,n,k);
    double l = p*n - x;
    cout<< "Месяцы|" << "   " << "|Остаток задолженности|   "<< "|Выплата   |"<<endl;
    for(int i = 2; i <= n; ++i)
    {
        x = x*(1+k);
        x = x - p;
        cout<< i << string(6 - to_string(i).length(),' ')<<'|'<<"   " << setprecision(1) << fixed <<'|'<<  x << string( 26 - to_string(double(x)).length(),' ') <<'|'<<"   "<<'|'<<p<<"   |"<<endl;
    }
    cout<<"Переплата составит:  "<< l <<endl;
}

//Вывод дифферинцированного платежа
void OutDifP(double x, int n, double k)
{
    k = k/(12*100);

    double itplt; //Итоговый платеж
    double osnplt = x/n; //Основной платеж
    const double x_c = x;
    double sum;
    cout<< "Месяцы|" << "   " << "|Остаток задолженности|   "<< "|Основная выплата|   "<< "|Итоговая выплата|"<<endl;
    for(int i = 1; i<=n; ++i)
    {
        itplt = x_c/n + (x_c - x_c/n*(i-1))*k;
        sum+=itplt;
        cout<<i<<string(6 - to_string(i).length(),' ')<<'|' << "   "<< setprecision(1) << fixed <<'|'<<x<<string( 26 - to_string(double(x)).length(),' ')<< '|' << "   "<< setprecision(1) << fixed<<'|'<<osnplt<<string( 21 - to_string(double(x_c/n)).length(),' ')<<'|'<<"   "<<'|'<<itplt<<"        |"<<endl;
        x-=osnplt;

    }
    cout<<"Переплата составит:  "<< sum-x_c <<endl;
}

//Создает map в которм храянтся значения месяца и соответствующего остатка долга
// Для дифференцируемого платежа
map<int,double> MakeDifp(double x, int n, double k)
{
    map<int,double> mp;
    k = k/(12*100);
    double itplt; //Итоговый платеж
    double osnplt = x/n; //Основной платеж
    const double x_c = x;
    double sum;
    for(int i = 1; i<=n; ++i)
    {
        itplt = x_c/n + (x_c - x_c/n*(i-1))*k;
        sum+=itplt;
        mp[i-1] = x;
        x-=osnplt;

    }
    return mp;
}

//Создает map в которм храянтся значения месяца и соответствующего остатка долга
// для Аннуитетного
map<int,double> MakeAnp(double x, int n, double k)
{
    k = k/(12*100);
    map<int,double> mp;
    double p = AnP(x,n,k);
    double l = p*n - x;
    for(int i = 2; i <= n; ++i)
    {
        x = x*(1+k);
        x = x - p;
        mp[i] = x;
    }
    return mp;
}



#endif //HELLOSFML_TEST_H
