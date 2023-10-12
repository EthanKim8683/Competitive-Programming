#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const I X=1e6;
const I LOGX=20;
const I MAX=1e9;
const I MIN=-MAX;
I a_arr[N];
I spas[2][X+1][LOGX];
I x;
void bld(){
  for(I i=0;i<2;i++)for(I j=1;j<LOGX;j++)for(I k=1;k+(1<<j)<=x+1;k++)spas[i][k][j]=min(spas[i][k][j-1],spas[i][k+(1<<(j-1))][j-1]);
}
I qry(I t,I l,I r){
  if(r==l)return MAX;
  I d=31-__builtin_clz(r-l);
  return min(spas[t][l][d],spas[t][r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&spas[0][0][0],&spas[0][0][0]+2*(X+1)*LOGX,MAX);
  I n;cin>>n>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I low=MAX;
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i];
    if(low<a)spas[0][a][0]=low;
    low=min(low,a);
  }
  I upp=MIN;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(upp>a)spas[1][a][0]=-upp;
    upp=max(upp,a);
  }
  bld();
  Lli res=0;
  for(I i=1;i<=x;i++){
    I l=i,r=x+1;
    while(l<r){
      I m=l+(r-l)/2;
      i-1<min(qry(0,1,i),qry(0,m+1,x+1))&&m+1>-min(qry(1,1,i),qry(1,m+1,x+1))?r=m:l=m+1;
    }
    res+=x+1-l;
  }
  printf("%lli\n",res);
}
/*
if we include a, we must not include values [s, t], where s and t are the
minimum and maximum values with which a has inversions with

if we include all a in [1, l) or (r, x], we must not include values
[min(s), max(t)], meaning must l - 1 < min(s) and r + 1 > max(t)

for each l, we can binary search the minimum r that satisfies the inequality
and add the number of ranges starting at l and ending not before r
*/