#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=5e5;

pair<I,I>segs[N];
map<I,I>rgts;
I pars[N];
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a,cnt--;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  cnt=n;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    segs[i]={l,r};
  }
  sort(segs,segs+n);
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    while(rgts.size()&&rgts.begin()->first<l)rgts.erase(rgts.begin());
    for(auto it=rgts.begin();it!=rgts.upper_bound(r);it++)
      if(!uni(it->second,i))printf("NO\n"),exit(0);
    rgts.insert({r,i});
  }
  if(cnt!=1)printf("NO\n"),exit(0);
  printf("YES\n");
}