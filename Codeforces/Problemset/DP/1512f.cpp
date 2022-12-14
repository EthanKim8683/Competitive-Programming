#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
const Lli MAX=1e18;
I a_arr[N];
I b_arr[N-1];
Lli tims[N],rems[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,c;cin>>n>>c;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n-1;i++)cin>>b_arr[i];
    Lli tim=0,rem=0;
    for(I i=0;i<n-1;i++){
      I a=a_arr[i],b=b_arr[i];
      rem-=b;
      Lli dbt=max((Lli)0,0-rem);
      Lli cur=dbt/a+!!(dbt%a);
      tim+=cur+1;
      rem+=cur*a;
      tims[i+1]=tim;
      rems[i+1]=rem;
    }
    Lli res=MAX;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      Lli tim=tims[i];
      Lli rem=rems[i];
      rem-=c;
      Lli dbt=max((Lli)0,0-rem);
      Lli cur=dbt/a+!!(dbt%a);
      tim+=cur;
      res=min(res,tim);
    }
    printf("%lli\n",res);
  }
}