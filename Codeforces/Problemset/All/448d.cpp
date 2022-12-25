#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
Lli n,m,k;
B chk(Lli x){
  Lli cnt=0;
  for(I i=1;i<=n;i++)cnt+=min((x-1)/i,m);
  return cnt<=k-1;
}
Lli fnd(){
  Lli l=1,r=n*m;
  while(l<r){
    Lli x=l+(r-l+1)/2;
    chk(x)?l=x:r=x-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m>>k;
  printf("%lli\n",fnd());
}