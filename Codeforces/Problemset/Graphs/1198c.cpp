#include<iostream>
#include<cstdio>
#include<set>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>ress;
set<I>unvs;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    ress.clear(),unvs.clear();
    for(I i=0;i<3*n;i++)unvs.insert(i);
    for(I i=0;i<m;i++){
      I u,v;cin>>u>>v,u--,v--;
      if(unvs.count(u)&&unvs.count(v)){
        ress.push_back(i);
        unvs.erase(u),unvs.erase(v);
      }
    }
    if(ress.size()<n){
      printf("IndSet\n");
      ress.clear();
      for(auto i:unvs)ress.push_back(i);
    }else printf("Matching\n");
    for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
    printf("\n");
  }
  return 0;
}