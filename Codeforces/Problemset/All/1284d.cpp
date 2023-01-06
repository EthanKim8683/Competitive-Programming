#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
vector<I>cpss;
pair<I,I>rngs1[N];
pair<I,I>rngs2[N];
set<I>curs;
I lows[N],upps[N],cnts[N];
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I sa,ea,sb,eb;cin>>sa>>ea>>sb>>eb;
    cpss.push_back(sa),cpss.push_back(ea),cpss.push_back(sb),cpss.push_back(eb);
    rngs1[i]={sa,ea},rngs2[i]={sb,eb};
  }
  sort(cpss.begin(),cpss.end());
  for(I i=0;i<n;i++){
    auto[s,e]=rngs1[i];
    rngs1[i]={cps(s),cps(e)};
  }
  for(I i=0;i<n;i++){
    auto[s,e]=rngs2[i];
    rngs2[i]={cps(s),cps(e)};
  }
  
}