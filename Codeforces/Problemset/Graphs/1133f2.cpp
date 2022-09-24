#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I M=2e5;

vector<I>adjs1[N];
set<I>adjs2;
set<I>adjs3;
pair<I,I>edgs[M];
I pars[N];
vector<pair<I,I>>ress;
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,d;cin>>n>>m>>d;
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I v,u;cin>>v>>u,v--,u--;
    adjs1[v].push_back(u);
    adjs1[u].push_back(v);
    if(u!=0&&v!=0)uni(u,v);
    edgs[i]={u,v};
  }
  if(adjs1[0].size()<d)printf("NO\n"),exit(0);
  for(auto i:adjs1[0]){
    I j=fnd(i);
    if(adjs2.find(j)==adjs2.end()&&ress.size()<d)
      ress.push_back({0,i}),adjs3.insert(i);
    adjs2.insert(j);
  }
  if(adjs2.size()>d)printf("NO\n"),exit(0);
  for(auto i:adjs1[0])
    if(adjs3.find(i)==adjs3.end()&&ress.size()<d)
      ress.push_back({0,i}),adjs3.insert(i);
  if(ress.size()!=d)printf("NO\n"),exit(0);
  fill_n(pars,n,-1);
  cnt=n;
  for(auto[i,j]:ress)uni(i,j);
  for(I i=0;i<m;i++){
    auto[a,b]=edgs[i];
    if(a==0||b==0)continue;
    if(uni(a,b))ress.push_back({a,b});
  }
  if(cnt!=1)printf("NO\n"),exit(0);
  printf("YES\n");
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
}