#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=4e5;
const I LOGN=19;
I a_arr[N];
vector<I>cpss;
I cnts[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,i;cin>>n>>i;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++)cnts[lower_bound(cpss.begin(),cpss.end(),a_arr[i])-cpss.begin()]++;
  I siz=1<<min(i*8/n,LOGN),res=0;
  I cur=0;
  for(I i=0;i<min(siz,(I)cpss.size());i++)cur+=cnts[i];
  res=max(res,cur);
  for(I i=0;i+siz<cpss.size();i++)cur+=cnts[i+siz]-cnts[i],res=max(res,cur);
  printf("%i\n",n-res);
}