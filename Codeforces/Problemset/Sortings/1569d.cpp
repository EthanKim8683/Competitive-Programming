#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I M=2e5;
const I K=3e5;
I x_arr[N];
I y_arr[M];
vector<pair<I,I>>hors,vers;
map<I,I>cnts;
B cmp1(pair<I,I>a,pair<I,I>b){
  return a.first<b.first;
}
B cmp2(pair<I,I>a,pair<I,I>b){
  return a.second<b.second;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    for(I i=0;i<n;i++)cin>>x_arr[i];
    for(I i=0;i<m;i++)cin>>y_arr[i];
    hors.clear(),vers.clear();
    for(I i=0;i<k;i++){
      I x,y;cin>>x>>y;
      if(binary_search(y_arr,y_arr+m,y))hors.push_back({x,y});
      if(binary_search(x_arr,x_arr+n,x))vers.push_back({x,y});
    }
    sort(hors.begin(),hors.end(),cmp1);
    sort(vers.begin(),vers.end(),cmp2);
    Lli res=0;
    for(I i=0,low=0,upp=0;i+1<n;i++){
      I x1=x_arr[i],x2=x_arr[i+1];
      while(low<hors.size()&&hors[low].first<=x1)low++;
      while(upp<hors.size()&&hors[upp].first<x2)upp++;
      cnts.clear();
      for(I j=low;j<upp;j++)cnts[hors[j].second]++;
      Lli pre=0;
      for(auto[y,cnt]:cnts)res+=pre*cnt,pre+=cnt;
    }
    for(I i=0,low=0,upp=0;i+1<m;i++){
      I y1=y_arr[i],y2=y_arr[i+1];
      while(low<vers.size()&&vers[low].second<=y1)low++;
      while(upp<vers.size()&&vers[upp].second<y2)upp++;
      cnts.clear();
      for(I j=low;j<upp;j++)cnts[vers[j].first]++;
      Lli pre=0;
      for(auto[y,cnt]:cnts)res+=pre*cnt,pre+=cnt;
    }
    printf("%lli\n",res);
  }
}