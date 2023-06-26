#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
I a_arr[N];
vector<I>vals[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  for(I i=0;i<n;i++)vals[a_arr[i]%2].push_back(a_arr[i]);
  if(vals[0].size()==vals[1].size())printf("0"),exit(0);
  if(vals[0].size()>vals[1].size())printf("%lli\n",accumulate(vals[0].begin(),vals[0].end()-vals[1].size()-1,0ll));
  if(vals[1].size()>vals[0].size())printf("%lli\n",accumulate(vals[1].begin(),vals[1].end()-vals[0].size()-1,0ll));
}