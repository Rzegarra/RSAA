//
//  lfsr.cpp
//  LFSR
//
//  Created by Alexander Arturo Baylon Ibanez on 9/16/14.
//  Copyright (c) 2014 Alexander Arturo Baylon Ibanez. All rights reserved.
//



#include "lfsr.h"

cadena::cadena(int t,int s,int p,int tp,bool dir)
{
    tam_bits    = t;
    sem         = s;
    num_part    = p;
    num_taps    = tp;
    direccion   = dir;
    tam_part    = tam_bits/num_part;
    pibot       = tam_bits/num_taps;
    resultado       = 4;
    resultado_tmp   = 0;
    
    generar_semilla();
    generar_cadena();
    generar_taps();
    iteraciones();
}



int cadena::num_rand(int x,int y)
{
    return (rand()%x)+y;
}


void a_binario(unsigned x)
{
    string a;
    // Mientras el numero no sea 0 al dividirlo entre 2( >>1 ).
    do
    {   // agregamos a la cadena el bit menos significativo de x con (x&1);
        a.push_back('0' + (x & 1));
    } while (x >>= 1);
    reverse(a.begin(), a.end());
    cout << a << endl;
}

void cadena::generar_semilla()
{
    for (int tmp, i = 0; i < sem; i++) {
        tmp = num_rand(99,1);
        if (tmp & 1)
            a.push_back('0');
        else
            a.push_back('1');
    }
}

void cadena::generar_cadena()
{
    for (long j=0; j < (tam_bits-sem); j++) {
        bool uno = a[j]-'0', dos = a[j+1]-'0';
        a.push_back((uno^dos)+'0');
    }
   
}

void cadena::generar_taps()
{
    int dist = pibot;
    for (int i = 0,j = 0, tmp; i < num_taps; i++,j+=dist) {
        tmp = num_rand(dist, 0) + j;
        pos_taps.push_back(tmp);
    }
}

bool cadena::suma_taps()
{
    bool res = a[pos_taps[0]] - '0';
    for (int i=1; i < num_taps; i++) {
        res = res ^ (a[pos_taps[i]] - '0');
    }
    return res;
}


void cadena::shift_izq(int i,int f)
{
    // Hallamos la suma de los valores en los taps actuales y lo sumamos al valor que estamos eliminando.
    bool temp = suma_taps() ^ (a[i]-'0');
    for (int j=i; j<f; j++)
        a[j] = a[j+1];  // Copiamos todos los valores a una posicion anterior, simulando el shift.
    a[f] = temp + '0';
    direccion = 1;
}

void cadena::shift_der(int i,int f)
{
    // Hallamos la suma de los taps actuales y le sumamos la ultima posicion del intervalo.
    bool temp = suma_taps() ^ (a[f]-'0');
    for (int j=f; j>i; j--)
        a[j] = a[j-1];
    a[i] = temp + '0';
    direccion = 0;
}

void cadena::iteraciones()
{
    bool temp = false;
    while(!fermaTest(resultado)) {
        resultado = 0;
        for (int j = 0,ini=0,fin=tam_part-1; j < num_part; j++,ini+=tam_part,fin+=tam_part) {
            if (j==num_part-1)   fin = tam_bits-1;
            if(direccion==1) {
                temp = a[fin] - '0';
                shift_der(ini,fin);
            }
            else{
                temp = a[ini] - '0';
                shift_izq(ini,fin);
            }
            for (int k = 0; k < num_taps; k++) {
                for (int l = ini; l <= fin ; l++) {
                    if (pos_taps[k]==l){
                        a[l] = ((a[l]-'0') ^ temp)+'0';
                        break;
                    }
                }
            }
        }
        a[a.size()-1] = '1';
        a_entero();
    }
}

void cadena::a_entero()
{
    // Sacamos cada bit de la cadena principal y hacemos una comparacion(or) con "resultado" que primeramente es 0;
    for (char c : a){
        // Haciendo un shift hacia la izquierda guardara cada bit en la variable.
        //cout << resultado << endl;
        resultado = resultado << 1;
        resultado = resultado | (c - '0');
    }
}

ZZ cadena::a_entero_tmp()
{
    // Sacamos cada bit de la cadena principal y hacemos una comparacion(or) con "resultado" que primeramente es 0;
    for (char c : a){
        // Haciendo un shift hacia la izquierda guardara cada bit en la variable.
        //cout << resultado << endl;
        resultado_tmp = resultado_tmp << 1;
        resultado_tmp = resultado_tmp | (c - '0');
    }
    return resultado;
}

void cadena::resetear()
{
    resultado       = 4;
    resultado_tmp   = 0;
    iteraciones();
}



void cadena::imprimir_cadena()
{
    for (int i=0,j=tam_part-1,k=1; i<tam_bits; i++) {
        cout << a[i];
        if (j==i) {
            cout << " ";
            j+=tam_part;
            k++;
        }
        if (k==num_part) {
            j=0;
        }
    }
    cout << endl;
}

int ingresar_valor(string c)
{
    int a;
    cout << "Ingrese el " << c; cin >> a;
    return a;
}

void pausa()
{
    cout << "Presione una tecla para continuar.... ";
    cin.ignore().get();
}

//Exponenciacion Modular
//Input: base, exponente, modulo
//Output: base^exponente % modulo
/*
ZZ fastermod(ZZ factor,ZZ power,ZZ modulo){
    ZZ result;
    result = result + 1;
    while(power > 0){
        if (power % 2 == 1){
            result = (result*factor) % modulo;
            power = power-1;
        }
        power = power/2;
        factor = (factor*factor)%modulo;
    }
    return result;
};
*/

ZZ mcd(ZZ x,ZZ y){
    ZZ z;
    while ( y != 0 ) {
        z = x % y;
		x = y;
		y = z;
	}
	return x;
};

//Test de Fermat
//Input: un numero entero (numtest)
//Output: TRUE si es primo, FALSE si es compuesto

bool fermaTest(ZZ inputNum){
	ZZ randTest;
    randTest = 0;
   	bool result = true;
   	// Itera el numero de veces definida en numTrials.
   	for (int trial = 0; trial < 20; trial++){
        
        // generamos un numero entre 1 y inputNum - 1
        //randTest = (rand() % inputNum-2) + 2;
        while(randTest==0){
            randTest = RandomBnd(inputNum);
        }
        //cout << randTest << endl;
        // verificamos si existe un factor comun diferente de 1 entre los numeros.
        if ( mcd(randTest,inputNum) != 1){
            // si encontramos un factor entonces es compuesto.
            result = false;
            return result;
        }
        // fermat test
        if (PowerMod(randTest,inputNum-1,inputNum) != 1){
            // si se cumple esta condicion es un numero compuesto
            result = false;
            return result;
        }
        randTest = 0;
 	}
   	result = true;
   	return result;
};




