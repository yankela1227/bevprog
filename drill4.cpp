#include <iostream>
#include "std_lib_facilities.h"

using namespace std;

int main()
{
    double a=0;
    //double b=0;
    double kicsi,nagy;
    //char c;
    bool tarolo;
    string megyseg;
    double sum=0;
    int db=0;
    vector<double>v;

    /*while(cin>>a>>b){
        if(c=='|'){
            return 0;
        }
        if(a<b){
            cout<<"A kisebb szam a: "<<a<<endl;
            cout<<"A nagyobb szam a: "<<b<<endl;
        }
        else if(b<a){
            cout<<"A kisebb szam a: "<<b<<endl;
            cout<<"A nagyobb szam a: "<<a<<endl;
        }
        else{
            cout<<"A ket szam egyenlo.\n";
        }
        if((a-b)<1.0/100){
            cout<<"A ket szam majdnem egyenlo.\n";
        }
    }*/

    /*while(cin>>a){

            cout<<a<<endl;
        if(tarolo){
            kicsi=a;
            nagy=a;
            tarolo=false;
        }
        else if(a<kicsi){
            cout<<" a legkisebb eddig.\n";
            kicsi=a;
        }
        else if(a>nagy){
            cout<<" a legnagyobb eddig.\n";
            nagy=a;
        }
    }*/
    while(cin>>a>>megyseg){
        if(megyseg=="cm"){
            a=a/100;
            db++;
            sum+=a;
        }
        else if(megyseg=="in"){
            a=(a/100)*2.54;
            db++;
            sum+=a;
        }
        else if(megyseg=="ft"){
            a=((a/100)*2.54)*12;
            db++;
            sum+=a;
        }
        else if(megyseg=="m"){
            a=a;
            db++;
            sum+=a;
        }
        else{
            cout<<"Nem jo mertekegyseg.";
        }
        v.push_back(a);
        if(tarolo){
            kicsi=a;
            nagy=a;
            tarolo=false;
        }
        else if(a<kicsi){
            cout<<a<<" a legkisebb eddig.\n";
            kicsi=a;
        }
        else if(a>nagy){
            cout<<a<<" a legnagyobb eddig.\n";
            nagy=a;
        }
    }
    cout<<"Legnagyobb: "<<nagy<<endl;
    cout<<"Legkisebb: "<<kicsi<<endl;
    cout<<"Szumma: "<<sum<<endl;
    cout<<"Darab: "<<db<<endl;

    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<' ';
    }
    return 0;
}
