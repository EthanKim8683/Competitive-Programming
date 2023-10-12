#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I LOGN=18;
const I MAX=1e9;
const I MIN=-1e9;
vector<pair<I,I>>qrys;
vector<pair<I,I>>upps[N];
vector<tuple<I,I,I>>slvs;
priority_queue<pair<I,I>>ques;
I spas[N][LOGN];
I tims[N],ress[N];
vector<I>unks;
I n;
void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=max(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return max(spas[l][d],spas[r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<q;i++){
    I t;cin>>t;
    if(t==0){
      I l,r,x;cin>>l>>r>>x,l--,r--;
      if(x==0)upps[l].push_back({r,i});
      if(x==1)slvs.push_back({l,r,i});
    }
    if(t==1){
      I j;cin>>j,j--;
      qrys.push_back({j,i});
    }
  }
  fill_n(tims,n,MAX);
  for(I i=0;i<n;i++){
    for(auto[j,t]:upps[i])ques.push({-t,j});
    while(ques.size()&&ques.top().second<i)ques.pop();
    if(ques.size()){
      tims[i]=spas[i][0]=-ques.top().first;
      ress[i]=0;
    }else{
      unks.push_back(i);
      spas[i][0]=MIN;
    }
  }
  bld();
  for(auto[l,r,t]:slvs){
    auto it=lower_bound(unks.begin(),unks.end(),l);
    if(upper_bound(unks.begin(),unks.end(),r)-it!=1)continue;
    I i=*it;
    tims[i]=min(tims[i],max(qry(l,r+1),t));
    ress[i]=1;
  }
  for(auto[i,t]:qrys)printf("%s\n",tims[i]<=t?ress[i]?"YES":"NO":"N/A");
}
/*
a patient can only be determined to be sick if they're covered by a range of
type 1 and all other patients in said range are not sick

thus, we can keep track of the minimum query each patient is marked "not
sick" and check for each query of type 1 the maximum query required to tell,
provided that only one patient is "unknown", then assign that patient that
value
*/