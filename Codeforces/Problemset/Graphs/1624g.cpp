#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I pars[N];
vector<tuple<I,I,I>>edgs;
I cnt;

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

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    edgs.clear();
    for(I i=0;i<m;i++){
      I v,u,w;cin>>v>>u>>w;
      edgs.push_back({w,v-1,u-1});
    }
    sort(edgs.begin(),edgs.end());
    I msk=0;
    for(I i=30;i>=0;i--){
      I cur=msk|(i>0?(1<<i)-1:0);
      fill_n(pars,n,-1);
      cnt=n;
      for(auto[w,v,u]:edgs)
        if((w&~cur)==0)uni(v,u);
      if(cnt>1)msk|=1<<i;
    }
    printf("%i\n",msk);
  }
  return 0;
}