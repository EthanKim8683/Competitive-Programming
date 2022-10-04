#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

map<I,I>cnts;
set<I>invs;
I n;

B chk(I x){
  if(invs.upper_bound(x)!=invs.end())return cnts.size()>=x;
  if(invs.lower_bound(x)!=invs.end())return cnts.size()-1>=x;
  return 0;
}

I fnd(){
  I l=0,r=n/2;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    cnts.clear(),invs.clear();
    for(I i=0;i<n;i++){I a;cin>>a,cnts[a]++;}
    for(auto[a,cnt]:cnts)invs.insert(cnt);
    printf("%i\n",fnd());
  }
}