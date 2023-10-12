#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  I x=0,cnt=0;
  for(I i=0;i<n;i++)cnt+=s[i]=='W';
  for(I i=0;i<n;i++)x=max(x,cnt),cnt+=(s[i+n]=='W')-(s[i]=='W');
  printf("%i\n",x);
}
/*
x can always be the maximum number of bottles of white wine among all
subsegments of n wines because no subsegment smaller than n will be needed to
achieve this many number of bottles of white wine (otherwise, there would be
a larger maximum) and every starting index before and ending index after the
maximum subsegment will have access to at least x wines for a total of n - 1
indices in addition to the maximal subsegment
*/