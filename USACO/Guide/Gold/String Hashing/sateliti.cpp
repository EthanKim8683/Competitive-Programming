#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=1000;
const I M=1000;
const Lli BAS=6969;
const Lli MOD=(1ll<<31)-1;
C imgs[N][M+1];
Lli pows[N*M+1];
Lli hshs1[N][M+1];
Lli hshs2[M][N+1];
I n,m;
Lli rng1(I i,I j,I len){
  if(j+len>m)return(rng1(i,j,m-j)*pows[j+len-m]+rng1(i,0,j+len-m))%MOD;
  return((hshs1[i][j+len]-hshs1[i][j]*pows[len])%MOD+MOD)%MOD;
}
Lli rng2(I i,I j,I len){
  if(i+len>n)return(rng2(i,j,n-i)*pows[(i+len-n)*m]+rng2(0,j,i+len-n))%MOD;
  return((hshs2[j][i+len]-hshs2[j][i]*pows[len*m])%MOD+MOD)%MOD;
}
Lli qry1(I i,I j,I len){
  I big=len/m,sml=len%m;
  return(rng2(i,j,big)*pows[sml]+rng1((i+big)%n,j,sml))%MOD;
}
C qry2(I i,I j,I len){
  I big=len/m,sml=len%m;
  return imgs[(i+big)%n][(j+sml)%m];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N*M;i++)pows[i]=pows[i-1]*BAS%MOD;
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>imgs[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)hshs1[i][j+1]=(hshs1[i][j]*pows[1]+imgs[i][j])%MOD;
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)hshs2[i][j+1]=(hshs2[i][j]*pows[m]+rng1(j,i,m))%MOD;
  pair<I,I>res={0,0};
  for(I i2=0;i2<n;i2++)for(I j2=0;j2<m;j2++){
    auto[i1,j1]=res;
    I l=0,r=n*m-1;
    while(l<r){
      I t=l+(r-l+1)/2;
      qry1(i2,j2,t)==qry1(i1,j1,t)?l=t:r=t-1;
    }
    if(qry2(i2,j2,l)<qry2(i1,j1,l))res={i2,j2};
  }
  auto[x,y]=res;
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)printf("%c",imgs[(x+i)%n][(y+j)%m]);
    printf("\n");
  }
}