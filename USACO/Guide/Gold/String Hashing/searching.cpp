#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using I128=__int128;
using S=string;
using B=bool;
const I L=200000;
const Lli BAS=(1ll<<31)-1;
const Lli MOD=(1ll<<61)-1;
Lli pows[L];
Lli hshs[L+1];
set<Lli>ress;
I tars[26];
I cnts[26];
void bld(S str){
  pows[0]=1;
  for(I i=1;i<str.size();i++)pows[i]=(I128)pows[i-1]*BAS%MOD;
  for(I i=0;i<str.size();i++)hshs[i+1]=((I128)hshs[i]*BAS+str[i])%MOD;
}
Lli qry(I l,I r){
  return((hshs[r]-(I128)hshs[l]*pows[r-l])%MOD+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S n;cin>>n;
  S h;cin>>h;
  for(auto c:n)tars[c-'a']++;
  bld(h);
  for(I i=0;i<h.size();i++){
    cnts[h[i]-'a']++;
    if(i>=n.size())cnts[h[i-n.size()]-'a']--;
    B vld=1;
    for(I i=0;i<26;i++)vld&=tars[i]==cnts[i];
    if(vld)ress.insert(qry(i-n.size()+1,i+1));
  }
  printf("%i\n",ress.size());
}