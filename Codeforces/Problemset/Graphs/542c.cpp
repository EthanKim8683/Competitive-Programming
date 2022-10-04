#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=200;

I f_arr[N];
I cycs[N];
I diss[N];
I viss[N];
I t=1;

Lli rnd(Lli a,Lli b){
  return max((a/b+!!(a%b))*b,b);
}

Lli gcd(Lli a,Lli b){
  return b?gcd(b,a%b):a;
}

Lli lcm(Lli a,Lli b){
  return a*b/gcd(a,b);
}

I dfs1(I a,I r,I d=1){
  if(viss[a]>=t)return -1;
  viss[a]=t;
  I b=f_arr[a];
  if(b==r)return d;
  return dfs1(b,r,d+1);
}

I dfs2(I a){
  if(cycs[a]!=-1)return 0;
  return dfs2(f_arr[a])+1;
}

I dfs3(I a){
  if(cycs[a]!=-1)return cycs[a];
  return dfs3(f_arr[a]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I f;cin>>f,f_arr[i]=f-1;}
  for(I i=0;i<n;i++)cycs[i]=dfs1(i,i),t++;
  for(I i=0;i<n;i++)diss[i]=dfs2(i);
  for(I i=0;i<n;i++)cycs[i]=dfs3(i);
  Lli cyc=1;
  for(I i=0;i<n;i++)cyc=lcm(cyc,cycs[i]);
  Lli res=0;
  for(I i=0;i<n;i++)res=max(res,rnd(diss[i],cyc));
  printf("%lli\n",res);
}