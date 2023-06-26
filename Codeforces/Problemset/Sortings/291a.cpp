#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e3;
I secs[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>secs[i];
  for(I i=0;i<n;i++)if(secs[i])cnts[secs[i]]++;
  I res=0;
  for(auto[cal,cnt]:cnts){
    if(cnt>2)printf("-1"),exit(0);
    res+=cnt==2;
  }
  printf("%i\n",res);
}