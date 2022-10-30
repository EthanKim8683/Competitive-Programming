#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
 
const I N=200000;
 
I a_arr[N];
vector<I>lfts,rgts;
pair<I,I>dp[N+1];
vector<pair<I,I>>ress;
I upp=0;
I s,d;

void trn(I rgt){
  auto it1=lower_bound(lfts.begin(),lfts.end(),rgt);
  if(it1==lfts.end())return;
  I lft=*it1;
  if(lft-rgt<s)return;
  auto it2=lower_bound(rgts.begin(),rgts.end(),lft);
  auto it3=upper_bound(rgts.begin(),rgts.end(),lft+d);
  if(it2==rgts.end()||it3==rgts.begin())return;
  I j=it2-rgts.begin(),k=it3-rgts.begin()-1;
  for(upp=max(upp,j);upp<=k;upp++)dp[upp]={rgt,lft};
}
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>s>>d;
  fill_n(dp,n+1,pair<I,I>{-1,-1});
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(!binary_search(a_arr,a_arr+n,a+1))rgts.push_back(a+1);
    if(!binary_search(a_arr,a_arr+n,a-1))lfts.push_back(a-1);
  }
  trn(0);
  for(I i=0;i<rgts.size();i++){
    if(dp[i].first<0)continue;
    trn(rgts[i]);
  }
  if(dp[rgts.size()-1].first==-1)printf("IMPOSSIBLE\n"),exit(0);
  if(m-rgts.back()>0)ress.push_back({0,m-rgts.back()});
  for(I i=rgts.size()-1;i>=0;){
    auto[rgt,lft]=dp[i];I cur=rgts[i];
    I j=lower_bound(rgts.begin(),rgts.end(),rgt)-rgts.begin();
    if(cur-lft>0)ress.push_back({1,cur-lft});
    if(lft-rgt>0)ress.push_back({0,lft-rgt});
    if(rgt!=rgts[j])break;
    i=j;
  }
  reverse(ress.begin(),ress.end());
  for(auto[t,len]:ress)printf("%s %i\n",t?"JUMP":"RUN",len);
}