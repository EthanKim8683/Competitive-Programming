#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3000;
const I K=N;
const Lli MAX=1e18;
const Lli MIN=-MAX;
Lli c_arr[N];
Lli ps1[N+1],ps2[N+1],ps3[N+1];
deque<pair<Lli,Lli>>stks1[K+1],stks2[K+1];
Lli slv(pair<Lli,Lli>f1,pair<Lli,Lli>f2){
  Lli n=f2.second-f1.second,d=f1.first-f2.first;
  return d?n/d-((n^d)<0&&n%d):MIN;
}
void upd(deque<pair<Lli,Lli>>&stks,pair<Lli,Lli>f){
  while(stks.size()>1&&slv(stks.end()[-1],f)<=slv(stks.end()[-1],stks.end()[-2]))stks.pop_back();
  stks.push_back(f);
}
Lli qry(deque<pair<Lli,Lli>>&stks,Lli x){
  while(stks.size()>1&&slv(stks[0],stks[1])<x)stks.pop_front();
  auto[m,b]=stks.front();
  return m*x+b;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)ps1[i+1]=ps1[i]+c_arr[i]*(i+1),ps2[i+1]=ps2[i]+c_arr[i]*(n-i),ps3[i+1]=ps3[i]+c_arr[i];
  upd(stks1[0],{0,MAX}),upd(stks2[0],{-ps3[0],ps3[0]*n-ps2[0]+ps3[0]});
  for(I i=1;i<=k;i++)upd(stks1[i],{0,MAX}),upd(stks2[i],{0,MAX});
  for(I i=0;i<n;i++)for(I j=1;j<=k;j++){
    upd(stks1[j],{-i,ps3[i]*(i+1)-ps1[i]+qry(stks2[j-1],i+1)+ps2[i+1]-ps3[i+1]*(n-i)});
    upd(stks2[j],{-ps3[i],ps3[i]*n-ps2[i]+ps3[i]+qry(stks1[j],ps3[i])+ps1[i]-ps3[i]});
  }
  printf("%lli\n",qry(stks1[k],ps3[n])+ps1[n]-ps3[n]);
}