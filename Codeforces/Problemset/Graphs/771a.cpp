#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=150000;
const I M=150000;

I pars[N];
I sums[N];
Lli edgs[N];

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
    I a,b;cin>>a>>b,a--,b--;
    sums[a]++,uni(a,b);
  }
  for(I i=0;i<n;i++)
    edgs[fnd(i)]+=sums[i];
  for(I i=0;i<n;i++){
    Lli s=siz(i);
    if(edgs[fnd(i)]!=s*(s-1)/2){
      printf("NO\n");return 0;
    }
  }
  printf("YES\n");
  return 0;
}