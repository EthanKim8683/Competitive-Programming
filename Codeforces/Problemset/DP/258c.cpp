#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I A=1e5;
const I V=128;
const Lli MOD=1e9+7;
I a_arr[N];
I eras[A+1];
I cnts[A+1];
I ps[A+2];
Lli pows[V+1][N+1];
map<I,I>vals;
set<I>facs;
I main(){
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)if(eras[i]==i)for(I j=i*i;j<=A;j+=i)if(eras[j]==j)eras[j]=i;
  for(I i=0;i<=V;i++){
    pows[i][0]=1;
    for(I j=1;j<=N;j++)pows[i][j]=pows[i][j-1]*i%MOD;
  }
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  for(I i=1;i<=A;i++)ps[i+1]=ps[i]+cnts[i];
  Lli res=0;
  for(I i=1;i<=A;i++){
    facs.clear(),vals.clear();
    for(I t=i;t>1;t/=eras[t])facs.insert(eras[t]);
    vals.insert({1,-1});
    I ind=1;
    for(auto it=vals.begin();it!=vals.end();it=vals.upper_bound(it->first)){
      Lli val=it->first;
      it->second=ind++;
      for(auto fac:facs)if(i%(val*fac)==0)vals.insert({val*fac,-1});
    }
    Lli res1=1,res2=1,low1=0,low2=0;
    for(auto it=vals.rbegin();it!=vals.rend();it++){
      I cnt=ps[A+1]-ps[it->first];
      (res1*=pows[it->second][cnt-low1])%=MOD,low1=cnt;
      if(it!=vals.rbegin())(res2*=pows[it->second][cnt-low2])%=MOD,low2=cnt;
    }
    (res+=res1-(vals.size()>1?res2:0))%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}