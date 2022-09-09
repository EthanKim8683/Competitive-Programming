#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I A=200000;
const I P=2750131;

B coms[P+1];
vector<I>prms;
I inds[P+1];
multiset<I>rems;
vector<I>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=1;
  for(I i=2;i*i<=P;i++)if(!coms[i])
    for(I j=i*i;j<=P;j+=i)coms[j]=1;
  for(I i=0;i<=P;i++)if(!coms[i])prms.push_back(i);
  for(I i=0;i<prms.size();i++)inds[prms[i]]=i+1;
  I n;cin>>n;
  for(I i=0;i<2*n;i++){I a;cin>>a,rems.insert(a);}
  while(rems.size()){
    auto it1=prev(rems.end());
    I a=*it1;
    if(!coms[a]){
      I b=inds[a];
      auto it2=rems.find(b);
      rems.erase(it1),rems.erase(it2);
      ress.push_back(b);
    }else{
      I b=1;
      for(I i=2;i*i<=a;i++)if(a%i==0){b=a/i;break;}
      auto it2=rems.find(b);
      rems.erase(it1),rems.erase(it2);
      ress.push_back(a);
    }
  }
  for(auto i:ress)printf("%i ",i);
  return 0;
}