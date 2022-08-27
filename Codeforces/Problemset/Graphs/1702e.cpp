#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I pars[N];
I cnts[N];

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
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(pars,n,-1),fill_n(cnts,n,0);
    B res=true;
    for(I i=0;i<n;i++){
      I a,b;cin>>a>>b,a--,b--;
      uni(a,b);
      res&=a!=b;
      cnts[a]++,cnts[b]++;
    }
    for(I i=0;i<n;i++)res&=cnts[i]==2;
    for(I i=0;i<n;i++)res&=siz(i)%2==0;
    if(res)printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}