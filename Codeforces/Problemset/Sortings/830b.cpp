#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
const I A=100000;
I a_arr[N];
vector<I>inds[A+1];
I fens[N+1];
I pre=0;
I n;
B cmp(I a,I b){
  return(a-pre+n)%n<(b-pre+n)%n;
}
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)inds[a_arr[i]].push_back(i);
  for(I i=0;i<n;i++)upd(i+1,1);
  Lli res=n;
  for(I i=1;i<=A;i++){
    sort(inds[i].begin(),inds[i].end(),cmp);
    for(auto j:inds[i]){
      upd(j+1,-1);
      if(pre<j)res+=qry(j+1)-qry(pre);
      if(pre>j)res+=qry(n)-qry(pre)+qry(j+1);
      pre=j;
    }
  }
  printf("%lli\n",res);
}