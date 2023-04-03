#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100000;
const I Q=100000;
const I SQTN=317;
I t_arr[N];
I a_arr[N];
pair<I,I>qrys[Q];
vector<Lli>cpss;
vector<pair<I,I>>reqs;
Lli ress[Q];
vector<I>inds[SQTN];
Lli ps[N+1];
I cnts[N+1];
Lli res=0;
I cps(Lli x){
  if(!binary_search(cpss.begin(),cpss.end(),x))return-1;
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
B cmp(I a,I b){
  return qrys[a].second<qrys[b].second;
}
void add1(I x){
  I y=reqs[x].first;
  if(y!=-1)res+=cnts[y];
  cnts[x]++;
}
void rem1(I x){
  cnts[x]--;
  I y=reqs[x].first;
  if(y!=-1)res-=cnts[y];
}
void add2(I x){
  I y=reqs[x].second;
  if(y!=-1)res+=cnts[y];
  cnts[x]++;
}
void rem2(I x){
  cnts[x]--;
  I y=reqs[x].second;
  if(y!=-1)res-=cnts[y];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+(t_arr[i]==1?1:-1)*a_arr[i];
  for(I i=0;i<n+1;i++)cpss.push_back(ps[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(auto x:cpss)reqs.push_back({cps(x-k),cps(x+k)});
  for(I i=0;i<n+1;i++)ps[i]=cps(ps[i]);
  I siz=sqrt(n);
  I q;cin>>q;
  for(I i=0;i<q;i++){
    I l,r;cin>>l>>r,l--,r--;
    qrys[i]={l,r+1};
    inds[l/siz].push_back(i);
  }
  I l1=0,r1=0;
  add1(ps[0]);
  for(I i=0;i<(n+siz-1)/siz;i++){
    sort(inds[i].begin(),inds[i].end(),cmp);
    for(auto j:inds[i]){
      auto[l2,r2]=qrys[j];
      while(r1<r2)add1(ps[++r1]);
      while(l1>l2)add2(ps[--l1]);
      while(l1<l2)rem2(ps[l1++]);
      while(r1>r2)rem1(ps[r1--]);
      ress[j]=res;
    }
  }
  for(I i=0;i<q;i++)printf("%lli\n",ress[i]);
}