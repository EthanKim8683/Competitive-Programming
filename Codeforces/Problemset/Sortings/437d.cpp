#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
using Lf=long double;
const I N=1e5;
I a_arr[N];
vector<I>adjs[N];
I inds[N];
I pars[N];
B viss[N];
set<I>curs;
B cmp(I a,I b){
  return a_arr[a]>a_arr[b];
}
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  fill_n(pars,n,-1);
  Lli res=0;
  for(I i=0;i<n;i++){
    I j=inds[i];viss[j]=1;
    curs.clear();
    for(auto k:adjs[j])if(viss[k])curs.insert(fnd(k));
    Lli pre=1;
    for(auto k:curs){
      res-=pre*pars[k]*a_arr[j];
      pre-=pars[k];
    }
    for(auto k:adjs[j])if(viss[k])uni(j,k);
  }
  printf("%.6Lf\n",(Lf)res/((Lli)n*(n-1)/2));
}