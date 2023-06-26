#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I b_arr[N];
vector<I>skls[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    skls[0].clear(),skls[1].clear();
    for(I i=0;i<n;i++)skls[a_arr[i]].push_back(b_arr[i]);
    sort(skls[0].begin(),skls[0].end());
    sort(skls[1].begin(),skls[1].end());
    I m=min(skls[0].size(),skls[1].size());
    Lli res=0;
    res+=accumulate(b_arr,b_arr+n,0ll);
    res+=accumulate(skls[0].end()-m,skls[0].end(),0ll);
    res+=accumulate(skls[1].end()-m,skls[1].end(),0ll);
    if(skls[0].size()==skls[1].size())res-=*min_element(b_arr,b_arr+n);
    printf("%lli\n",res);
  }
}