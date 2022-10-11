#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MIN=-9e18;

I x_arr[N];
Lli ps[N+1];
pair<Lli,I>dp1[N],dp2[N];

void cmb1(pair<Lli,I>&a,pair<Lli,I>b){
  if(get<0>(a)>get<0>(b))return;
  if(get<0>(a)<get<0>(b)){a=b;return;}
  if(get<1>(a)<get<1>(b))return;
  if(get<1>(a)>get<1>(b)){a=b;return;}
}

void cmb2(tuple<Lli,I,I>&a,tuple<Lli,I,I>b){
  if(get<0>(a)>get<0>(b))return;
  if(get<0>(a)<get<0>(b)){a=b;return;}
  if(get<1>(a)<get<1>(b))return;
  if(get<1>(a)>get<1>(b)){a=b;return;}
  if(get<2>(a)<get<2>(b))return;
  if(get<1>(a)<get<1>(b)){a=b;return;}
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=x_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  fill_n(dp1,n,pair<Lli,I>{MIN,-1});
  fill_n(dp2,n,pair<Lli,I>{MIN,-1});
  for(I i=0;i+k<=n;i++){
    Lli sum=ps[i+k]-ps[i];
    dp1[i+k-1]={sum,i};
    dp2[i]={sum,i};
  }
  for(I i=0;i+1<n;i++)cmb1(dp1[i+1],dp1[i]);
  for(I i=n-1;i>0;i--)cmb1(dp2[i-1],dp2[i]);
  tuple<Lli,I,I>res={MIN,-1,-1};
  for(I i=0;i+1<n;i++){
    auto[sum1,x]=dp1[i];
    auto[sum2,y]=dp2[i+1];
    cmb2(res,{sum1+sum2,x,y});
  }
  printf("%i %i\n",get<1>(res)+1,get<2>(res)+1);
}