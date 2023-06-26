#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I fens[N+1];
vector<I>ress;
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
Lli qry(I l,Lli r){
  if(r>n){
    Lli res=0;
    res+=qry(n)-qry(l);
    res+=qry(n)*(r/n-1);
    res+=qry(r%n)-qry(0);
    return res;
  }
  return qry(r)-qry(l);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>k;
  for(I i=0;i<n;i++)upd(i+1,1);
  I j=-1;
  for(I i=0;i<n;i++){
    Lli l=j+1,r=j+(Lli)n*(k+1);
    while(l<r){
      Lli m=l+(r-l+1)/2;
      qry(j,m)<=k?l=m:r=m-1;
    }
    j=l%n;
    ress.push_back(j);
    upd(j+1,-1);
  }
  for(auto i:ress)printf("%i ",i+1);
}