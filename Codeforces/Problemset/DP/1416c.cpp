#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
const I LOGA=30;
I a_arr[N];
I inds[N];
vector<I>cpss;
I fens[N+1];
I cnts[2];
I t=0;
I n;
B cmp(I a,I b){
  I dif=(a_arr[a]>>(t+1))-(a_arr[b]>>(t+1));
  if(dif==0)return a<b;
  return dif<0;
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
  Lli inv=0;
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    I a=lower_bound(cpss.begin(),cpss.end(),a_arr[i])-cpss.begin();
    upd(a+1,1),inv+=qry(n)-qry(a+1);
  }
  iota(inds,inds+n,0);
  I res=0;
  for(;t<LOGA;t++){
    sort(inds,inds+n,cmp);
    Lli cst=0;
    cnts[a_arr[inds[0]]>>t&1]++;
    for(I i=1;i<n;i++){
      if((a_arr[inds[i-1]]^a_arr[inds[i]])>>(t+1))cst+=(Lli)cnts[0]*cnts[1],fill_n(cnts,2,0);
      I a=a_arr[inds[i]]>>t&1;
      if(!a)cst-=2*cnts[1];
      cnts[a]++;
    }
    cst+=(Lli)cnts[0]*cnts[1],fill_n(cnts,2,0);
    if(cst<0)inv+=cst,res|=1<<t;
  }
  printf("%lli %i\n",inv,res);
}