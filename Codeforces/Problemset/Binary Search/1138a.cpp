#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100000;

I t_arr[N];
I ps1[N+1],ps2[N+1];

B chk(I l,I r){
  r++;
  I sum1=ps1[r]-ps1[l];
  I sum2=ps2[r]-ps2[l];
  return (sum1>0&&sum2==0)||(sum1==0&&sum2>0);
}

I fnd1(I l,I r){
  I i=r;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m,i))r=m;
    else l=m+1;
  }
  return l;
}

I fnd2(I l,I r){
  I i=l;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(i,m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++){
    ps1[i+1]+=t_arr[i]==1;
    ps2[i+1]+=t_arr[i]==2;
  }
  for(I i=0;i<n;i++){
    ps1[i+1]+=ps1[i];
    ps2[i+1]+=ps2[i];
  }
  I res=0;
  for(I i=0;i+1<n;i++){
    if(t_arr[i]==t_arr[i+1])continue;
    I l=fnd1(0,i),r=fnd2(i+1,n-1);
    res=max(res,min(i-l+1,r-(i+1)+1)*2);
  }
  printf("%i\n",res);
}