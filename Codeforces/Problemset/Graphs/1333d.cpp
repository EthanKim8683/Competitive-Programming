#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=3000;

vector<vector<I>>movs;
vector<vector<I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  S s;cin>>s;
  I cnt=0;
  while(1){
    movs.push_back({});
    for(I i=0;i+1<n;i++){
      if(s[i]!='R'||s[i+1]!='L')continue;
      movs.back().push_back(i),cnt++;
    }
    if(!movs.back().size())break;
    for(auto i:movs.back())swap(s[i],s[i+1]);
  }
  movs.pop_back();
  if(cnt<k||movs.size()>k)printf("-1"),exit(0);
  I rem=k-movs.size();
  for(auto&row:movs){
    I cnt=min(rem,(I)row.size()-1);
    ress.push_back({});
    for(auto i:row){
      ress.back().push_back(i);
      if(cnt)ress.push_back({}),cnt--,rem--;
    }
  }
  for(auto&row:ress){
    printf("%i ",row.size());
    for(auto i:row)printf("%i ",i+1);
    printf("\n");
  }
}