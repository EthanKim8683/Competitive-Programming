#include<iostream>
#include<cstdio>
#include<set>

using namespace std;

using I=int;

set<pair<I,I>>edgs;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,p;cin>>n>>p;
    edgs.clear();
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++)
      edgs.insert({i,j});
    for(I i=0;i<n;i++){
      I a=(i+1)%n,b=(i+2)%n;
      edgs.erase({min(i,a),max(i,a)});
      edgs.erase({min(i,b),max(i,b)});
      printf("%i %i\n",i+1,a+1);
      printf("%i %i\n",i+1,b+1);
    }
    for(I i=0;i<p;i++){
      auto it=edgs.begin();
      auto[j,k]=*it;
      printf("%i %i\n",j+1,k+1);
      edgs.erase(it);
    }
  }
  return 0;
}