#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
using C=char;
using B=bool;
const I N=1e6;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
Lli pows[N+1];
vector<C>rems;
deque<C>curs;
pair<I,Lli>tar={0,0};
pair<I,Lli>adf(pair<I,Lli>x,C c){
  auto[len,hsh]=x;
  return{len+1,(c*pows[len]+hsh)%MOD};
}
pair<I,Lli>adb(pair<I,Lli>x,C c){
  auto[len,hsh]=x;
  return{len+1,(hsh*BAS+c)%MOD};
}
pair<I,Lli>rem(pair<I,Lli>x,C c){
  auto[len,hsh]=x;
  return{len-1,((hsh-c*pows[len-1])%MOD+MOD)%MOD};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("censor.in","r",stdin);
  freopen("censor.out","w",stdout);
#endif
  pows[0]=1;
  for(I i=0;i<N;i++)pows[i+1]=pows[i]*BAS%MOD;
  S s;cin>>s;
  S t;cin>>t;
  for(I i=0;i<t.size();i++)tar=adb(tar,t[i]);
  pair<I,Lli>cur={0,0};
  for(I i=0;i<s.size();i++){
    cur=adb(cur,s[i]),curs.push_back(s[i]);
    while(cur.first<tar.first&&rems.size()){
      C c=rems.back();rems.pop_back();
      cur=adf(cur,c),curs.push_front(c);
    }
    while(cur.first>tar.first&&curs.size()){
      C c=curs.front();curs.pop_front();
      cur=rem(cur,c),rems.push_back(c);
    }
    if(cur==tar){
      cur={0,0};
      while(curs.size())curs.pop_back();
    }
  }
  for(auto c:rems)printf("%c",c);
  for(auto c:curs)printf("%c",c);
}