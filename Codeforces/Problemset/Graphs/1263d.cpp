#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using B=bool;

I pars[26];
B viss[26];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,26,-1);
  for(I i=0;i<n;i++){
    S s;cin>>s;
    I a=s[0]-'a';
    viss[a]=true;
    for(I j=1;j<s.size();j++){
      I b=s[j]-'a';
      viss[b]=true;
      uni(a,b);
    }
  }
  I res=0;
  for(I i=0;i<26;i++)
    res+=fnd(i)==i&&viss[i];
  printf("%i\n",res);
  return 0;
}