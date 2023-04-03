#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=30000;
const I A=1e6;
const I Q=200000;
const I SQTN=174;
I a_arr[N];
pair<I,I>qrys[Q];
vector<I>inds[SQTN];
I cnts[A+1];
I ress[Q];
I res=0;
B cmp(I a,I b){
  return qrys[a].second<qrys[b].second;
}
void add(I a){
  if(cnts[a]==0)res++;
  cnts[a]++;
}
void rem(I a){
  cnts[a]--;
  if(cnts[a]==0)res--;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I q;cin>>q;
  I siz=sqrt(n);
  for(I i=0;i<q;i++){
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
  for(I i=0;i<q;i++)printf("%i\n",ress[i]);
}