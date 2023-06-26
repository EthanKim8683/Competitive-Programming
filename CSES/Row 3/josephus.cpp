#include<bits/stdc++.h>
using namespace std;
using I=int;
set<I>curs;
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)curs.insert(i);
  I i=-1;
  while(curs.size()){
    auto it=curs.upper_bound(i);
    if(it==curs.end())it=curs.begin();
    it++;
    if(it==curs.end())it=curs.begin();
    i=*it,curs.erase(it);
    ress.push_back(i);
  }
  for(auto i:ress)printf("%i ",i+1);
}