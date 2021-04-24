#include <iostream>
#include <math.h>

using namespace std;
int main(){
  long long int a;//=2520;
  cin>>a;
  cout<<"\nPrime factors of "<<a<<": \n ";
  long long int b=sqrt(a)+1;
  for(int i=2;;){
    if(a%i==0){
      cout<<i<<", ";
      a=a/i;
      for (;a%i==0;){
        a=a/i;
      }
    }
    else{
      ++i;
    }
    if(i>b){
      cout<<a;
      break;
    }
  }
  cout<<endl;
  getchar();
  return 0;
}
