#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I LOGN=17;
const I MIN=-1e9;
I a_arr[N];
I ps[N+1];
I spas1[LOGN][N];
I spas2[LOGN][N+1];
I spas3[LOGN][N+1];
I n;
void bld1(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n;j++)spas1[i][j]=max(spas1[i-1][j],spas1[i-1][j+(1<<(i-1))]);
}
void bld2(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n+1;j++)spas2[i][j]=min(spas2[i-1][j],spas2[i-1][j+(1<<(i-1))]);
}
void bld3(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n+1;j++)spas3[i][j]=max(spas3[i-1][j],spas3[i-1][j+(1<<(i-1))]);
}
I qry1(I l,I r){
  I dis=31-__builtin_clz(r-l);
  return max(spas1[dis][l],spas1[dis][r-(1<<dis)]);
}
I qry2(I l,I r){
  I dis=31-__builtin_clz(r-l);
  return min(spas2[dis][l],spas2[dis][r-(1<<dis)]);
}
I qry3(I l,I r){
  I dis=31-__builtin_clz(r-l);
  return max(spas3[dis][l],spas3[dis][r-(1<<dis)]);
}
I fnd1(I i){
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    qry1(m,i+1)<=a_arr[i]?r=m:l=m+1;
  }
  return l;
}
I fnd2(I i){
  I l=i,r=n-1;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry1(i,m+1)<=a_arr[i]?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&spas1[0][0],&spas1[0][0]+LOGN*N,MIN);
  fill(&spas2[0][0],&spas2[0][0]+LOGN*(N+1),MIN);
  fill(&spas3[0][0],&spas3[0][0]+LOGN*(N+1),MIN);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i]+ps[i];
  copy_n(a_arr,n,spas1[0]),bld1();
  copy_n(ps,n+1,spas2[0]),bld2();
  copy_n(ps,n+1,spas3[0]),bld3();
  I res=MIN;
  for(I i=0;i<n;i++)res=max(res,qry3(i+1,fnd2(i)+2)-qry2(fnd1(i),i+1)-a_arr[i]);
  printf("%i\n",res);
}