#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;
const I MAX=1e9;

I a_arr[N];
I b_arr[N];
vector<I>vals1;
vector<I>vals2;
Lli ps1[N+1],ps2[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(ps1,n+1,0);
    fill_n(ps2,n+1,0);
    vals1.clear();
    vals2.clear();
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    for(I i=0;i<n;i++){
      I a=a_arr[i],b=b_arr[i];
      if(b==1)vals1.push_back(a);
      if(b==2)vals2.push_back(a);
    }
    sort(vals1.begin(),vals1.end(),greater<I>());
    sort(vals2.begin(),vals2.end(),greater<I>());
    I x=vals1.size(),y=vals2.size();
    for(I i=0;i<x;i++)ps1[i+1]=vals1[i];
    for(I i=0;i<y;i++)ps2[i+1]=vals2[i];
    for(I i=0;i<x;i++)ps1[i+1]+=ps1[i];
    for(I i=0;i<y;i++)ps2[i+1]+=ps2[i];
    I res=MAX;
    for(I i=0;i<=n;i++){
      if(i>x)continue;
      I j=lower_bound(ps2,ps2+y+1,m-ps1[i])-ps2;
      if(j>y)continue;
      res=min(res,i*1+j*2);
    }
    printf("%i\n",res==MAX?-1:res);
  }
}