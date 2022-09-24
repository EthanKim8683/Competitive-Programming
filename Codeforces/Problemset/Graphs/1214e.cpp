#include<iostream>
#include<cstdio>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100000;

I d_arr[N];
vector<I>ques[2*N];
I inds[N];
vector<pair<I,I>>ress;

B cmp(I a,I b){
  return d_arr[a]>d_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  I a=-1;
  for(I i=0;i<n;i++){
    I b=inds[i];
    if(a!=-1)ress.push_back({a,2*b});
    for(auto c:ques[i])ress.push_back({a,2*c+1});
    ques[i+d_arr[b]].push_back(b);
    a=2*b;
  }
  for(I i=n;i<2*n;i++){
    if(!ques[i].size())break;
    I b=ques[i].back();ques[i].pop_back();
    ress.push_back({a,2*b+1});
    for(auto c:ques[i])ress.push_back({a,2*c+1});
    a=2*b+1;
  }
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
}