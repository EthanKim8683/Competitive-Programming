#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=40;
const I MIN=-1e9;
vector<I>adjs[N];
I invs[N],trns[N/2];
tuple<I,I,B>dp1[1<<(N/2)],dp2[1<<(N/2)];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  I low=n/2,upp=n-low;
  for(I i=0;i<low;i++){
    invs[i]=((1<<low)-1)^(1<<i),trns[i]=(1<<upp)-1;
    for(auto j:adjs[i])if(j<low)invs[i]^=1<<j;
    for(auto j:adjs[i])if(j>=low)trns[i]^=1<<(j-low);
  }
  for(I i=0;i<upp;i++){
    invs[i+low]=((1<<upp)-1)^(1<<i);
    for(auto j:adjs[i+low])if(j>=low)invs[i+low]^=1<<(j-low);
  }
  dp1[0]={0,-1,-1};
  for(I i=0;i<(1<<low);i++){
    I msk=(1<<low)-1;
    for(I j=0;j<low;j++)if(i>>j&1)msk&=invs[j];
    for(I j=0;j<low;j++)if(msk>>j&1)dp1[i|1<<j]=max(dp1[i|1<<j],{get<0>(dp1[i])+1,i,1});
    for(I j=0;j<low;j++)if(~i>>j&1)dp1[i|1<<j]=max(dp1[i|1<<j],{get<0>(dp1[i]),i,0});
  }
  dp2[0]={0,-1,-1};
  for(I i=0;i<(1<<upp);i++){
    I msk=(1<<upp)-1;
    for(I j=0;j<upp;j++)if(i>>j&1)msk&=invs[j+low];
    for(I j=0;j<upp;j++)if(msk>>j&1)dp2[i|1<<j]=max(dp2[i|1<<j],{get<0>(dp2[i])+1,i,1});
    for(I j=0;j<upp;j++)if(~i>>j&1)dp2[i|1<<j]=max(dp2[i|1<<j],{get<0>(dp2[i]),i,0});
  }
  tuple<I,I,I>res={0,0,0};
  for(I i=0;i<(1<<low);i++){
    I msk=(1<<upp)-1;
    for(I j=0;j<low;j++)if(i>>j&1)msk&=trns[j];
    res=max(res,{get<0>(dp1[i])+get<0>(dp2[msk]),i,msk});
  }
  auto[siz,i,j]=res;
  while(1){
    auto[cur,k,add]=dp1[i];
    if(k==-1)break;
    if(add)ress.push_back(__builtin_ctz(i^k));
    i=k;
  }
  while(1){
    auto[cur,k,add]=dp2[j];
    if(k==-1)break;
    if(add)ress.push_back(__builtin_ctz(j^k)+low);
    j=k;
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i);
}