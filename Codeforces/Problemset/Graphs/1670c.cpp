#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e5;
const Lli MOD=1e9+7;

I a_arr[N],b_arr[N];
B viss[N];
I pars[N];
Lli pows[N+1];

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
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(viss,n,false);
    fill_n(pars,n,-1);
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<n;i++){I b;cin>>b,b_arr[i]=b-1;}
    for(I i=0;i<n;i++)uni(a_arr[i],b_arr[i]);
    for(I i=0;i<n;i++){
      I d;cin>>d;
      if(d>0)viss[fnd(d-1)]=true;
    }
    I cnt=0;
    for(I i=0;i<n;i++)cnt+=fnd(i)==i&&!viss[i]&&siz(i)>1;
    printf("%lli\n",pows[cnt]);
  }
  return 0;
}