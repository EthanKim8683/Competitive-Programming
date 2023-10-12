#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I Q=3e5;
const I K=548;
I a_arr[N];
pair<I,I>qrys[Q];
vector<I>inds[(N+K-1)/K];
vector<I>cons[N];
I fens[N+1];
B uses[N];
I ress[N];
I pars[N];
I l1,r1,cur;
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
B cmp(I a,I b){
  return qrys[a]>qrys[b];
}
void adl(){
  l1--;
  for(auto i:cons[l1])uses[i]=1,cur+=i<r1;
}
void adr(){
  cur+=uses[r1],r1++;
}
void rmr(){
  r1--,cur-=uses[r1];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<q;i++){
    I x,y;cin>>x>>y,y=n-y;
    qrys[i]={x,y};
    inds[y/K].push_back(i);
  }
  for(I i=0;i<n;i++){
    I req=i-(a_arr[i]-1);
    if(req<0||req>qry(n))continue;
    I l=0,r=i;
    while(l<r){
      I m=l+(r-l+1)/2;
      qry(i)-qry(m)>=req?l=m:r=m-1;
    }
    cons[l].push_back(i),upd(l+1,1);
  }
  for(I i=0;i<(n+K-1)/K;i++){
    sort(inds[i].begin(),inds[i].end(),cmp);
    l1=n,r1=n,cur=0;
    fill_n(uses,n,0);
    for(auto j:inds[i]){
      auto[l2,r2]=qrys[j];
      while(l2<l1)adl();
      while(r2>r1)adr();
      while(r2<r1)rmr();
      ress[j]=cur;
    }
  }
  for(I i=0;i<q;i++)printf("%i\n",ress[i]);
}
/*
for an index i, it is possible to remove its corresponding element if i - a[i]
is non-negative and less than or equal to the number of removable j such that
j < i

this is because i can always be removed after the (i - a[i])-th removal, as no
j will be affected by this, since j < i

we can solve queries using Mo's algorithm, keeping track of which elements
become removable at which left bound
*/