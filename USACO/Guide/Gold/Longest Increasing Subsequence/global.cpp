#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=200000;

I t_arr[N];
multiset<I>liss[N+1];
vector<pair<I,I>>adds;
vector<I>dp1;
vector<I>dp2;
I n,x;

void cmb(I& a,I b){
  a=max(a,b);
}

void add(I len,I las){
  liss[len].insert(las);
  adds.push_back({len,las});
}

void rem(){
  auto[len,las]=adds.back();
  adds.pop_back();
  liss[len].erase(liss[len].find(las));
}

B chk(I i,I las){
  return liss[i].size()&&liss[i].begin()!=liss[i].upper_bound(las+x-1);
}

I fnd(I las){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m,las))l=m;
    else r=m-1;
  }
  return r;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>x;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++){
    I t=t_arr[i];
    auto it=lower_bound(dp1.begin(),dp1.end(),t);
    I len;
    if(it==dp1.end())dp1.push_back(t),len=dp1.size();
    else len=it-dp1.begin()+1,*it=t;
    add(len,t);
  }
  I res=0;
  for(I i=n-1;i>=0;i--){
    I t=t_arr[i];
    auto it=lower_bound(dp2.begin(),dp2.end(),t,greater<I>());
    I len;
    if(it==dp2.end())dp2.push_back(t),len=dp2.size();
    else len=it-dp2.begin()+1,*it=t;
    rem(),res=max(res,fnd(t)+len);
  }
  printf("%i\n",res);
  return 0;
}