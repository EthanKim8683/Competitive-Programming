#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

vector<I>dp;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a;cin>>a;
    auto it=lower_bound(dp.begin(),dp.end(),a);
    if(it!=dp.end())*it=a;
    else dp.push_back(a);
  }
  printf("%i\n",dp.size());
}