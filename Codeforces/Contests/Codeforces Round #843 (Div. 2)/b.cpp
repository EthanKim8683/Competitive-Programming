#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
vector<I>bits[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)bits[i].clear();
    for(I i=0;i<n;i++){
      I k;cin>>k;
      for(I j=0;j<k;j++){
        I p;cin>>p;
        bits[i].push_back(p-1);
      }
    }
    cnts.clear();
    for(I i=0;i<n;i++)for(auto p:bits[i])cnts[p]++;
    B res=0;
    for(I i=0;i<n;i++){
      B dup=1;
      for(auto p:bits[i])dup&=cnts[p]>=2;
      res|=dup;
    }
    printf("%s\n",res?"Yes":"No");
  }
}