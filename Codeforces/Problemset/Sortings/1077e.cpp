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
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  for(auto[a,cnt]:cnts)vals.push_back(cnt);
  sort(vals.begin(),vals.end());
  I res=0;
  for(I i=0;i<min(32-__builtin_clz(n),(I)vals.size());i++){
    I cur=MAX;
    for(I j=0;j<=i;j++)cur=min(cur,vals.end()[j-i-1]/(1<<j));
    res=max(res,cur*((1<<(i+1))-1));
  }
  printf("%i\n",res);
}