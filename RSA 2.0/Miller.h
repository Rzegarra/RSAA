#include <iostream>
#include <NTL/ZZ.h>
#include <bitset>
#include <vector>
#include <math.h>
#include <stdio.h>
#include "Miller.h"


using namespace NTL;
using namespace std;

ZZ fun(ZZ a,ZZ n,ZZ k){

    ZZ b=conv<ZZ>(1);
    bitset<4096> f(conv<int>(k));
    int iteracion=log2(conv<int>(k));

    ZZ  A=a;
    if (f[0] ==1){
        b=a;
    }
    for (int i=1;i<=iteracion;i++){
        A=power(A, 2);
        A=A%n;
//        A= PowerMod(A, 2, n); // z = x^m % n
        if (f[i]==1){
            b=(A*b)%n;
        }
    }
    //cout<<b<<endl;
    return b;
}

vector<ZZ> values;
void factorizacion_normal(int numero){

        // Print the number of 2s that divide n
        while (numero%2 == 0)
        {
            printf("%d ", 2);
            numero = numero/2;
        }

        // n must be odd at this point.  So we can skip one element (Note i = i +2)
        for (int i = 3; i <= sqrt(numero); i = i+2)
        {
            // While i divides n, print i and divide n
            while (numero%i == 0)
            {
                printf("%d ", i);
                numero = numero/i;
            }
        }

        // This condition is to handle the case whien n is a prime number
        // greater than 2
        if (numero > 2)
            printf ("%d ", numero);

}

bool Test_bin(vector<ZZ> X,ZZ num)
{
    ZZ D=conv<ZZ>(1);
    ZZ A=conv<ZZ>(rand()%1024);
    for(int i=0;i<X.size();i++)
    {
        ZZ Y=D;
        D=mod(D*D,num);
        if(D==1 && Y!=1 && Y!=num-1)
            return false;
        if(X.at(i)==1)
            D=mod(D*A,num);
        A=conv<ZZ>(rand()%1024);
    }
        if(D!=1)
            return false;
    return true;
}
bool Test_Miller(ZZ p,int iteration){
    if(p<2){
        return false;
    }
    if(p!=2 && mod(p,conv<ZZ>(2))==0 && mod(p,conv<ZZ>(5))==0 && mod(p,conv<ZZ>(9))==0){
        return false;
    }
    ZZ s=p-1;
    while(modzz(s,conv<ZZ>(2))==0){
        s=s/2;
    }
    for(int i=0;i<iteration;i++){
        ZZ a=to_ZZ(rand())%(p-1)+1,temp=s;
        ZZ mod=ExpRS(a,temp,p);
        
        while(temp!=p-1 && mod!=1 && mod!=p-1){
            mod=modzz(mod*mod,p);
            temp *= 2;
        }
        if(mod!=p-1 && modzz(temp,conv<ZZ>(2))==0){
            return false;
        }
    }
    return true;
}
