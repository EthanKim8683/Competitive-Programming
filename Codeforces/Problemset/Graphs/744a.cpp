#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1000;
const I M=100000;
const I K=N;

pair<I,I>pais[M];
I c_arr[K];
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

I con(I i){
  return i*(i-1)/2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(pars,n,-1);
  for(I i=0;i<k;i++){I c;cin>>c,c_arr[i]=c-1;}
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v;u--,v--;
    uni(u,v),pais[i]={u,v};
  }
  I l=0,r=n,res=0;
  for(I i=0;i<k;i++){
    I s=siz(c_arr[i]);
    l=max(l,s),res+=con(s),r-=s;
  }
  printf("%i\n",res+con(l+r)-con(l)-m);
  return 0;
}