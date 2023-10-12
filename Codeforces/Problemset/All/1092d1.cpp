#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I a_arr[N];
vector<pair<I,I>>stks;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  if(n==1)printf("YES\n"),exit(0);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i]%2,len=1;
    while(stks.size()&&stks.back().first%2==0)len+=stks.back().first,stks.pop_back();
    if(stks.size()&&stks.back().second==a)stks.back().first+=len;
    else stks.push_back({len,a});
  }
  I cnt=0;
  for(auto[len,a]:stks)cnt+=len%2;
  printf("%s\n",cnt<=1?"YES":"NO");
}