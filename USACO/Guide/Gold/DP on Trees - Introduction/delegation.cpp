#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
vector<I>adjs[N];
vector<pair<I,I>>facs;
I sizs[N];
B ress[N];
I rems[N];
I dfs3(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p)sizs[a]+=dfs3(b,a);
  return sizs[a];
}
B dfs2(I a,I x,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    I cur=sizs[b]%x,rem=x-cur;
    if(cur==0)continue;
    rems[rem]?rems[rem]--:rems[cur]++;
  }
  I cnt=0;
  for(auto b:adjs[a])if(b!=p){
    I cur=sizs[b]%x;
    cnt+=rems[cur],rems[cur]=0;
  }
  if(cnt>1)return 0;
  for(auto b:adjs[a])if(b!=p&&!dfs2(b,x,a))return 0;
  return 1;
}
void dfs1(I i,I acc=1){
  if(i==facs.size()){ress[acc]=dfs2(0,acc);return;}
  auto[fac,cnt]=facs[i];
  for(I j=0;j<=cnt;j++)dfs1(i+1,acc),acc*=fac;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("deleg.in","r",stdin);
  freopen("deleg.out","w",stdout);
#endif
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  I m=n-1;
  for(I i=2;i*i<=m;i++){
    I cnt=0;
    for(;m%i==0;m/=i)cnt++;
    if(cnt)facs.push_back({i,cnt});
  }
  if(m>1)facs.push_back({m,1});
  dfs3(0),dfs1(0);
  for(I i=1;i<=n-1;i++)printf("%i",ress[i]);
}