#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N+1];
I tots[N+1];
I pars[N+1];
I maxs[N+1];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  maxs[a]=max(maxs[a],maxs[b]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,n+1,-1);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(maxs,maxs+n+1,0);
  I m;cin>>m;
  while(m--){
    I t;cin>>t;
    if(t==1){
      I p,x;cin>>p>>x,p--;
      while(x){
        p=maxs[fnd(p)];
        if(p==n)break;
        I dif=min(a_arr[p]-tots[p],x);
        tots[p]+=dif,x-=dif;
        if(tots[p]==a_arr[p])uni(p,p+1);
      }
    }
    if(t==2){
      I k;cin>>k,k--;
      printf("%i\n",tots[k]);
    }
  }
}