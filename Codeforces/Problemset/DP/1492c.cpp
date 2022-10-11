#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I M=2e5;

I dp1[M],dp2[M];
set<I>inds[26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  S s;cin>>s;
  S t;cin>>t;
  for(I i=0;i<n;i++)inds[s[i]-'a'].insert(i);
  I l=-1,r=n;
  for(I i=0;i<m;i++)dp1[i]=l=*inds[t[i]-'a'].upper_bound(l);
  for(I i=m-1;i>=0;i--)dp2[i]=r=*--inds[t[i]-'a'].lower_bound(r);
  I res=0;
  for(I i=0;i+1<m;i++)res=max(res,dp2[i+1]-dp1[i]);
  printf("%i\n",res);
}