#include<bits/stdc++.h>
using namespace std;
using I=int;
const I A=1e4;
const I MAX=1e9;
vector<I>divs[2*A+1];
I a,b,c;
tuple<I,I,I>fnd(I i){
  pair<I,I>res1={MAX,-1},res2={MAX,-1};
  auto it=upper_bound(divs[i].begin(),divs[i].end(),a);
  if(it!=divs[i].end()){
    I fac1=*it;
    res1=min(res1,{abs(fac1-a),fac1});
  }
  if(it!=divs[i].begin()){
    I fac2=*prev(it);
    res1=min(res1,{abs(fac2-a),fac2});
  }
  I fac3=c/i,fac4=fac3+1;
  fac3=i*fac3,fac4=i*fac4;
  res2=min(res2,{abs(fac3-c),fac3});
  res2=min(res2,{abs(fac4-c),fac4});
  return{res1.second,i,res2.second};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=2*A;i++)for(I j=i;j<=2*A;j+=i)divs[j].push_back(i);
  I t;cin>>t;
  while(t--){
    cin>>a>>b>>c;
    pair<I,I>res={MAX,-1};
    for(I i=1;i<=2*A;i++){
      auto[x,y,z]=fnd(i);
      res=min(res,{abs(x-a)+abs(y-b)+abs(z-c),i});
    }
    auto[x,y,z]=fnd(res.second);
    printf("%i\n",res.first);
    printf("%i %i %i\n",x,y,z);
  }
}