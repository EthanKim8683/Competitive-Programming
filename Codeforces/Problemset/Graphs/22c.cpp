#include<iostream>
#include<cstdio>
#include<set>
#include<vector>

using namespace std;

using I=int;
using B=bool;

set<pair<I,I>>ress;
I v;

I fix(I i){
  if(i==1)return v;
  if(i==v)return 1;
  return i;
}

B add(I i,I j){
  if(i>j)swap(i,j);
  if(i==j||ress.find({i,j})!=ress.end())return 0;
  ress.insert({i,j});
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>v,v--;
  for(I i=0;i<n-1;i++)add(i,i+1);
  I cnt=m-(n-1);
  for(I i=0;i<=1&&cnt>0;i++)for(I j=0;j<=1&&cnt>0;j++)cnt-=add(i,j);
  for(I i=1;i<n&&cnt>0;i++)for(I j=1;j<n&&cnt>0;j++)cnt-=add(i,j);
  if(cnt==0)for(auto[i,j]:ress)printf("%i %i\n",fix(i)+1,fix(j)+1);
  else printf("-1\n");
  return 0;
}