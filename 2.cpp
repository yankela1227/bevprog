#include <iostream>
#include "std_lib_facilities.h"

using namespace std;
void swap_v(int a,int b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}
void swap_r(int & a,int & b){
    int temp;
    temp = a,
    a=b;
    b=temp;
}
/*void swap_cr(const int & a,const int & b){
    int temp;
    temp = a;
    a=b; a,b are only readable
    b=temp;
}
*/

int main()
{
    int x = 7;
    int y =9;
    cout<<"x= "<<x<<endl;
    cout<<"y= "<<y<<endl;
    swap_r(x,y);                      // replace ? by v, r, or cr
    swap_v(7,9);
    cout<<"x= "<<x<<endl;
    cout<<"y= "<<y<<endl;
    const int cx = 7;
    const int cy = 9;
    cout<<"cx= "<<cx<<endl;
    cout<<"cy= "<<cy<<endl;
    //swap_cr(cx,cy); can't be done
    //swap_v(7.7,9.9); won't do anything, only for int's
    cout<<"cx= "<<cx<<endl;
    cout<<"cy= "<<cy<<endl;
    double dx = 7.7;
    double dy = 9.9;
    cout<<"dx= "<<dx<<endl;
    cout<<"dy= "<<dy<<endl;
    //swap_r(dx,dy); not constants
    //swap_v(7.7,9.9); won't do anything, only for int's
    cout<<"dx= "<<dx<<endl;
    cout<<"dy= "<<dy<<endl;
    return 0;
}
