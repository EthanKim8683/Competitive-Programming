#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=500;

I a_arr[N];
vector<I>ones,mors;
vector<I>pats;
vector<pair<I,I>>ress;
I cur=0;
I n;

void add1(I i){
  I j=pats.back();
  ress.push_back({j,i});
  pats.push_back(i);
  a_arr[j]--,a_arr[i]--;
}

B add2(I i){
  while(cur<pats.size()&&!a_arr[pats[cur]])cur++;
  if(cur>=pats.size())return 0;
  I j=pats[cur];
  ress.push_back({j,i});
  a_arr[j]--,a_arr[i]--;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    if(a_arr[i]==1)ones.push_back(i);
    else mors.push_back(i);
  }
  if(ones.size())pats.push_back(ones.back()),ones.pop_back();
  else pats.push_back(mors.back()),mors.pop_back();
  while(mors.size())add1(mors.back()),mors.pop_back();
  if(ones.size())add1(ones.back()),ones.pop_back();
  while(ones.size()){
    if(!add2(ones.back())){printf("NO\n");return 0;}
    ones.pop_back();
  }
  printf("YES %i\n",pats.size()-1);
  printf("%i\n",ress.size());
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  return 0;
}