
#include "rsa.h"

//Pollard Rho

//funcion f



ZZ f(ZZ x)
{
    ZZ c=to_ZZ("1");
    return x*x+c;
}


ZZ pollard_rho(ZZ N){
    ZZ a,b, d;
    a=to_ZZ("2");
    b=to_ZZ("2");
    
    if(N>>1==0){return to_ZZ("2");}
    
    do{
        a=modulo_for_ZZ(f(a),N);
        b=modulo_for_ZZ(f(b),N);
        b=modulo_for_ZZ(f(b),N);
        d=gcd_binary((abs(a-b)), N);
        cout<<d<<endl;
        if( conv<ZZ>(1)<d && d<N){
            return d;
        }
        if(d==N) conv<ZZ>(0);
    }
    while (d==1);
    
    
    return N;
}


ZZ phi_euler (ZZ numero){

    ZZ arra [1000][1000];

//    for(ZZ i=to_ZZ("2");i<SqrRoot(numero);i++){
        
    
  //  }
    
    return numero;
}



int main(int argc, const char * argv[]) {
    

    //phi_euler(to_ZZ("125"));
    
    /*
    
    RSA objeto(1024);
    
    ZZ numero;
    numero=conv<ZZ>(4096);
    cout<<"Numero a cifrar : "<<numero<<endl;
    ZZ c=objeto.cifrado(numero);
    objeto.descifrado(c);
    
    cout<<endl<<GetTime()<<endl;
    */
 
    
    //cout<<inversa(conv<ZZ>(3), conv<ZZ>(899464))<<endl;
    

    //cout<<inversa(conv<ZZ>(3), conv<ZZ>(4));
    //cout<<modulo_for_ZZ(to_ZZ("680"), to_ZZ("77"));
    //cout<<expo_modular_rapida_II(conv<ZZ>(81), conv<ZZ>(17), conv<ZZ>(77))<<endl;
    //cout<<inversa(to_ZZ("8"), to_ZZ("77"))<<endl;
    /*
    RSA o(8);
    ZZ a;
    a=o.fi_N;
    cout<<a<<endl<<endl;
    ZZ p;
    p=pollard_rho(a);
    ZZ ot;
    ot=a/p;
    cout<<"HACIENDO PAUSAA "<<endl<<endl<<a<<endl;
    cout<<endl<<endl<<ot<<endl;
    */
    
    //cout<<ProbPrime(to_ZZ("53"));
    

    
    
    
    RSA objet_1(256);
    
    string cifrado = objet_1.cifrado_bloques("Hey there, what happened , ARE YOU OK !!Hey there, what happened , ARE YOU OK !!Hey there, what happened , ARE YOU OK !!Hey there, what happened CAPITAN");
    cout<<endl<<endl<<endl<<cifrado<<endl;
    cout<<endl<<endl<<endl;
    //objet_1.DES_cifrado_bloques(cifrado);
    //string cifrado=objet_1.cifrado_texto("Kasparette");
    //cout<<"palabra cifrada es : "<<cifrado<<endl<<endl;
    //objet_1.des_cifrado_texto(cifrado);
    //objet_1.des_cifrado_texto_II(cifrado);
    
    cout<<endl<<GetTime()<<endl;
    
    return 0;
}