#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e6;
const I MIN=-2e9;
pair<I,I>rngs[N];
map<I,pair<I,I>>evts;
vector<pair<I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    evts[l].first++,evts[r].second++;
  }
  I cur=0,low=MIN;
  for(auto[x,dif]:evts){
    auto[add,sub]=dif;
    cur+=add;
    if(low==MIN&&cur>=k)low=x;
    cur-=sub;
    if(low!=MIN&&cur<k)ress.push_back({low,x}),low=MIN;
  }
  printf("%i\n",ress.size());
  for(auto[l,r]:ress)printf("%i %i\n",l,r);
}