#include<iostream>
#include<cstdio>
#include<set>
#include<vector>

using namespace std;

using I=int;

const I N=2e5;

set<pair<I,I>>vals;
vector<pair<I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    vals.clear(),ress.clear();
    for(I i=0;i<n;i++){
      I a;cin>>a;
      if(a)vals.insert({a,i});
    }
    while(vals.size()>1){
      auto a=vals.begin();
      auto b=--vals.end();
      auto[av,ai]=*a;
      auto[bv,bi]=*b;
      if(--av)vals.insert({av,ai});
      if(--bv)vals.insert({bv,bi});
      vals.erase(a),vals.erase(b);
      ress.push_back({ai,bi});
    }
    printf("%i\n",ress.size());
    for(auto[a,b]:ress)printf("%i %i\n",a+1,b+1);
  }
  return 0;
}