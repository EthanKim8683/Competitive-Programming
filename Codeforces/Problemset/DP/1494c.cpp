#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I M=2e5;
I a_arr[N];
I b_arr[M];
vector<I>lows1,upps1;
vector<I>lows2,upps2;
I ps1[M+1],ps2[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<m;i++)cin>>b_arr[i];
    lows1.clear(),upps1.clear();
    lows2.clear(),upps2.clear();
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      if(a<0)lows1.push_back(-a);
      if(a>0)upps1.push_back(a);
    }
    for(I i=0;i<m;i++){
      I b=b_arr[i];
      if(b<0)lows2.push_back(-b);
      if(b>0)upps2.push_back(b);
    }
    reverse(lows1.begin(),lows1.end());
    reverse(lows2.begin(),lows2.end());
    I k=lows2.size(),l=upps2.size();
    fill_n(ps1,k+1,0);
    fill_n(ps2,l+1,0);
    for(I i=0;i<k;i++)ps1[i+1]=binary_search(lows1.begin(),lows1.end(),lows2[i]);
    for(I i=0;i<l;i++)ps2[i+1]=binary_search(upps1.begin(),upps1.end(),upps2[i]);
    for(I i=0;i<k;i++)ps1[i+1]+=ps1[i];
    for(I i=0;i<l;i++)ps2[i+1]+=ps2[i];
    I res1=0;
    for(I i=0;i<k;i++){
      I cnt=upper_bound(lows1.begin(),lows1.end(),lows2[i])-lows1.begin()-1;
      auto low=lower_bound(lows2.begin(),lows2.end(),lows2[i]-cnt);
      auto upp=upper_bound(lows2.begin(),lows2.end(),lows2[i]);
      I tot=upp-low+ps1[k]-ps1[i+1];
      res1=max(res1,tot);
    }
    I res2=0;
    for(I i=0;i<l;i++){
      I cnt=upper_bound(upps1.begin(),upps1.end(),upps2[i])-upps1.begin()-1;
      auto low=lower_bound(upps2.begin(),upps2.end(),upps2[i]-cnt);
      auto upp=upper_bound(upps2.begin(),upps2.end(),upps2[i]);
      I tot=upp-low+ps2[l]-ps2[i+1];
      res2=max(res2,tot);
    }
    printf("%i\n",res1+res2);
  }
}