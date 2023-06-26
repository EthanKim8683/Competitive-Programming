#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  if(cnts.size()<=2)printf("0"),exit(0);
  cnts.erase(cnts.begin());
  cnts.erase(prev(cnts.end()));
  I res=0;
  for(auto[val,cnt]:cnts)res+=cnt;
  printf("%i\n",res);
}