#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using S=string;

I pars[26];
vector<pair<I,I>>ress;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S a;cin>>a;
  S b;cin>>b;
  fill_n(pars,26,-1);
  for(I i=0;i<n;i++)
    uni(a[i]-'a',b[i]-'a');
  for(I i=0;i<26;i++){
    if(siz(i)==1)continue;
    I j=fnd(i);
    if(i!=j)ress.push_back({i,j});
  }
  printf("%i\n",ress.size());
  for(auto[i,j]:ress)
    printf("%c %c\n",i+'a',j+'a');
  return 0;
}