#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=100;

vector<pair<I,I>>ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)ress[i].push_back({i,i});
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    ress[a].push_back({n+i,a});
    ress[b].push_back({n+i,b});
  }
  for(I i=0;i<n;i++){
    printf("%i\n",ress[i].size());
    for(auto[j,k]:ress[i])
      printf("%i %i\n",j+1,k+1);
  }
  return 0;
}