#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=3e18;
I r_arr[N];
I g_arr[N];
I b_arr[N];
Lli cst(I x,I y,I z){
  Lli dif1=x-y,dif2=x-z,dif3=y-z;
  return dif1*dif1+dif2*dif2+dif3*dif3;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n1,n2,n3;cin>>n1>>n2>>n3;
    for(I i=0;i<n1;i++)cin>>r_arr[i];
    for(I i=0;i<n2;i++)cin>>g_arr[i];
    for(I i=0;i<n3;i++)cin>>b_arr[i];
    sort(r_arr,r_arr+n1);
    sort(g_arr,g_arr+n2);
    sort(b_arr,b_arr+n3);
    Lli res=MAX;
    for(I i=0;i<n1;i++){
      I r=r_arr[i];
      auto it1=lower_bound(g_arr,g_arr+n2,r);
      if(it1==g_arr+n2)continue;
      I g=*it1;
      auto it2=lower_bound(b_arr,b_arr+n3,r+(g-r)/2);
      if(it2!=b_arr+n3)res=min(res,cst(r,g,*it2));
      if(it2!=b_arr)res=min(res,cst(r,g,*prev(it2)));
    }
    for(I i=0;i<n1;i++){
      I r=r_arr[i];
      auto it1=lower_bound(b_arr,b_arr+n3,r);
      if(it1==b_arr+n3)continue;
      I b=*it1;
      auto it2=lower_bound(g_arr,g_arr+n2,r+(b-r)/2);
      if(it2!=g_arr+n2)res=min(res,cst(r,*it2,b));
      if(it2!=g_arr)res=min(res,cst(r,*prev(it2),b));
    }
    for(I i=0;i<n2;i++){
      I g=g_arr[i];
      auto it1=lower_bound(r_arr,r_arr+n1,g);
      if(it1==r_arr+n1)continue;
      I r=*it1;
      auto it2=lower_bound(b_arr,b_arr+n3,g+(r-g)/2);
      if(it2!=b_arr+n3)res=min(res,cst(r,g,*it2));
      if(it2!=b_arr)res=min(res,cst(r,g,*prev(it2)));
    }
    for(I i=0;i<n2;i++){
      I g=g_arr[i];
      auto it1=lower_bound(b_arr,b_arr+n3,g);
      if(it1==b_arr+n3)continue;
      I b=*it1;
      auto it2=lower_bound(r_arr,r_arr+n1,g+(b-g)/2);
      if(it2!=r_arr+n1)res=min(res,cst(*it2,g,b));
      if(it2!=r_arr)res=min(res,cst(*prev(it2),g,b));
    }
    for(I i=0;i<n3;i++){
      I b=b_arr[i];
      auto it1=lower_bound(r_arr,r_arr+n1,b);
      if(it1==r_arr+n1)continue;
      I r=*it1;
      auto it2=lower_bound(g_arr,g_arr+n2,b+(r-b)/2);
      if(it2!=g_arr+n2)res=min(res,cst(r,*it2,b));
      if(it2!=g_arr)res=min(res,cst(r,*prev(it2),b));
    }
    for(I i=0;i<n3;i++){
      I b=b_arr[i];
      auto it1=lower_bound(g_arr,g_arr+n2,b);
      if(it1==g_arr+n2)continue;
      I g=*it1;
      auto it2=lower_bound(r_arr,r_arr+n1,b+(g-b)/2);
      if(it2!=r_arr+n1)res=min(res,cst(*it2,g,b));
      if(it2!=r_arr)res=min(res,cst(*prev(it2),g,b));
    }
    printf("%lli\n",res);
  }
}