#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
pair<I,I>segs[N];
vector<I>unqs;
I ps1[2*N],ps2[2*N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    segs[i]={l,r};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    unqs.push_back(l);
    unqs.push_back(r);
  }
  sort(unqs.begin(),unqs.end());
  unqs.erase(unique(unqs.begin(),unqs.end()),unqs.end());
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    l=lower_bound(unqs.begin(),unqs.end(),l)-unqs.begin();
    r=lower_bound(unqs.begin(),unqs.end(),r)-unqs.begin();
    segs[i]={l,r};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    ps1[l]++,ps1[r]--;
  }
  for(I i=0;i+1<unqs.size();i++)ps1[i+1]+=ps1[i];
  I tot=0,res=0;
  for(I i=0;i+1<unqs.size();i++){
    I siz=unqs[i+1]-unqs[i];
    tot+=(ps1[i]==n-1)*siz,res+=(ps1[i]==n)*siz;
    ps2[i+1]=ps2[i]+((ps1[i]==n)-(ps1[i]==n-1))*siz;
  }
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    res=max(res,tot+ps2[r]-ps2[l]);
  }
  printf("%i\n",res);
}