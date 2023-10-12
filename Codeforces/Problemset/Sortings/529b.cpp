#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000;
const I MAX=1e9;
pair<I,I>ppls[N];
set<I>hgts;
vector<I>curs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I w,h;cin>>w>>h;
    ppls[i]={w,h};
    hgts.insert(w);
    hgts.insert(h);
  }
  I res=MAX;
  for(auto t:hgts){
    B vld=1;
    I cur=0,rem=n/2;
    curs.clear();
    for(I i=0;i<n;i++){
      auto[w,h]=ppls[i];
      if(h>t){
        if(w>t){vld=0;break;}
        cur+=h,rem--;
      }else{
        cur+=w;
        if(w<=t)curs.push_back(h-w);
      }
    }
    if(!vld)continue;
    if(rem<0)continue;
    sort(curs.begin(),curs.end());
    for(I i=0;i<min(rem,(I)curs.size());i++){
      if(curs[i]>0)break;
      cur+=curs[i];
    }
    res=min(res,cur*t);
  }
  printf("%i\n",res);
}