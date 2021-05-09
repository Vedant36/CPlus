#include <iostream>
#include <cmath>
using namespace std;
long long int emm=0;

int fac(long long int num, long int i=2)
{
  if(num==1){
    return 0;
  }
  for (; i < sqrt(num)+1; ++i){
    if(num%i==0){
      cout<<i<<' ';
      for (;num%i==0;){
        num=num/i;
      }
      return fac(num,i);
    }
    if(i>emm){
      cout<<num<<' ';
      return 0;
    }
  }
  cout<<num<<' ';
  return 0;
}
int main()
{
  long long int num=0L;
  // cin>>num;
  num =  8753195687658317;
  cout<<"Prime factors of "<<num<<":\n\t";
  emm=sqrt(num);
  fac(num);
  cout<<endl;
}
