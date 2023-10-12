#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
const Lli MAX=4e18;
I a_arr[N];
I n,m;
B chk(Lli x){
  Lli pre=0,tot=0;
  for(I i=n-1;i>=0;i--){
    Lli a=a_arr[i],dif=min(a,pre);
    a-=dif,pre-=dif;
    Lli rem=x-(i+1);
    if(rem<=0){
      if(a>0)return 0;
      continue;
    }
    Lli cnt=(a+rem-1)/rem;
    tot+=cnt,pre+=cnt*rem-a;
  }
  return tot<=m;
}
Lli fnd(){
  Lli l=0,r=MAX;
  while(l<r){
    Lli m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  printf("%lli\n",fnd());
}