#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
I a_arr[N];
vector<I>adjs[N];
I deps[N];
I tbgs[2][N],teds[2][N];
Lli segs[2][2*N];
I tims[2];
I dep=0;
I n;
void dfs1(I a,I p=-1){
  deps[a]=dep++;
  for(auto b:adjs[a])if(b!=p)dfs1(b,a);
  dep--;
}
void dfs2(I a,I p=-1){
  for(I i=0;i<2;i++)tbgs[i][a]=tims[i];
  tims[deps[a]%2]++;
  for(auto b:adjs[a])if(b!=p)dfs2(b,a);
  for(I i=0;i<2;i++)teds[i][a]=tims[i];
}
void asn(I i,I j,Lli x){
  segs[i][j+n]=x;
}
void upd(I i,I l,I r,Lli x){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs[i][l++]+=x;
    if(r&1)segs[i][--r]+=x;
  }
}
Lli qry(I i,I j){
  Lli res=0;
  for(j+=n;j>0;j>>=1)res+=segs[i][j];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0),dfs2(0);
  for(I i=0;i<n;i++){
    I t=deps[i]%2;
    asn(t,tbgs[t][i],a_arr[i]);
  }
  while(m--){
    I t;cin>>t;
    if(t==1){
      I x,val;cin>>x>>val,x--;
      I t=deps[x]%2;
      upd(t,tbgs[t][x],teds[t][x],val);
      upd(!t,tbgs[!t][x],teds[!t][x],-val);
    }
    if(t==2){
      I x;cin>>x,x--;
      I t=deps[x]%2;
      printf("%lli\n",qry(t,tbgs[t][x]));
    }
  }
}