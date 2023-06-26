#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lf=long double;
const I N=1e3;
const I K=N;
const I MAX=1e9;
I c_arr[N];
vector<I>stls,pens;
vector<I>ress[K];
B cmp(I a,I b){
  return c_arr[a]<c_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I c,t;cin>>c>>t;
    c_arr[i]=c;
    if(t==1)stls.push_back(i);
    if(t==2)pens.push_back(i);
  }
  sort(stls.begin(),stls.end(),cmp);
  sort(pens.begin(),pens.end(),cmp);
  for(I i=0;i<max(k-(I)stls.size(),0);i++)ress[i].push_back(pens[i]);
  for(I i=max(k-(I)stls.size(),0);i<k;i++)ress[i].push_back(stls[i-(k-stls.size())]);
  for(I i=max(k-(I)stls.size(),0);i<pens.size();i++)ress[0].push_back(pens[i]);
  for(I i=0;i<max(k-(I)stls.size(),0)-(k-(I)stls.size());i++)ress[0].push_back(stls[i]);
  Lf res=0;
  for(I i=max(k-(I)stls.size(),0);i<k;i++){
    I low=MAX;
    for(auto j:ress[i])low=min(low,c_arr[j]);
    res-=low;
  }
  res/=2;
  for(I i=0;i<n;i++)res+=c_arr[i];
  printf("%.1Lf\n",res);
  for(I i=0;i<k;i++){
    printf("%i ",ress[i].size());
    for(auto j:ress[i])printf("%i ",j+1);
    printf("\n");
  }
}