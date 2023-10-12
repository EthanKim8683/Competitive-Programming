#include<bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
using B=bool;
const I M=500;
const I N=500;
const Lli MOD=1e9+9;
const Lli BAS=6969;
I dx[]{-1,-1,-1,0,0,1,1,1},dy[]{-1,0,1,-1,1,-1,0,1};
C blks[M][N+1];
B viss[M][N][8];
map<Lli,I>cnts;
I m,n;
B ins(I i,I j){
  return i>=0&&i<m&&j>=0&&j<n;
}
C get(I i,I j,I dir,I len){
  return blks[((i+len*dx[dir])%m+m)%m][((j+len*dy[dir])%n+n)%n];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>m>>n>>k;
  for(I i=0;i<m;i++)cin>>blks[i];
  I len=min(lcm(m,n),k);
  Lli pow=1;
  for(I i=1;i<=len;i++)pow=pow*BAS%MOD;
  for(I i=0;i<8;i++)for(I j=0;j<m;j++)for(I l=0;l<n;l++){
    if(viss[j][l][i])continue;
    I x=j,y=l;
    for(;ins(x,y);x-=dx[i],y-=dy[i]);
    x+=dx[i],y+=dy[i];
    Lli hsh=0;
    for(I o=0;o<len;o++)hsh=(hsh*BAS+get(x,y,i,o))%MOD;
    for(;ins(x,y);x+=dx[i],y+=dy[i]){
      cnts[hsh]++,viss[x][y][i]=1;
      hsh=((hsh*BAS+get(x,y,i,len)-get(x,y,i,0)*pow)%MOD+MOD)%MOD;
    }
  }
  Lli num=0,den=8*m*n;
  den*=den;
  for(auto[hsh,cnt]:cnts)num+=(Lli)cnt*cnt;
  Lli fac=gcd(num,den);
  printf("%lli/%lli\n",num/fac,den/fac);
}