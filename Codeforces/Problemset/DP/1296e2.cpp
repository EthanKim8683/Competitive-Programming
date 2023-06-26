#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
vector<I>dp;
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  for(auto c:s){
    auto it=lower_bound(dp.begin(),dp.end(),-c);
    if(it==dp.end())ress.push_back(dp.size()),dp.push_back(-c);
    else*it=-c,ress.push_back(it-dp.begin());
  }
  printf("%i\n",dp.size());
  for(auto i:ress)printf("%i ",i+1);
}