#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=5000;
const Lli MOD=998244353;
Lli facs[N+1];
I ps[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  if(k==0)printf("1"),exit(0);
  S s;cin>>s;
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+s[i]-'0';
  Lli res=0;
  for(I l=0,r=0;r<n||l<r;){
    r<=n&&ps[r]-ps[l]<=k?r++:l++;
    if(ps[r]-ps[l]!=k||!(l-1<0||s[l-1]=='1')||!(r>=n||s[r]=='1'))continue;
    (res+=bin(r-l,k)-1)%=MOD;
  }
  for(I l=0,r=0;r<n||l<r;){
    r<=n&&ps[r]-ps[l]<=k-1?r++:l++;
    if(ps[r]-ps[l]!=k-1||!(l-1<0||s[l-1]=='1')||!(r>=n||s[r]=='1'))continue;
    if(l==0||r==n)continue;
    (res-=bin(r-l,k-1)-1)%=MOD;
  }
  printf("%lli\n",(res+1+MOD)%MOD);
}
/*
we can look at all maximum-length substrings containing subsets of k 1's

the number of possible strings different from the original string for each
such substring is bin(m, k) - 1, where m is the length of the substring

to ensure there is no counting overlap between substrings, we can count
only the shuffles that result in the leftmost 1 being moved for all but
the rightmost such substring
*/