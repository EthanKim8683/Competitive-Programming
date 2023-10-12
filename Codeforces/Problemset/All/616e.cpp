#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using I128=__int128;
const Lli MOD=1e9+7;
Lli res=0;
Lli n,m;
void add(Lli l,Lli r,Lli val){
  l=min(l,m+1),r=min(r,m+1);
  res=(res+(I128)(r-l)*n)%MOD;
  res=(res-((I128)r*(r-1)/2-(I128)l*(l-1)/2)*val)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  Lli upp=m+1;
  for(Lli i=0;i*i<=n;i++){
    if(i>0)add(i,i+1,n/i);
    Lli l=1,r=upp;
    while(l<r){
      Lli t=l+(r-l)/2;
      n/t<=i?r=t:l=t+1;
    }
    if((I128)l*l>n)add(l,upp,i);
    upp=l;
  }
  printf("%lli\n",(res+MOD)%MOD);
}