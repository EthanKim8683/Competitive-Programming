#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I D=200;
const I L=1e5;
const I MAX=1e9;
I l_arr[N];
I d_arr[N];
I inds[N];
I lens[N];
I csts[N];
I dp1[N+1][D+1];
I dp2[N+1][D+1];
I ps[N+1];
B chk(I i,I j,I x){
  return j>=dp1[i][x];
}
I fnd(I i,I j){
  I l=0,r=D;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(i,j,m)?l=m:r=m-1;
  }
  return l;
}
I tot(I i,I j){
  I k=fnd(i,j);
  return dp2[i][k]+(k+1)*(j-dp1[i][k]);
}
B cmp(I a,I b){
  return l_arr[a]<l_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>l_arr[i];
  for(I i=0;i<n;i++)cin>>d_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    lens[i]=l_arr[inds[i]];
    csts[i]=d_arr[inds[i]];
  }
  for(I i=0;i<n;i++)dp1[i+1][csts[i]]=1;
  for(I i=0;i<n;i++)dp2[i+1][csts[i]]=csts[i];
  for(I i=0;i<n;i++)for(I j=0;j<=D;j++)dp1[i+1][j]+=dp1[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<=D;j++)dp2[i+1][j]+=dp2[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<D;j++)dp1[i][j+1]+=dp1[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<D;j++)dp2[i][j+1]+=dp2[i][j];
  for(I i=0;i<n;i++)ps[i+1]=csts[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  I res=MAX;
  for(I i=1;i<=L;i++){
    I low=lower_bound(lens,lens+n,i)-lens;
    I upp=upper_bound(lens,lens+n,i)-lens;
    I cnt=upp-low;
    if(!cnt)continue;
    res=min(res,tot(low,max(low-(cnt-1),0))+ps[n]-ps[upp]);
  }
  printf("%i\n",res);
}