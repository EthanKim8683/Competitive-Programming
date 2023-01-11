#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I a_arr[N];
I inds[N];
vector<I>subs;
B cols[N];
I n,k;
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
B chk(I x){
  subs.clear();
  for(I i=0;i<=x;i++)subs.push_back(inds[i]);
  sort(subs.begin(),subs.end());
  fill_n(cols,n,0),cols[subs[0]]=0;
  for(I i=1;i<subs.size();i++){
    I j=subs[i];
    if(j-1<0||cols[j-1]==0)cols[j]=1;
  }
  I lst=-1,cnt0=0,cnt1=0;
  for(I i=0;i<n;i++){
    if(cols[i]==lst)continue;
    cnt0+=cols[i]==0;
    cnt1+=cols[i]==1;
    lst=cols[i];
  }
  if(cnt0+cnt1>=k)return 1;
  fill_n(cols,n,0),cols[subs[0]]=1;
  for(I i=1;i<subs.size();i++){
    I j=subs[i];
    if(j-1<0||cols[j-1]==0)cols[j]=1;
  }
  lst=-1,cnt0=0,cnt1=0;
  for(I i=0;i<n;i++){
    if(cols[i]==lst)continue;
    cnt0+=cols[i]==0;
    cnt1+=cols[i]==1;
    lst=cols[i];
  }
  if(cnt0+cnt1>=k)return 1;
  return 0;
}
I fnd(){
  I l=0,r=n-1;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  printf("%i\n",a_arr[inds[fnd()]]);
}