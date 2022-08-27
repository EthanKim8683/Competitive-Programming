#include<iostream>
#include<cstdio>
#include<algorithm>
#include<deque>

using namespace std;

using I=int;
using Lli=long long int;

const I M=1500;
const I N=1500;

I cels[M][N];
Lli ps[M+1][N+1];
Lli lefs1[N];
Lli lefs2[N];
Lli lefs3[N];
Lli rigs1[N];
Lli rigs2[N];
Lli rigs3[N];
Lli bots1[M];
Lli bots2[M];
Lli bots3[M];
Lli tops1[M];
Lli tops2[M];
Lli tops3[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,n,k;cin>>m>>n>>k;
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)
    cin>>cels[i][j];
  for(I i=1;i<=m;i++)for(I j=1;j<=n;j++)
    ps[i][j]=cels[i-1][j-1]+ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
  for(I i=0;i+k<=m;i++)for(I j=0;j+k<=n;j++){
    Lli sum=ps[i+k][j+k]-ps[i+k][j]-ps[i][j+k]+ps[i][j];
    bots2[i]=max(bots2[i],sum);
    tops2[i+k-1]=max(tops2[i+k-1],sum);
    lefs2[j]=max(lefs2[j],sum);
    rigs2[j+k-1]=max(rigs2[j+k-1],sum);
  }
  fill_n(lefs1,n,0);
  fill_n(rigs1,n,0);
  for(I i=0;i+k<=m;i++){
    for(I j=0;j+k<=n;j++){
      Lli sum=ps[i+k][j+k]-ps[i+k][j]-ps[i][j+k]+ps[i][j];
      lefs1[j]=max(lefs1[j],sum);
      rigs1[j+k-1]=max(rigs1[j+k-1],sum);
    }
    for(I j=n-2;j>=0;j--)
      lefs1[j]=max(lefs1[j],lefs1[j+1]);
    for(I j=1;j<n;j++)
      rigs1[j]=max(rigs1[j],rigs1[j-1]);
    for(I j=1;j<n;j++)
      tops3[i+k-1]=max(tops3[i+k-1],rigs1[j-1]+lefs1[j]);
  }
  fill_n(lefs1,n,0);
  fill_n(rigs1,n,0);
  for(I i=m-k;i>=0;i--){
    for(I j=0;j+k<=n;j++){
      Lli sum=ps[i+k][j+k]-ps[i+k][j]-ps[i][j+k]+ps[i][j];
      lefs1[j]=max(lefs1[j],sum);
      rigs1[j+k-1]=max(rigs1[j+k-1],sum);
    }
    for(I j=n-2;j>=0;j--)
      lefs1[j]=max(lefs1[j],lefs1[j+1]);
    for(I j=1;j<n;j++)
      rigs1[j]=max(rigs1[j],rigs1[j-1]);
    for(I j=1;j<n;j++)
      bots3[i]=max(bots3[i],rigs1[j-1]+lefs1[j]);
  }
  fill_n(bots1,m,0);
  fill_n(tops1,m,0);
  for(I i=0;i+k<=n;i++){
    for(I j=0;j+k<=m;j++){
      Lli sum=ps[j+k][i+k]-ps[j+k][i]-ps[j][i+k]+ps[j][i];
      bots1[j]=max(bots1[j],sum);
      tops1[j+k-1]=max(tops1[j+k-1],sum);
    }
    for(I j=m-2;j>=0;j--)
      bots1[j]=max(bots1[j],bots1[j+1]);
    for(I j=1;j<m;j++)
      tops1[j]=max(tops1[j],tops1[j-1]);
    for(I j=1;j<m;j++)
      rigs3[i+k-1]=max(rigs3[i+k-1],tops1[j-1]+bots1[j]);
  }
  fill_n(bots1,m,0);
  fill_n(tops1,m,0);
  for(I i=n-k;i>=0;i--){
    for(I j=0;j+k<=m;j++){
      Lli sum=ps[j+k][i+k]-ps[j+k][i]-ps[j][i+k]+ps[j][i];
      bots1[j]=max(bots1[j],sum);
      tops1[j+k-1]=max(tops1[j+k-1],sum);
    }
    for(I j=m-2;j>=0;j--)
      bots1[j]=max(bots1[j],bots1[j+1]);
    for(I j=1;j<m;j++)
      tops1[j]=max(tops1[j],tops1[j-1]);
    for(I j=1;j<m;j++)
      lefs3[i]=max(lefs3[i],tops1[j-1]+bots1[j]);
  }
  for(I i=n-2;i>=0;i--){
    lefs2[i]=max(lefs2[i],lefs2[i+1]);
    lefs3[i]=max(lefs3[i],lefs3[i+1]);
  }
  for(I i=1;i<n;i++){
    rigs2[i]=max(rigs2[i],rigs2[i-1]);
    rigs3[i]=max(rigs3[i],rigs3[i-1]);
  }
  for(I i=m-2;i>=0;i--){
    bots2[i]=max(bots2[i],bots2[i+1]);
    bots3[i]=max(bots3[i],bots3[i+1]);
  }
  for(I i=1;i<m;i++){
    tops2[i]=max(tops2[i],tops2[i-1]);
    tops3[i]=max(tops3[i],tops3[i-1]);
  }
  Lli res=0;
  for(I i=1;i<n;i++)
    res=max(res,max(rigs2[i-1]+lefs3[i],rigs3[i-1]+lefs2[i]));
  for(I i=1;i<m;i++)
    res=max(res,max(tops2[i-1]+bots3[i],tops3[i-1]+bots2[i]));
  for(I i=1;i+k<m;i++){
    Lli sum=0;
    for(I j=0;j+k<=n;j++)
      sum=max(sum,ps[i+k][j+k]-ps[i+k][j]-ps[i][j+k]+ps[i][j]);
    res=max(res,tops2[i-1]+sum+bots2[i+k]);
  }
  for(I i=1;i+k<n;i++){
    Lli sum=0;
    for(I j=0;j+k<=m;j++)
      sum=max(sum,ps[j+k][i+k]-ps[j+k][i]-ps[j][i+k]+ps[j][i]);
    res=max(res,rigs2[i-1]+sum+lefs2[i+k]);
  }
  printf("%lli\n",res);
  return 0;
}