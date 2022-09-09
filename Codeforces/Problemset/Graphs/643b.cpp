#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

B viss[N];
vector<I>pats;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  I a,b,c,d;cin>>a>>b>>c>>d,a--,b--,c--,d--;
  if(n==4||k<n+1){printf("-1\n");return 0;}
  viss[a]=viss[b]=viss[c]=viss[d]=true;
  for(I i=0;i<n;i++)if(!viss[i])pats.push_back(i);
  I m=pats.back();pats.pop_back();
  printf("%i ",a+1);
  for(auto pat:pats)printf("%i ",pat+1);
  printf("%i %i %i %i",c+1,m+1,d+1,b+1);
  reverse(pats.begin(),pats.end());
  printf("\n");
  printf("%i ",c+1);
  for(auto pat:pats)printf("%i ",pat+1);
  printf("%i %i %i %i",a+1,m+1,b+1,d+1);
  return 0;
}