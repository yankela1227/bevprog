#include "std_lib_facilities.h"

int main()
{
    string first_name;
    string friend_name;
    char friend_sex = 0;
    int age = 0;

    cout << "Kerem ird be a nevet akinek szeretnel irni:\n";
    cin >> first_name;
    cout<< "Kedves " <<first_name<<", hogy vagy? En jol vagyok, hianyzol nagyon.\n\n";

    cout << "Kerem ird be a baratod nevet akit reg lattal:\n";
    cin >> friend_name;
    cout << "Reg lattam mar "<<friend_name<<"-et, te mikor lattad utoljara?\n\n";

    cout << "Kerem ird be a baratod nemet, ha ferfi f-et irj, ha no n-et:\n";
    cin >> friend_sex;
    if(friend_sex=='f'){
        cout <<"Ha latod, mondd a csavonak hogy hivjon fel!\n\n";
    }
    else if(friend_sex=='n'){
        cout <<"Ha latod, mondd a csajnak hogy hivjon fel!\n\n";
    }

    cout << "Kerem ird be hany eves:\n";
    cin >> age;
    if(age<0 || age>100){
        simple_error("Te most viccelsz!");
    }
    cout <<"Hallottam most volt a "<<age<<".-dik szulinapod!\n";
    if(age<12){
        cout<<"Jovore mar "<<age+1<<"eves leszel.\n\n";
    }
    else if(age==17){
        cout<<"Jovore mar szavazhatsz.\n\n";
    }
    else if(age>70){
        cout<<"Remelem elvezed a nyugdijat!\n\n";
    }
    cout<<"Udvozlettel,\n\nIvan\nJankelic";
    return 0;
}
