#include<iostream>
#include<cstdio>
#include<vector>
#include<set>

using namespace std;

using I=int;

vector<I>unvs;
set<pair<I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  if(k%2==0){printf("NO\n");return 0;}
  if(k==1){printf("YES\n2 1\n1 2\n");return 0;}
  I u=k+2;
  for(I i=0;i<k+1;i++)for(I j=i+1;j<k+1;j++)
    ress.insert({i+0,j+0});
  for(I i=0;i<k+1;i++)unvs.push_back(i+0);
  for(I i=0;i<k-1;i+=2){
    I a=unvs.back();unvs.pop_back();
    I b=unvs.back();unvs.pop_back();
    ress.erase({b,a});
    ress.insert({b,k+1+0});
    ress.insert({a,k+1+0});
  }
  unvs.clear();
  for(I i=0;i<k+1;i++)for(I j=i+1;j<k+1;j++)
    ress.insert({i+u,j+u});
  for(I i=0;i<k+1;i++)unvs.push_back(i+u);
  for(I i=0;i<k-1;i+=2){
    I a=unvs.back();unvs.pop_back();
    I b=unvs.back();unvs.pop_back();
    ress.erase({b,a});
    ress.insert({b,k+1+u});
    ress.insert({a,k+1+u});
  }
  ress.insert({k+1+0,k+1+u});
  printf("YES\n");
  printf("%i %i\n",(k+2)*2,ress.size());
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  return 0;
}