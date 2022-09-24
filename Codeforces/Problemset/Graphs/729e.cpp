#include<iostream>
#include<cstdio>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I a_arr[N];
multiset<I>unvs;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,s;cin>>n>>s,s--;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I res=0;
  if(a_arr[s]!=0)a_arr[s]=0,res++;
  for(I i=0;i<n;i++)unvs.insert(a_arr[i]);
  unvs.erase(unvs.find(0));
  I rem=0;
  while(unvs.find(0)!=unvs.end())
    unvs.erase(unvs.find(0)),rem++;
  res+=rem;
  I cur=0;
  while(unvs.size()){
    if(unvs.find(cur)!=unvs.end()){
      unvs.erase(unvs.find(cur));
      continue;
    }
    cur++;
    if(unvs.find(cur)!=unvs.end()){
      unvs.erase(unvs.find(cur));
      continue;
    }
    if(rem){rem--;continue;}
    unvs.erase(prev(unvs.end()));
    res++;
  }
  printf("%i\n",res);
  return 0;
}