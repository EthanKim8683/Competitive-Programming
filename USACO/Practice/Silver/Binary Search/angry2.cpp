#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;
using B=bool;

const I N=50000;
const I MAX=1e9;

I x_arr[N];
I mins1[N],mins2[N];
I n;

B chk(I d){
  I res=0;
  for(I i=0;i<n;i++){
    I j=upper_bound(x_arr,x_arr+n,x_arr[i]+d)-x_arr-1;
    res|=max(mins1[i],mins2[j])+1<=d/2;
  }
  return res;
}

Lf fnd(){
  I l=0,r=MAX;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return (Lf)l/2;
}

I main(){
#ifndef ETHANKIM8683
  freopen("angry.in","r",stdin);
  freopen("angry.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  fill_n(mins1,n,MAX),fill_n(mins2,n,MAX);
  for(I i=0;i<n;i++)cin>>x_arr[i];
  sort(x_arr,x_arr+n);
  I j=0;
  mins1[0]=0;
  for(I i=0;i<n;i++){
    if(i-1>=0)mins1[i]=min(mins1[i],max(mins1[i-1]+1,x_arr[i]-x_arr[i-1]));
    I min1=mins1[i]+1;
    I k=upper_bound(x_arr,x_arr+n,x_arr[i]+min1)-x_arr-1;
    for(;j<=k;j++)mins1[j]=min(mins1[j],min1);
  }
  j=n-1;
  mins2[n-1]=0;
  for(I i=n-1;i>=0;i--){
    if(i+1<n)mins2[i]=min(mins2[i],max(mins2[i+1]+1,x_arr[i+1]-x_arr[i]));
    I min2=mins2[i]+1;
    I k=lower_bound(x_arr,x_arr+n,x_arr[i]-min2)-x_arr;
    for(;j>=k;j--)mins2[j]=min(mins2[j],min2);
  }
  Lf res=fnd();
  for(I i=0;i<n;i++){
    Lf dis=0;
    dis=max(dis,(Lf)mins1[i]);
    dis=max(dis,(Lf)mins2[i]);
    res=min(res,dis);
  }
  printf("%.1Lf\n",res);
}