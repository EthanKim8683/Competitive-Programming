#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I L=64;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli l,r;cin>>l>>r;
  B dif=0;
  Lli res=0;
  for(I i=L-1;i>=0;i--){
    I a=l>>i&1,b=r>>i&1;
    dif|=a!=b;
    if(dif)res|=(Lli)1<<i;
  }
  printf("%lli\n",res);
}