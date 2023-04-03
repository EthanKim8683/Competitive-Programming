#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
const I Q=100000;
const I SQTN=317;
I a_arr[N];
pair<I,I>qrys[Q];
vector<I>inds[SQTN];
vector<I>cpss;
I fens[N+1];
Lli ress[Q];
Lli res=0;
I n;
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
B cmp(I a,I b){
  return qrys[a].second<qrys[b].second;
}
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
void add1(I x){
  res+=qry(n)-qry(x+1);
  upd(x+1,1);
}
void rem1(I x){
  upd(x+1,-1);
  res-=qry(n)-qry(x+1);
}
void add2(I x){
  res+=qry(x)-qry(0);
  upd(x+1,1);
}
void rem2(I x){
  upd(x+1,-1);
  res-=qry(x)-qry(0);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I siz=sqrt(n);
  for(I i=0;i<q;i++){
    I l,r;cin>>l>>r;
    qrys[i]={l,r};
    inds[l/siz].push_back(i);
  }
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++)a_arr[i]=cps(a_arr[i]);
  I l1=0,r1=0;
  for(I i=0;i<(n+siz-1)/siz;i++){
    sort(inds[i].begin(),inds[i].end(),cmp);
    for(auto j:inds[i]){
      auto[l2,r2]=qrys[j];
      while(r1<r2)add1(a_arr[r1++]);
      while(l1>l2)add2(a_arr[--l1]);
      while(r1>r2)rem1(a_arr[--r1]);
      while(l1<l2)rem2(a_arr[l1++]);
      ress[j]=res;
    }
  }
  for(I i=0;i<q;i++)printf("%lli\n",ress[i]);
}