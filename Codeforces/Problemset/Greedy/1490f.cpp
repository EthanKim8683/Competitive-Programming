#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;
const I MAX=1e9;

I a_arr[N];
map<I,I>cnts;
vector<I>vals;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    cnts.clear(),vals.clear();
    for(I i=0;i<n;i++)cnts[a_arr[i]]++;
    for(auto[a,cnt]:cnts)vals.push_back(cnt);
    sort(vals.begin(),vals.end());
    I m=vals.size(),res=MAX;
    for(I i=0;i<m;i++)res=min(res,n-vals[i]*(m-i));
    printf("%i\n",res);
  }
}