#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=500;
I a_arr[N];
map<I,I>cnts;
list<I>curs;
vector<pair<I,I>>oprs;
vector<I>divs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    cnts.clear();
    for(I i=0;i<n;i++)cnts[a_arr[i]]++;
    B vld=1;
    for(auto[a,cnt]:cnts)vld&=cnt%2==0;
    if(!vld){printf("-1\n");continue;}
    curs.clear(),oprs.clear(),divs.clear();
    for(I i=0;i<n;i++)curs.push_back(a_arr[i]);
    I glb=1,pre=0;
    for(auto i=curs.begin(),j=next(i);j!=curs.end();j++,glb++){
      if(*i==*j){
        auto l=next(j);
        I loc=glb+1;
        for(auto k=next(i);k!=j;k++){
          oprs.push_back({loc,*k});
          l=curs.insert(l,*k),loc++;
          curs.insert(l,*k);
        }
        if(l==curs.end())break;
        divs.push_back(loc-pre),pre=loc;
        i=l,j=l,glb=loc;
      }
    }
    divs.push_back(curs.size()-pre);
    printf("%i\n",oprs.size());
    for(auto[p,c]:oprs)printf("%i %i\n",p,c);
    printf("%i\n",divs.size());
    for(auto t:divs)printf("%i ",t);
    printf("\n");
  }
}