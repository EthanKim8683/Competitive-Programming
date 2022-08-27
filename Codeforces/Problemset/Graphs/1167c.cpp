#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=5e5;

I pars[N];

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
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I k;cin>>k;
    if(!k)continue;
    I r;cin>>r,r--;
    for(I j=1;j<k;j++){
      I d;cin>>d,d--;
      uni(r,d);
    }
  }
  for(I i=0;i<n;i++)
    printf("%i ",siz(i));
  return 0;
}