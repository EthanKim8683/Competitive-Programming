#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=262144;
const I LOGN=18;
const I A=40;
const I MAX=1e9;
I a_arr[N];
I ancs[N][A+LOGN+1];
I main(){
#ifndef ETHANKIM8683
  freopen("262144.in","r",stdin);
  freopen("262144.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fill(&ancs[0][0],&ancs[0][0]+N*(A+LOGN+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ancs[i][a_arr[i]]=i-1;
  I res=*max_element(a_arr,a_arr+n);
  for(I i=1;i<=A+LOGN;i++)for(I j=0;j<n;j++){
    I a=ancs[j][i-1];
    if(a==MAX||a==-1)continue;
    I b=ancs[a][i-1];
    if(b==MAX)continue;
    res=max(res,i);
    ancs[j][i]=b;
  }
  printf("%i\n",res);
}