#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

vector<I>cols[2];
vector<pair<I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    if(cols[0].size()>cols[1].size()){
      for(auto j:cols[0])ress.push_back({i,j});
      cols[1].push_back(i);
    }else{
      for(auto j:cols[1])ress.push_back({i,j});
      cols[0].push_back(i);
    }
  }
  printf("%i\n",ress.size());
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  return 0;
}