#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=100000;
Lli l_arr[M];
Lli rgts[M];
vector<Lli>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++)cin>>l_arr[i];
  Lli upp=accumulate(l_arr,l_arr+m,0ll);
  Lli low=0;
  for(I i=0;i<m;i++)low=max(low,i+l_arr[i]);
  if(low>n||upp<n)printf("-1\n"),exit(0);
  rgts[m-1]=l_arr[m-1];
  for(I i=m-2;i>=0;i--)rgts[i]=max(rgts[i+1]+1,l_arr[i]);
  for(I i=0;i<m;i++)rgts[i]=n-rgts[i];
  Lli rgt=0;
  for(I i=0;i<m;i++){
    Lli l=l_arr[i];
    Lli cur=min(rgt,rgts[i]);
    ress.push_back(cur);
    rgt=cur+l;
  }
  for(auto res:ress)printf("%lli ",res+1);
}