#include<iostream>
#include<cstdio>
#include<queue>
#include<unordered_map>

using namespace std;

using I=int;
using S=string;

const I K=100;

unordered_map<S,I>deps;
queue<S>que;

void add(I d,S s){
  if(deps.count(s))return;
  que.push(s),deps.insert({s,d});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  S s;cin>>s;
  add(0,s);
  I cnt=0,tot=0;
  while(que.size()){
    auto a=que.front();que.pop();
    tot+=deps[a];
    if(++cnt==k)printf("%i\n",tot),exit(0);
    I l=a.size();
    for(I i=0;i<l;i++)
      add(deps[a]+1,a.substr(0,i)+a.substr(i+1,l));
  }
  printf("-1\n");
}