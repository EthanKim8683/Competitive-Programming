#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=5e5;
const I LOGN=19;
const I MAX=1e9;
const I MIN=-1e9;

I a_arr[N];
I spas1[N][LOGN],spas2[N][LOGN];
I lefs1[N],lefs2[N];
I rigs1[N],rigs2[N];
map<I,vector<I>>vals;
I n;

void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n;j++)
    spas1[j][i]=min(spas1[j][i-1],spas1[j+(1<<(i-1))][i-1]);
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n;j++)
    spas2[j][i]=max(spas2[j][i-1],spas2[j+(1<<(i-1))][i-1]);
}

I qry1(I l,I r){
  I dis=31-__builtin_clz(++r-l);
  return min(spas1[l][dis],spas1[r-(1<<dis)][dis]);
}

I qry2(I l,I r){
  I dis=31-__builtin_clz(++r-l);
  return max(spas2[l][dis],spas2[r-(1<<dis)][dis]);
}

I fnd1(I i){
  I a=a_arr[i];
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    if(qry1(m,i)==a)r=m;
    else l=m+1;
  }
  return l;
}

I fnd2(I i){
  I a=a_arr[i];
  I l=i,r=n-1;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(qry1(i,m)==a)l=m;
    else r=m-1;
  }
  return l;
}

I fnd3(I i){
  I a=a_arr[i];
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    if(qry2(m,i)==a)r=m;
    else l=m+1;
  }
  return l;
}

I fnd4(I i){
  I a=a_arr[i];
  I l=i,r=n-1;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(qry2(i,m)==a)l=m;
    else r=m-1;
  }
  return l;
}

Lli cnt(I i,I j){
  I lef1=max(lefs1[i],lefs2[j]);
  I rig1=min(rigs1[i],rigs2[j]);
  I lef2=min(i,j)-lef1+1;
  I rig2=rig1-max(i,j)+1;
  if(lef2<=0||rig2<=0)return 0;
  return lef2*rig2;
}

Lli tst(I i,I j){
  if(!vals.count(i))return 0;
  Lli res=0;
  for(auto x:vals[i])res+=cnt(x,j);
  return res;
}

Lli fac(){
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    for(I j=1;j*j<=a;j++){
      if(a%j==0){
        I k=a/j;
        res+=tst(j,i);
        if(k!=j)res+=tst(k,i);
      }
    }
  }
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    vals.clear();
    for(I i=0;i<n;i++)for(I j=0;j<LOGN;j++)spas1[i][j]=MAX;
    for(I i=0;i<n;i++)for(I j=0;j<LOGN;j++)spas2[i][j]=MIN;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)spas1[i][0]=spas2[i][0]=a_arr[i];
    for(I i=0;i<n;i++)vals[a_arr[i]].push_back(i);
    bld();
    for(I i=0;i<n;i++){
      lefs1[i]=fnd1(i),rigs1[i]=fnd2(i);
      lefs2[i]=fnd3(i),rigs2[i]=fnd4(i);
    }
    printf("%lli\n",fac());
  }
}