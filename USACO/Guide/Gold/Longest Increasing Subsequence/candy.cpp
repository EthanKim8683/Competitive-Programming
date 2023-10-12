#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I MAX=2e9+1;
pair<I,I>cans[N];
I mins[N],majs[N];
I inds[N];
vector<pair<I,I>>dp;
I pars[N];
vector<I>mids,lows,upps;
I pres[N];
I ress[N];
I invs[N];
B cmp1(I a,I b){
  return mins[a]==mins[b]?majs[a]>majs[b]:mins[a]<mins[b];
}
B cmp2(I a,I b){
  return majs[a]==majs[b]?mins[a]>mins[b]:majs[a]<majs[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I s,t;cin>>s>>t;
    cans[i]={s,t};
    mins[i]=s+t,majs[i]=s-t;
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp1);
  for(I i=0;i<n;i++){
    I j=inds[i],maj=majs[j];
    auto it=lower_bound(dp.begin(),dp.end(),pair<I,I>{maj,-1});
    pars[j]=it!=dp.begin()?prev(it)->second:-1;
    if(it==dp.end())dp.push_back({maj,j});
    else*it={maj,j};
  }
  for(I i=dp.back().second;i!=-1;i=pars[i])mids.push_back(i);
  reverse(mids.begin(),mids.end());
  for(I i=0,j=0;i<n;i++){
    I k=inds[i];
    if(j<mids.size()){
      if(k==mids[j])j++;
      else(majs[k]<majs[mids[j]]?lows:upps).push_back(k);
    }else{
      lows.push_back(k);
    }
  }
  for(I i=0;i<mids.size();i++)pres[i]=majs[mids[i]];
  for(auto i:lows){
    I l=0,r=mids.size()-1;
    while(l<r){
      I m=l+(r-l)/2;
      pres[m]>=majs[i]?r=m:l=m+1;
    }
    pres[l]=majs[i],ress[i]=mids[l];
  }
  sort(mids.begin(),mids.end(),cmp2);
  sort(upps.begin(),upps.end(),cmp2);
  for(I i=0;i<mids.size();i++)pres[i]=mins[mids[i]];
  for(auto i:upps){
    I l=0,r=mids.size()-1;
    while(l<r){
      I m=l+(r-l)/2;
      pres[m]>=mins[i]?r=m:l=m+1;
    }
    pres[l]=mins[i],ress[i]=mids[l];
  }
  for(auto i:mids)ress[i]=i;
  for(I i=0;i<mids.size();i++)invs[mids[i]]=i;
  printf("%i\n",mids.size());
  for(I i=0;i<n;i++){
    auto[s,t]=cans[i];
    printf("%i %i %i\n",s,t,invs[ress[i]]+1);
  }
}