#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
const I M=5e4;
const Lli MOD=998244353;
I d_arr[N][M];
I cnts[N+1];
Lli prms[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  prms[0]=1;
  for(I i=1;i<=N;i++)prms[i]=prms[i-1]*i%MOD;
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>d_arr[i][j];
  Lli res=0;
  for(I i=0;i<m;i++){
    fill_n(cnts,n+1,0);
    for(I j=0;j<n;j++)cnts[d_arr[j][i]-1]++;
    for(I j=n;j-1>=0;j--)cnts[j-1]+=cnts[j];
    Lli cur=1;
    for(I j=n;j>=1;j--)(cur*=max(cnts[j]-(n-j),0))%=MOD;
    (res+=1-cur*inv(prms[n]))%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}
/*
the probability that a monument i is conquered is equal to the number of
permutations p of [1, 2, ..., n] such that any p[j] >= d[j][i]

however, instead of finding all such p, we can instead find its complement
*/