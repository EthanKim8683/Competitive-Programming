#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=5000;

S strs[N];

B cmp(S a,S b){
  return a+b<b+a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  S s;cin>>s;
  for(I i=0;i<n;i++)strs[i]=s.substr(0,i+1);
  for(I i=0;i<n;i++)strs[i]+=strs[i];
  S str=*min_element(strs,strs+n,cmp),res="";
  while(res.size()+str.size()<=k)res+=str;
  res+=str.substr(0,k-res.size());
  printf("%s\n",res.c_str());
}