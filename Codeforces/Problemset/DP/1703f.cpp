#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
vector<I>pres;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    pres.clear();
    Lli res=0;
    for(I i=0;i<n;i++){
      if(i+1<=a_arr[i])continue;
      auto it=lower_bound(pres.begin(),pres.end(),a_arr[i]);
      if(it!=pres.begin())res+=it-pres.begin();
      pres.push_back(i+1);
    }
    printf("%lli\n",res);
  }
}