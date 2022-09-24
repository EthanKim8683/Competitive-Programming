#include<iostream>
#include<cstdio>
#include<algorithm>
#include<unordered_map>

using namespace std;

using I=int;
using Lli=long long int;

unordered_map<I,I>bses;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    bses.clear();
    for(I i=0;i<n;i++){
      I a;cin>>a;
      for(I j=2;j*j<=a;j++)while(a%(j*j)==0)a/=j*j;
      bses[a]++;
    }
    I res1=0,res2=0,cnt=bses[1];
    for(auto[i,j]:bses){
      res1=max(res1,j);
      if(j%2)res2=max(res2,j);
      else if(i!=1)cnt+=j;
    }
    res2=max(res2,cnt);
    I q;cin>>q;
    while(q--){
      Lli w;cin>>w;
      printf("%i\n",w?res2:res1);
    }
  }
  return 0;
}