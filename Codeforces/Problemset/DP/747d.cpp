#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I t_arr[N];
B uses[N];
vector<pair<I,I>>segs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++)uses[i]=t_arr[i]<0;
  I cnt=accumulate(uses,uses+n,0);
  if(cnt>k)printf("-1\n"),exit(0);
  if(cnt==0)printf("0\n"),exit(0);
  I l=0;
  while(l>=0&&!uses[l])l++;
  for(I i=l;i<n;i++){
    if(uses[i])continue;
    I len=0;
    while(i<n&&!uses[i])i++,len++;
    segs.push_back({i==n?-1:-2,len});
  }
  I res=uses[0];
  for(I i=0;i+1<n;i++)res+=uses[i]!=uses[i+1];
  sort(segs.begin(),segs.end());
  I cur=0;
  for(auto[dif,len]:segs){
    if(cur+len+cnt>k)continue;
    res+=dif,cur+=len;
  }
  printf("%i\n",res);
}