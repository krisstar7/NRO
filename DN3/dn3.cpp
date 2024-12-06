#include <iostream>
#include <cmath>

using namespace std;

double calcAtan(double x, int N_steps){
    int n = 0;
    double rez = 0;

    while (n<=N_steps){
        rez += pow(-1, n)*((pow(x, 2*n+1))/(2*n+1));
        n++;
    }

    return rez;
}

double func(double x, int N_steps){
    double rez;
    rez = exp(3*x)*calcAtan(x, N_steps);
    return rez;
}

int main(){

    double a = 0;
    double b = M_PI_4;

    int N_steps = 1000;

    int n = 1000;
    double dx = (b-a)/n;

    double sum = func(a, N_steps) + func(b, N_steps);

    for(int i=1; i<n; i++){
        sum += 2*func(i*dx, N_steps);
    }

    double rez = (dx/2)*sum;
    cout<<"Rezultat na integral e: "<<rez<<endl;

    return 0;
}