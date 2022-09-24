#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=200000;
const I M=200000;

I pars[N+M];
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  fill_n(pars,n+m,-1);
  cnt=n+m;
  for(I i=0;i<q;i++){
    I r,c;cin>>r>>c,r--,c--;
    uni(r,c+n);
  }
  printf("%i\n",cnt-1);
  return 0;
}