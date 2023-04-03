#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
using B=bool;
const I N=5000;
const I LOGN=13;
const Lli MOD=1000000033;
const Lli BAS=10069;
Lli pows[N+1];
Lli hshs1[N+1],hshs2[N+1];
B vlds[2][N+1][N+1];
I ress[N];
I n;
void bld(S&s){
  pows[0]=1;
  for(I i=0;i<n;i++)pows[i+1]=pows[i]*BAS%MOD;
  for(I i=0;i<n;i++)hshs1[i+1]=(hshs1[i]*BAS+s[i])%MOD,hshs2[i+1]=(hshs2[i]*BAS+s[n-i-1])%MOD;
}
B qry(I l,I r){
  return((hshs1[r]-hshs1[l]*pows[r-l])%MOD+MOD)%MOD==((hshs2[n-l]-hshs2[n-r]*pows[r-l])%MOD+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  n=s.size();
  bld(s);
  for(I i=0;i<n;i++)for(I j=i+1;j<=n;j++)vlds[0][i][j]=vlds[1][i][j]=qry(i,j);
  I log=log2(n);
  for(I i=0;i<=log;i++){
    I res=0;
    for(I j=0;j<n;j++)for(I k=j+(1<<i);k<=n;k++){
      I siz=(k-j)/2;
      if(i>0)vlds[i%2][j][k]&=vlds[(i+1)%2][j][j+siz]&&vlds[(i+1)%2][k-siz][k];
      res+=vlds[i%2][j][k];
    }
    printf("%i ",res);
  }
  for(I i=log+1;i<n;i++)printf("0 ");
}