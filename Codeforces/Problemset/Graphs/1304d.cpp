#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using S=string;

const I N=2e5;

I pars[N];
I typs[N];
I ress1[N],ress2[N];
I inds1[N],inds2[N];

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
    S s;cin>>s;
    fill_n(pars,n,-1);
    I r=0;
    while(r<n-1){
      I l=r;
      while(++r<n-1&&s[r]==s[l])uni(l+1,r+1);
    }
    uni(0,1);
    for(I i=1;i<n;i++)typs[fnd(i)]=s[i-1]=='<';
    I low=0;
    for(I i=n-1;i>=0;i--)if(!typs[fnd(i)])
      ress1[i]=ress2[i]=low++;
    I cur=low;
    for(I i=n-1;i>=0;i--)if(i==fnd(i)&&typs[fnd(i)])
      cur+=siz(i),inds1[i]=cur;
    cur=low;
    for(I i=0;i<n;i++)if(i==fnd(i)&&typs[fnd(i)])
      inds2[i]=cur,cur+=siz(i);
    for(I i=n-1;i>=0;i--)if(typs[fnd(i)])
      ress1[i]=--inds1[fnd(i)];
    for(I i=0;i<n;i++)if(typs[fnd(i)])
      ress2[i]=inds2[fnd(i)]++;
    for(I i=0;i<n;i++)printf("%i ",ress1[i]+1);
    printf("\n");
    for(I i=0;i<n;i++)printf("%i ",ress2[i]+1);
    printf("\n");
  }
  return 0;
}