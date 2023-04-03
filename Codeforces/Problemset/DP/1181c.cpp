#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
using Lli=long long int;
const I N=1000;
const I M=1000;
C blns[N][M+1];
I ps[N+1][M+1][26];
I n,m;
void bld(){
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i+1][j+1][blns[i][j]-'a']++;
  for(I i=1;i<=n;i++)for(I j=1;j<=m;j++)for(I k=0;k<26;k++)ps[i][j][k]+=ps[i-1][j][k]+ps[i][j-1][k]-ps[i-1][j-1][k];
}
I qry(I i1,I j1,I i2,I j2){
  if(i1<0||j1<0||i2>n||j2>m)return-1;
  I i=blns[i1][j1]-'a';
  if((i2-i1)*(j2-j1)==ps[i2][j2][i]-ps[i1][j2][i]-ps[i2][j1][i]+ps[i1][j1][i])return i;
  return-1;
}
B chk(I i,I j1,I j2,I siz){
  I a=qry(i-siz,j1,i,j2),b=qry(i,j1,i+siz,j2),c=qry(i+siz,j1,i+2*siz,j2);
  return a!=-1&&b!=-1&&c!=-1&&a!=b&&b!=c;
}
I cnt(I i,I siz,I j){
  if(i-siz<0||i+2*siz>n)return 0;
  I l=j,r=m;
  while(l<r){
    I t=l+(r-l+1)/2;
    chk(i,j,t,siz)?l=t:r=t-1;
  }
  return l-j;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>blns[i];
  bld();
  Lli res=0;
  for(I i=0;i<m;i++){
    C pre=blns[0][i];I siz=1;
    for(I j=1;j<n;j++){
      C cur=blns[j][i];
      if(cur!=pre)res+=cnt(j-siz,siz,i),siz=0,pre=cur;
      siz++;
    }
    res+=cnt(n-siz,siz,i);
  }
  printf("%lli\n",res);
}