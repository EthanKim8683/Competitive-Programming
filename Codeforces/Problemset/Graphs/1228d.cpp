#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I M=3e5;

set<I>invs[N];
set<I>unvs;
I pars[N];
map<I,I>cpss;
pair<I,I>edgs[M];

I cps(I i){
  if(cpss.count(i))return cpss[i];
  return cpss[i]=cpss.size();
}

void dfs(I a,I r){
  pars[a]=cps(r);
  for(auto it=unvs.begin();it!=unvs.end();){
    I b=*it;
    if(!invs[a].count(b)){
      unvs.erase(it);
      dfs(b,r);
      it=unvs.upper_bound(b);
    }else it++;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    invs[a].insert(b);
    invs[b].insert(a);
    edgs[i]={a,b};
  }
  for(I i=0;i<n;i++)unvs.insert(i);
  for(auto it=unvs.begin();it!=unvs.end();){
    I b=*it;
    unvs.erase(it);
    dfs(b,b);
    it=unvs.upper_bound(b);
  }
  if(cpss.size()!=3)printf("-1\n"),exit(0);
  for(I i=0;i<m;i++){
    auto[a,b]=edgs[i];
    if(pars[a]==pars[b])printf("-1\n"),exit(0);
  }
  for(I i=0;i<n;i++)
    printf("%i ",pars[i]+1);
  printf("\n");
}