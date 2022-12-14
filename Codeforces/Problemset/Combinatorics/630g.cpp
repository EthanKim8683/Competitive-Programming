#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  Lli x=1,y=1;
  for(I i=1;i<=5;i++)x*=n-1+i;
  for(I i=1;i<=5;i++)x/=i;
  for(I i=1;i<=3;i++)y*=n-1+i;
  for(I i=1;i<=3;i++)y/=i;
  printf("%lli\n",x*y);
}