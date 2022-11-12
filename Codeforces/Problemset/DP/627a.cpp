#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

vector<I>xors;
vector<I>subs;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli s,x;cin>>s>>x;
  Lli y=s-x;
  if(y<0)printf("0\n"),exit(0);
  I len=0;
  for(Lli i=s;i;i/=2)len++;
  for(Lli i=x,j=0;j<len;j++,i/=2)xors.push_back(i%2);
  for(Lli i=y,j=0;j<len;j++,i/=2)subs.push_back(i%2);
  while(subs.size()<xors.size())subs.push_back(0);
  reverse(xors.begin(),xors.end());
  reverse(subs.begin(),subs.end());
  I n=xors.size();
  Lli res=1;
  for(I i=0;i<n;i++)if(subs[i]==1)res&=i+1<n&&xors[i+1]==0;
  res<<=__builtin_popcountll(x);
  if(y==0&&res>=2)res-=2;
  printf("%lli\n",res);
}