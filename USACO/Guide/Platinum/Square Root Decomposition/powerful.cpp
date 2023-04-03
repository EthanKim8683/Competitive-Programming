#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=200000;
const I SQTN=448;
const I A=1e6;
const I T=200000;
I a_arr[N];
pair<I,I>qrys[T];
vector<I>inds[SQTN];
Lli ress[T];
I cnts[A+1];
Lli res=0;
B cmp(I a,I b){
  return qrys[a].second<qrys[b].second;
}
void add(I a){
  res+=(2*cnts[a]+1)*a;
  cnts[a]++;
}
void rem(I a){
  cnts[a]--;
  res-=(2*cnts[a]+1)*a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,t;cin>>n>>t;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I siz=sqrt(n);
  for(I i=0;i<t;i++){
    I l,r;cin>>l>>r,l--,r--;
    qrys[i]={l,r};
    inds[l/siz].push_back(i);
  }
  I l1=0,r1=0;
  add(a_arr[0]);
  for(I i=0;i<(n+siz-1)/siz;i++){
    sort(inds[i].begin(),inds[i].end(),cmp);
    for(auto j:inds[i]){
      auto[l2,r2]=qrys[j];
      while(r1<r2)add(a_arr[++r1]);
      while(l1>l2)add(a_arr[--l1]);
      while(r1>r2)rem(a_arr[r1--]);
      while(l1<l2)rem(a_arr[l1++]);
      ress[j]=res;
    }
  }
  for(I i=0;i<t;i++)printf("%lli\n",ress[i]);
}