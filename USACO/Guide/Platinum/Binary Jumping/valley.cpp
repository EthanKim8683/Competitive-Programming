#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
const I LOGN=17;
const I S=N;
const I W=1e9;
const Lli MAX=1e18;
vector<pair<I,I>>adjs[N];
I w_arr[N-1];
I c_arr[S];
B shps[N];
Lli lows[N];
Lli diss[N];
I deps[N];
tuple<I,Lli,B>ancs[N][LOGN];
I bots[N-1];
I tbgs[N],teds[N];
I t=0;
void dfs(I a,I p,Lli dis=0,I dep=0){
  tbgs[a]=t++;
  lows[a]=shps[a]?0:MAX;
  diss[a]=dis,deps[a]=dep;
  for(auto[b,i]:adjs[a])if(b!=p){
    I w=w_arr[i];
    bots[i]=b;
    dfs(b,a,dis+w,dep+1);
    lows[a]=min(lows[a],lows[b]+w);
    shps[a]|=shps[b];
  }
  for(auto[b,w]:adjs[a])if(b!=p)ancs[b][0]={a,dis-lows[a],shps[a]};
  teds[a]=t;
}
Lli qry(I i,I j){
  Lli upp=diss[i],res=diss[i]-lows[i];B vld=shps[i];
  for(I k=0;k<LOGN;k++)if(j>>k&1){
    auto[l,d,f]=ancs[i][k];
    i=l,res=max(res,d),vld|=f;
  }
  return vld?upp-res:-1;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,s,q,e;cin>>n>>s>>q>>e,e--;
  for(I i=0;i<n-1;i++){
    I a,b,w;cin>>a>>b>>w,a--,b--;
    adjs[a].push_back({b,i});
    adjs[b].push_back({a,i});
    w_arr[i]=w;
  }
  for(I i=0;i<s;i++){I c;cin>>c,c_arr[i]=c-1;}
  for(I i=0;i<s;i++)shps[c_arr[i]]=1;
  dfs(e,e);
  ancs[e][0]={e,0-lows[e],shps[e]};
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++){
    auto[k,d1,f1]=ancs[j][i-1];auto[l,d2,f2]=ancs[k][i-1];
    ancs[j][i]={l,max(d1,d2),f1|f2};
  }
  while(q--){
    I i,r;cin>>i>>r,i--,r--;
    I j=bots[i];
    if(!anc(j,r)){printf("escaped\n");continue;}
    Lli d=qry(r,deps[r]-deps[j]);
    d==-1?printf("oo\n"):printf("%lli\n",d);
  }
}