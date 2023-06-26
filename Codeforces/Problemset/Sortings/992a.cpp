#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
vector<I>unqs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)if(a_arr[i])unqs.push_back(a_arr[i]);
  sort(unqs.begin(),unqs.end());
  unqs.erase(unique(unqs.begin(),unqs.end()),unqs.end());
  printf("%i\n",unqs.size());
}