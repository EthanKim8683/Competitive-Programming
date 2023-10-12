#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
const Lli MOD=998244353;
Lli facs[N+1];
pair<I,I>eles[N];
map<I,I>cnts1;
map<pair<I,I>,I>cnts2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    eles[i]={a,b};
  }
  sort(eles,eles+n);
  B vld=1;
  for(I i=0;i+1<n;i++){
    auto[a1,b1]=eles[i];
    auto[a2,b2]=eles[i+1];
    vld&=a1<=a2&&b1<=b2;
  }
  Lli res=facs[n],cur=1;
  for(I i=0;i<n;i++){
    auto[a,b]=eles[i];
    cnts1[a]++;
  }
  for(auto[a,cnt]:cnts1)(cur*=facs[cnt])%=MOD;
  (res-=cur)%=MOD;
  cur=1;
  cnts1.clear();
  for(I i=0;i<n;i++){
    auto[a,b]=eles[i];
    cnts1[b]++;
  }
  for(auto[b,cnt]:cnts1)(cur*=facs[cnt])%=MOD;
  (res-=cur)%=MOD;
  if(vld){
    cur=1;
    for(I i=0;i<n;i++)cnts2[eles[i]]++;
    for(auto[ele,cnt]:cnts2)(cur*=facs[cnt])%=MOD;
    (res+=cur)%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}
/*
we can use the principle of inclusion-exclusion to discount when the first
elements are sorted or the second elements are sorted and count back when both
sets of elements are sorted
*/