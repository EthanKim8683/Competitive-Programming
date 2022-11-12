#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;
const I M=3*N;

I x_arr[N];
I y_arr[N];
vector<I>cpss;
vector<I>pnts;
I ps[M+1];
I dp1[N],dp2[N];

I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>x_arr[i];
    for(I i=0;i<n;i++)cin>>y_arr[i];
    pnts.clear(),cpss.clear();
    for(I i=0;i<n;i++){
      I x=x_arr[i];
      pnts.push_back(x);
      cpss.push_back(x);
      cpss.push_back(x+k);
      cpss.push_back(x-k);
    }
    sort(pnts.begin(),pnts.end());
    sort(cpss.begin(),cpss.end());
    pnts.erase(unique(pnts.begin(),pnts.end()),pnts.end());
    cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
    I l=pnts.size(),m=cpss.size();
    fill_n(ps,m+1,0);
    for(I i=0;i<n;i++)ps[cps(x_arr[i])+1]++;
    for(I i=0;i<m;i++)ps[i+1]+=ps[i];
    for(I i=0;i<l;i++){
      I x=pnts[i];
      dp1[i]=ps[cps(x)+1]-ps[cps(x-k)];
      dp2[i]=ps[cps(x+k)+1]-ps[cps(x)];
    }
    for(I i=0;i+1<l;i++)dp1[i+1]=max(dp1[i+1],dp1[i]);
    for(I i=l-1;i>0;i--)dp2[i-1]=max(dp2[i-1],dp2[i]);
    I res=max(dp1[l-1],dp2[0]);
    for(I i=0;i+1<l;i++)res=max(res,dp1[i]+dp2[i+1]);
    printf("%i\n",res);
  }
}