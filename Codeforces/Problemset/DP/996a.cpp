#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I res=0;
  res+=n/100,n=n%100;
  res+=n/20,n=n%20;
  res+=n/10,n=n%10;
  res+=n/5,n=n%5;
  res+=n/1,n=n%1;
  printf("%i\n",res);
  return 0;
}