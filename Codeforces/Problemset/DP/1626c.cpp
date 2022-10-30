#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100;

I k_arr[N];
I h_arr[N];
pair<I,I>rngs[N];
vector<I>pnts;
vector<I>ps;

Lli sum(I l,I r){
  Lli len=r-l+1;
  return len*(len+1)/2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>k_arr[i];
    for(I i=0;i<n;i++)cin>>h_arr[i];
    pnts.clear(),ps.clear();
    for(I i=0;i<n;i++){
      I k=k_arr[i],h=h_arr[i];
      rngs[i]={k-h+1,k};
      pnts.push_back(k-h+1);
      pnts.push_back(k);
    }
    sort(pnts.begin(),pnts.end());
    pnts.erase(unique(pnts.begin(),pnts.end()),pnts.end());
    for(I i=0;i<n;i++){
      auto[l,r]=rngs[i];
      l=lower_bound(pnts.begin(),pnts.end(),l)-pnts.begin();
      r=lower_bound(pnts.begin(),pnts.end(),r)-pnts.begin();
      rngs[i]={l,r};
    }
    ps.resize(pnts.size());
    for(I i=0;i<n;i++){
      auto[l,r]=rngs[i];
      ps[l]++,ps[r]--;
    }
    Lli res=0;
    I l=-1;
    for(I i=0;i+1<ps.size();i++)ps[i+1]+=ps[i];
    for(I i=0;i<ps.size();i++){
      if(l==-1)l=pnts[i];
      if(ps[i]==0)res+=sum(l,pnts[i]),l=-1;
    }
    printf("%lli\n",res);
  }
}