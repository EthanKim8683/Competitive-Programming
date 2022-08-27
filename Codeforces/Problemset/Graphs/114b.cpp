#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=16;
const I M=N*(N-1)/2;

unordered_map<S,I>keys;
S vals[N];
I msks[M];
vector<S>ress;

I pop(I i){
  return __builtin_popcount(i);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    S s;cin>>s;
    keys[s]=i;
    vals[i]=s;
  }
  for(I i=0;i<m;i++){
    S a,b;cin>>a>>b;
    msks[i]=1<<keys[a]|1<<keys[b];
  }
  I res=0;
  for(I i=0;i<(1<<n);i++){
    B vld=true;
    for(I j=0;j<m&&vld;j++){
      I msk=msks[j];
      vld&=(msk&i)!=msk;
    }
    if(vld&&pop(i)>pop(res))res=i;
  }
  for(I i=0;i<n;i++)if(res>>i&1)
    ress.push_back(vals[i]);
  sort(ress.begin(),ress.end());
  printf("%i\n",ress.size());
  for(auto s:ress)printf("%s\n",s.c_str());
  return 0;
}