#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;

vector<tuple<I,I,I>>adjs[6+1];
I viss[N];
vector<I>ress;
I pars[N];
set<I>incs;
I cnt=0;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

void dfs(I a){
  for(auto[b,i,c]:adjs[a])if(!viss[i])
    viss[i]=c,dfs(b),ress.push_back(i);
}

B chk(){
  I cnt=0;
  for(I i=0;i<=6;i++)cnt+=adjs[i].size()%2;
  return cnt<=2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,6+1,-1);
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    adjs[a].push_back({b,i,1});
    adjs[b].push_back({a,i,2});
    incs.insert(a),incs.insert(b);
    uni(a,b);
  }
  if(incs.size()+cnt!=1)printf("No solution\n"),exit(0);
  if(!chk())printf("No solution\n"),exit(0);
  for(I i=0;i<=6;i++)if(adjs[i].size()%2){dfs(i);break;}
  if(!ress.size())for(I i=0;i<=6;i++)if(adjs[i].size()){dfs(i);break;}
  reverse(ress.begin(),ress.end());
  for(auto i:ress)printf("%i %c\n",i+1,viss[i]==1?'+':'-');
}