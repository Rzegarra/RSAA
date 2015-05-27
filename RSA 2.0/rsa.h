#include <NTL/ZZ.h>
#include <iostream>
#include <regex>
#include <math.h>

#include <sstream>

#include "functions.h"


#ifndef RSA_2_0_rsa_h
#define RSA_2_0_rsa_h


using namespace NTL;
using namespace std;

ZZ gcd_binary(ZZ x, ZZ y){
    ZZ t; ZZ g;
    g=conv<ZZ>(1);
    
    while( (bit(x, 0)==0) && (bit(y, 0)==0)){ // evalua si ambos son pares
        x=x>>1; y=y>>1; g=g<<1;               // divide ambos entre 2
    }
    while(x!=0){
        while (bit(x,0)==0) x=x>>1;
        while (bit(y,0)==0) y=y>>1;
        t=abs(x-y)>>1;
        if(x>=y) x=t;
        else y=t;
    }
    return g*y;
}

ZZ binary_extended_gcd (ZZ x, ZZ y){
    
    ZZ g=to_ZZ("1");
    ZZ a;ZZ b;ZZ u;ZZ v;
    ZZ A=to_ZZ("1"), B=to_ZZ("0"), C=to_ZZ("0"),D=to_ZZ("1");
    
    while(((bit(x,0))==0) && ((bit(y,0))==0)){
        x=x>>1; y=y>>1; g=g<<1;
    }
    u=x;
    v=y;
step:
    while((bit(u,0))==0) {
        u=u>>1;
        if((bit(A,0)==0) && (bit(B,0)==0) ){
            A=A>>1; B=B>>1;
        }
        else {
            A=(A+y)>>1; B=(B-x)>>1;
        }
    }
    
    while((bit(v,0))==0) {
        v=v>>1;
        if((bit(D,0)==0) && (bit(C,0)==0) ){
            C=C>>1; D=D>>1;
        }
        else {
            C=(C+y)>>1; D=(D-x)>>1;
        }
    }
    
    if(u>=v){
        u=u-v;  A=A-C;  B=B-D;
    }
    else {
        v=v-u;  C=C-A;  D=D-B;
    }
    if(u==0){
        a=C;    b=D;    //cout<<"a es : "<<a<<" b es : "<<b<<" otro : "<<g*v<<endl;
        return a; // que es la inversa
    }
    else goto step;
}


ZZ inversa(ZZ n1, ZZ n2){
    ZZ ret = binary_extended_gcd(n1, n2);
    if(ret<0)
    {
        ret += n2;
    }
    return ret;
}




class RSA{

public:
    
    
    vector<int> algo;
    vector<ZZ> xxx;
    ZZ p;
    ZZ q;
    ZZ N;
    ZZ fi_N;
    ZZ e;
    ZZ d;
    
    ZZ numero_cifrado;
    ZZ numero_descifrado;
    ZZ bits_II;
    
    string abecedario="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:";
    
    RSA(int a, int b) {
        
        p=to_ZZ("1");
        q=p;
        N=to_ZZ("1451650761465387866207057735535821306864156710951859471670543113376853250566729");
        cout<<"N es "<<N<<endl;
        e=to_ZZ("235040151400800041545659945736902735271");
        cout<<"e es "<<e<<endl;

        d=to_ZZ("1242307535595943191407386589181976630453604707607890194998541627057343615178431");
        cout<<"d es "<<d<<endl;

       // imprimir();
    
    }
    RSA(int bits){
        
        if (bits>=8196) {
            p=funcion(8196, 91, 1000, 512, 20);
            q=funcion(8196, 91, 500, 16, 469);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(8196, 91, 500, 16, 469);
            //d=binary_extended_gcd(e, fi_N);
            d=inversa(e, fi_N);
            
            imprimir();
        }
        
        else if(bits>=4096 and bits<=8195 ){
            p=funcion(4096, 91, 1000, 512, 20);
            q=funcion(4096, 91, 1000, 512, 20);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(4093, 91, 1000, 512, 20);
            d=inversa(e, fi_N);
            
            
            imprimir();
        }
        
       else  if (bits>=2048 and bits<=4095) {
            p=funcion(2048, 91, 1000, 512, 20);
            
            q=funcion(2048, 91, 500, 16, 469);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(2043, 91, 500, 16, 469);
            //d=binary_extended_gcd(e, fi_N);
            d=inversa(e, fi_N);
            
            imprimir();
        }
        else if(bits<=2047  and bits>=1024 ){

            p=funcion(1024,13,20,16,5);
            q=funcion(1023,798,550,32,729);
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(1021,798,550,32,729);
            d=inversa(e, fi_N);
            
            imprimir();
        }
        else if(bits<=1023 and bits>=512 ){
            cout<<"EALSKDALSKJDLAKSJDL"<<endl<<endl<<endl<<endl;
            
            p=funcion(bits,99,500,16,259);
            q=funcion(bits,99,500,16,259);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(509,99,500,16,259);
            d=inversa(e, fi_N);
            
            imprimir();
        }

        else if(bits>=256 and bits<=511 ){
            p=funcion(256,13,20,16,5);
            q=funcion(255,91,505,64,247);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(253,129,20,16,5);
            d=inversa(e, fi_N);
            
            imprimir();
        }
        
        
       
        else if(bits>=128 and bits<=255){
            p=funcion(128,29,120,16,55);
            q=funcion(127,126,505,32,79);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(125,126,505,32,79);
            d=inversa(e, fi_N);
            
            imprimir();
        }
        

        else if(bits>=64 and bits<=127 ){
            p=funcion(64,15,500,8,5);
            q=funcion(62,38,387,8,37);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(57,38,387,8,37);
            d=binary_extended_gcd(e, fi_N);
            d=inversa(e, fi_N);
            
            imprimir();
            
        }
        
        else if(bits>=32 and bits<=65){
            p=funcion(32, 15, 5, 4, 5);
            q=funcion(32, 3, 126, 4, 19);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(29, 3, 126, 4, 19);
            d=inversa(e, fi_N);
            
            imprimir();
            
        }
        else if(bits>=16 and bits<=31 ){
            p=funcion(bits,14,7,2,5);
            q=funcion(bits,3,126,2,13);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=q=funcion(13,3,126,2,13);
            d=inversa(e, fi_N);
            
            imprimir();
        }
        //

        else if(bits>=8 and bits<=15){
            p=funcion(bits, 7, 15, 2, 6);
            q=funcion(bits, 3, 1000, 2, 6);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            e=funcion(7, 3, 1000, 2, 6);
        
            d=inversa(e, fi_N);
            
            imprimir();
        }
        else if(bits>=4 and bits<=7){
            p=funcion(bits, 2, 123, 2, 3);
            q=funcion(bits, 2, 1000, 1, 2);
            
            N=p*q;
            fi_N=(p-1)*(q-1);
            
            e=funcion(4, 2, 1000, 1, 3);
            d=inversa(e, fi_N);
            
            imprimir();
            
        }
        bits_II=conv<ZZ>(bits);
    }

    void imprimir(){
        cout<<"GCD de e y fi_n es "<<gcd_binary(e, fi_N)<<endl<<endl;
        cout<<"p es : "<<endl<<p<<endl<<endl<<"q es : "<<endl<<q<<endl<<endl;
        cout<<"Aleatorio es : "<<endl<<e<<endl<<endl;
        cout<<"Inverso de e es : "<<endl<<d<<endl<<endl;
        cout<<"N es : "<<endl<<N<<endl<<endl<<"fi_N es : "<<endl<<fi_N<<endl<<endl;// con esta media si
        numero_descifrado=conv<ZZ>(14);
        
    }
    
    
    // ESTA FUNCION NO SE PUEDE, porque no tengo suficiente hardware para factorizar numeros de 1024
    
    ZZ inversa_with_euler_theorem(ZZ base, ZZ modulo){
        
        return expo_modular_rapida_II(base, fi_N-1, modulo);

    }
    
    
    
    ZZ cifrado(ZZ numero){
        numero_cifrado=expo_modular_rapida_II(numero, e, N);
        cout<<endl<<"Numero Cifrado : "<<numero_cifrado<<endl<<endl;
        return numero_cifrado;
    }
    
    ZZ descifrado(ZZ numero){
        numero_descifrado=expo_modular_rapida_II(numero,d, N);
        cout<<"Numero Descifrado es : "<<numero_descifrado<<endl<<endl;
        return numero_descifrado;
    }
    
    string cifrado_texto(string palabra){
    
        
        algo.push_back(0);
        string almacen;
        cout<<"Palabra a cifrar es : "<<palabra<<endl;
        for(int i=0;i<palabra.length();i++){
            //cout<<abecedario.find(palabra[i]);
            ZZ numero;numero=abecedario.find(palabra[i]);
            ZZ cifrado=expo_modular_rapida_II(numero, e, N);
            stringstream ss;
            ss << cifrado;
            string str1 = ss.str();
            xxx.push_back(cifrado);
            almacen+=str1;

            algo.push_back(almacen.length());
            almacen+=',';
        }
        algo.push_back(almacen.length());
        cout<<almacen<<endl<<endl<<endl;
        return almacen;
    }

    string des_cifrado_texto(string palabra){
        
        
        const std::regex r("[0-9]+");
        ZZ Result ;
        Result=conv<ZZ>(0);
        ZZ descifrado;
        vector<ZZ> numeros;
        for (std::sregex_iterator N(palabra.begin(), palabra.end(), r); N != std::sregex_iterator(); ++N)
        {
            std::stringstream SS(*N->begin());
            ZZ Current;
            Current=conv<ZZ>(0);
            SS >> Current;
            Result = conv<ZZ>(Current);
            numeros.push_back(Result);
        }
        
        
        for(int i=0;i<numeros.size();i++){
            
            descifrado=expo_modular_rapida_II(numeros[i], d, N);
            int nn=conv<int>(descifrado);
            cout<<abecedario[nn];
        }
        
        
        cout<<endl<<endl;
        return palabra;
    }
    
    string des_cifrado_texto_II(string palabra){
        ZZ aaa;

        for(int i=0;i<xxx.size();i++){
            
            aaa=expo_modular_rapida_II(xxx[i], d, N);
            int nn=conv<int>(aaa);
            cout<<abecedario[nn];
        }
        
        
        cout<<endl<<endl;
        return palabra;
    }
    
    ZZ euler_fi_N(ZZ base, ZZ expo, ZZ modulo){
        //comprobando que sea mayor que fi_n
        
        //la segunda condicion no funciona para todos los casos;
        fi_N=to_ZZ("44486259507807367829594984500627327602717075289692864520459440387250465956101823546708543737117481640259886713311111815023228477154557324569912214986438502127000175646898277076767168747776935539871653945284129823006538748370449180433310243247692626267913610025761962089726328855729367749947804021872267546068010882350800810255388741040305691152675827454932502619200555033349289711793308038225930542135063492902012043466235519297508621024597659508358194122464274021459164186073238539911430856058466420682332828273624711975578120210816941437900629931423432728171067467057619471611296404891567918474033955866377762651176058715078959985214249135075327417261686006727427028966051589225229937568961251162594651024125095022004082698759303448928733613275836947739882234776547757830672328262713103010047750526526775533336109673191619212373641407522392375395549851889554457634086538424211230705707277557768380335988002705842795187052183718841682893766987108370657336499111261484106222050948090890366318295019955598720447905637790783745901409197568430767154690098550260020419877318205456439779200764978370630660907928502179554040371434304842950354242913059932077542451616253179982312615438278190948209454344789513647341581624230223656515063120");
        
        
        if(fi_N==expo){  // primera condicion de euler;
            
            return to_ZZ("1");
        }
        
        if(expo>fi_N){  // tercera condicion, esta fue modificada y si funciona
            expo=abs(expo-fi_N);
            base=expo_modular_rapida_II(base, expo, modulo);
            cout<<"EULER ENTRA"<<endl;
            return base;
        }
        base=expo_modular_rapida_II(base, expo, modulo);
        cout<<"TIEMPO EULER - >>"<<endl<<GetTime()<<endl;
        cout<<"EULER ENTRA "<<endl;
        return base;
    }
    
    string cifrado_bloques(string palabra){
    
        
        N=to_ZZ("5888113332502691251761936431009284884966640757179802337490546478326238537107326596800820237597139824869184990638749556269785797065508097452399642780486933");

        e=to_ZZ("84966350715998407970959990824869629568939665578685934638248176892675059102765");
        //N=to_ZZ("72034954131175013156554178211395580626391742877530575894580130175454073710327464529602899469346154058809936050647610607649202104986861764843831539143904398137177234668938596983238155176184827734377355282371046830244960337745758402137546882336469574119393481788113634830990084388549120332043364171135456254239517981146299854097947873067159916830262204169996157850598219758703883028999387851349163763834245751906555427162957304338455346177762331564749241085012718042407826565575033674927542225181345911904665484901741822049522417045737989725166332095349630322669946701967033739608940712798196788556657763244079260282937");
       // cout<<"N es "<<N<<endl;
        //e=to_ZZ("133107410335364063367082308894580709356826248914464845341833682609946174753569656770483049042974406732217847358220253980229193891952876753065915297179118138882009822176811456383722844536993535669138148358077048620291534175639077252294898868270153410095750634392422558075937465455941221563537405964805002022189");
        //cout<<"e es "<<e<<endl;
        
        //d=to_ZZ("6982161831578783412324400536311483741518505660929166712732690862262371989064578534344282828935201636186678450046942455272783053330827585591345670342987687428641963593674985195861709804871171145425728981587198373210781401561451669554107444486840535414544483486002397702579590978907844273046987604074881663516592066282363335702264191429093323472605858379808267249613733124343477317158843942080201683124902721104826228506022143376556134125975951264537027225332170277297645452732565828182135791596167205866533725226332421423535916195032032797999376332908621920354506529056239183719325413992271849301511999753953306346001");
        //cout<<"d es "<<d<<endl;

        palabra="hola mundo como estan, hola mundo.... como estan hola mundo como estan hola mundo como estan hola mundo, como estan hola mundo como estan hola mundo como estan hola mundo, como estan:::hola mundo, como estan hola mundo como estan hola mundo como estan hola mundo como estan hola mundo como estan hola mundo como estan, hola mundo como estan hola mundo como estan hola mundo como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan hola mundo:::::: como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan JESUS VERA CALLME..........";
        //cout<<palabra;
        stringstream ss;
        ss << N;
        string str1 = ss.str();
        int largo_N=str1.length();
        int tamano_bloque=largo_N-1;
        //cout<<largo_N<<endl<<endl;
        
        string almacen;
        
        for(int i=0;i<palabra.length();i++){
            ZZ numero;
            numero=abecedario.find(palabra[i])+101;
            stringstream ss;
            ss << numero;
            string str1 = ss.str();
            
            almacen+=str1;
        }

        string nuevo_almacen;
        
        for(int i=0;i<almacen.length();){
            string temporal=almacen.substr(i,tamano_bloque);
            ZZ other;
            istringstream convert(temporal);
            if ( !(convert >> other) )  other = 0;
            other=expo_modular_rapida_II(other, e, N);
            //cout<<other<<endl;
            stringstream ss;
            ss << other;
            string str1 = ss.str();
            
            if(str1.length()==largo_N) nuevo_almacen+=str1;
            else {
                string a((largo_N-str1.length()),'0');
                nuevo_almacen+=a+str1;
            }
            i+=tamano_bloque;
            
        }
        cout<<endl;
        return nuevo_almacen;
    }
    
    ZZ resto_chino_G(ZZ n)
    {

        
        ZZ dp, dq, Dp, Dq, m1, m2;
        ZZ q1, q2, q11, q22;
        ZZ res1, res2, res, r1, r2;
        dp = modulo_for_ZZ(d,p-1);
        dq = modulo_for_ZZ(d,q-1);
        m1 = modulo_for_ZZ(n,p);
        m2 = modulo_for_ZZ(n,q);
        Dp = expo_modular_rapida_II(m1,dp,p);
        Dq = expo_modular_rapida_II(m2,dq,q);
        q1 = inversa(q,p);
        q11 = modulo_for_ZZ(q1,p);
        q2 = inversa(p,q);
        q22 = modulo_for_ZZ(q2,q);
        r1 = modulo_for_ZZ(Dp*q,N);
        res1 = modulo_for_ZZ(r1*q11,N);
        r2 = modulo_for_ZZ(Dq*p,N);
        res2 = modulo_for_ZZ(r2*q22,N);
        res = modulo_for_ZZ(res1+res2,N);
        return res;
    }
    
    ZZ resto_chino(ZZ num,ZZ p,ZZ q,ZZ d,ZZ n){
        
        ZZ dp=modulo_for_ZZ(d,p-1);
        ZZ dq=modulo_for_ZZ(d,q-1);
        ZZ a1=expo_modular_rapida_II(modulo_for_ZZ(num,p),dp,p);
        ZZ a2=expo_modular_rapida_II(modulo_for_ZZ(num,q),dq,q);
        ZZ p2=inversa(q,p);
        ZZ q2=inversa(p,q);
        ZZ a=modulo_for_ZZ(a1*q*p2,n);
        ZZ b=modulo_for_ZZ(a2*p*q2,n);
        num=modulo_for_ZZ(a+b,n);
        return num;
    }
    
    string DES_cifrado_bloques(string palabra){
        
        palabra="39424110781910315351465036958621370773857376228941490746449827399514804038381623485266904172787213542749402887426887048799226955006582962288706377695518409245095969193899257597854815047174726969341413531003584727191730863924199551472829112349854001012833258935166674347500587946527064307952378370962021650653279144763616869106555741007040636611863405049695829534421028019448874328980688194155718994913462702040513929727985790115985401300040826143238954313097722186816446072099625634708013714576100237926066934377197899727889280409352012759234563198709995354980398923068882402201661642243709488751643157062176713006740078940914025039111652583754860792584369694873674941985099819158384921758038127598575038963558651301505029690867977456622736268925442137069430137364462181526000700115080414509105348147935854180338169877963384783053937401632682151460523249677608769127562601116014496293591122335713237019216086700530496482073197493408822339830274840542892423485409477404014579772162058931864924143012879706957474305991542410102807587166557217484514334238957912048566870681502051074902900626983369265027706649156569501101495290019764860880562642574070414977402214458942569035078979244266456175934645179413689808931428705169832894793984";
        d=to_ZZ("657739983065433445548997759481919623609316830070323402758934081663202515422180067504053765470891500521905808294330357933199733519920096875914169928646273102654371012197572197785713278758588432182689567689524136037497679659124114460026866410421351247582862937731678453221025284326545878032505647217219518673944404511272264120042191354082360193599209527938493026758796306925754507289577666305185948381380931350625942528295635320025194957832149650326331028891309409733862016304150573817992168951832254178219675224194156013160747102628985651348988865868222537831858184433639496686184347970903970307276388141974797699633");
        
        N=to_ZZ("4273370250343504626339660038385401669108088953558649896404309652828377002468309152220526917080635880248607619727907970446940927872681169318193529174272180120870813976988650023406227200032000593955754126475525249197160721692258391407895520542756382163245658458830898378451011324188334319257813335265414361994632169976542960701274740482784969327088365169130380872675433191041359735226614191466265085823911394177773891156032946776594126651761649553925189624796567366909198137723289053475005115674387576238218843083429264912193805086105523806183641355206018163002035560884197667482280556562634895737553795006783996985887");
        stringstream ss;
        ss << N;
        string str1 = ss.str();
        int largo_N=str1.length();
        int tamano_bloque=largo_N-1;
        string nuevo_almacen;
        
        for(int i=0;i<palabra.length()-1;){
            string nuevo=palabra.substr(i,largo_N);
            ZZ other;
            istringstream convert(nuevo);
            if ( !(convert >> other) )  other = 0;
            
            //other=expo_modular_rapida_II(other, d, N);
            other=euler_fi_N(other, d, N);  // este es mas rapido que el resto chino
            //cout<<other<<endl;
            //ZZ resto_chino(ZZ num,ZZ p,ZZ q,ZZ d,ZZ n){
            //other = resto_chino(other, p, q, d, N);
            //resto_chino_G(other);
            //cout<<other<<endl;
            
            stringstream tt;
            tt << other;
            string astr1 = tt.str();
            
            if(astr1.length()==tamano_bloque) nuevo_almacen+=astr1;
            else {
                string a((tamano_bloque-astr1.length()),'0');
                nuevo_almacen+=a+astr1;
            }
            
            i+=largo_N;
            
        }
   
        for (int i=0;i<nuevo_almacen.length();i+=3){
            string ll=nuevo_almacen.substr(i,3);
            ZZ other;
            istringstream convert(ll);
            if ( !(convert >> other) )  other = 0;
            
            //other=other-101;
            other=abs(other- conv<ZZ>(101));
            //cout<<other<<endl;
            cout<<abecedario[conv<int>(other)];
            
        }
        cout<<"LLEGUE A QUI"<<endl;
        //cout<<nuevo_almacen<<endl;
        
        return palabra;
    }
};

#endif
