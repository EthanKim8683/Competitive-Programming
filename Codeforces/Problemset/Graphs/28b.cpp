#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100;

I p_arr[N],d_arr[N];
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

B con(I a,I b){
  return fnd(a)==fnd(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
  for(I i=0;i<n;i++)cin>>d_arr[i];
  for(I i=0;i<n;i++){
    I d=d_arr[i];
    if(i-d>=0)uni(i,i-d);
    if(i+d<n)uni(i,i+d);
  }
  B res=true;
  for(I i=0;i<n;i++)
    res&=con(i,p_arr[i]);
  if(res)printf("YES\n");
  else printf("NO\n");
  return 0;
}