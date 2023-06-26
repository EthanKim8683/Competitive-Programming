#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100;
const I K=N;
B viss[2*N];
I fens[2*N+1];
I upps[2*N];
vector<I>rems;
I n;
void upd(I i,I val){
  for(;i<=2*n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I k;cin>>n>>k;
    fill_n(viss,2*n,0);
    fill_n(upps,2*n,-1);
    fill_n(fens,2*n+1,0);
    for(I i=0;i<k;i++){
      I x,y;cin>>x>>y,x--,y--;
      if(x>y)swap(x,y);
      upps[x]=y;
      viss[x]=viss[y]=1;
    }
    rems.clear();
    for(I i=0;i<2*n;i++)if(!viss[i])rems.push_back(i);
    for(I i=0;i<rems.size()/2;i++)upps[rems[i]]=rems[i+rems.size()/2];
    Lli res=0;
    for(I i=0;i<2*n;i++)if(upps[i]!=-1){
      res+=qry(upps[i]+1)-qry(i);
      upd(upps[i]+1,1);
    }
    printf("%lli\n",res);
  }
}