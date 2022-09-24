#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I a_arr[N];
vector<map<I,I>>viss;
I ress[N];

I fnd(I x){
  I l=0,r=viss.size();
  while(l<r){
    I m=l+(r-l)/2;
    if(viss[m].count(x))l=m+1;
    else r=m;
  }
  return l;
}

void add(I i){
  I a=a_arr[i];
  I j=fnd(a);
  if(j==viss.size())viss.push_back({});
  viss[j].insert({a,i});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    viss.clear();
    for(I i=0;i<n;i++)add(i);
    for(auto&cycs:viss){
      I j=-1;
      for(auto[a,i]:cycs){
        if(j!=-1)ress[j]=a;
        j=i;
      }
      ress[j]=cycs.begin()->first;
    }
    for(I i=0;i<n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}