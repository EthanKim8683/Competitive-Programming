#include<bits/stdc++.h>

using namespace std;

using I=int;
using Llu=long long unsigned;
using B=bool;

vector<I>xors;
vector<I>subs;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Llu a;cin>>a;
  Llu b;cin>>b;
  if(a<b)printf("-1\n"),exit(0);
  Llu c=a-b;
  I len=0;
  for(Llu i=a;i;i/=2)len++;
  for(Llu i=b,j=0;j<len;j++,i/=2)xors.push_back(i%2);
  for(Llu i=c,j=0;j<len;j++,i/=2)subs.push_back(i%2);
  while(subs.size()<xors.size())subs.push_back(0);
  reverse(xors.begin(),xors.end());
  reverse(subs.begin(),subs.end());
  I n=xors.size();
  Llu res=0;
  B vld=1;
  for(I i=0;i<n;i++)if(subs[i]==1){
    if(i+1>=n||xors[i+1]!=0){vld=0;break;}
    res|=(Llu)1<<(n-2-i);
  }
  if(!vld)printf("-1\n"),exit(0);
  printf("%llu %llu\n",res,a-res);
}