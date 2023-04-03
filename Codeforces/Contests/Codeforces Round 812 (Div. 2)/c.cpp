#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I ress[N];

void slv(I x){
  I u=sqrt(2*x);u*=u;
  for(I i=u-x;i<=x;i++)ress[i]=u-i;
  if(u>x)slv(u-x-1);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    slv(n-1);
    for(I i=0;i<n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
  return 0;
}