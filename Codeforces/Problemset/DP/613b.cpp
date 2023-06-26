#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100000;
I a_arr[N];
I inds[N];
Lli ps1[N+1],ps2[N];
B cmp(I a,I b){
  return a_arr[a]>a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,a,c1,c2;Lli m;cin>>n>>a>>c1>>c2>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++)ps1[i+1]=ps1[i]+a-a_arr[inds[i]];
  if(ps1[n]<=m){
    printf("%lli\n",(Lli)n*c1+(Lli)a*c2);
    for(I i=0;i<n;i++)printf("%i ",a);
    exit(0);
  }
  for(I i=n-1;i>0;i--)ps2[i-1]=ps2[i]+(Lli)(a_arr[inds[i-1]]-a_arr[inds[i]])*(n-i);
  tuple<Lli,I,I>res={0,0,0};
  for(I i=0,j=0;i<n;i++){
    j=max(j,i);
    while(j<n&&ps1[i]+ps2[j]>m)j++;
    if(j>=n)break;
    Lli rem=m-ps1[i]-ps2[j];
    if(rem>=0){
      Lli low=a_arr[inds[j]]+rem/(n-j);
      res=max(res,{(Lli)i*c1+low*c2,i,low});
    }
  }
  auto[tot,cnt,low]=res;
  for(I i=0;i<cnt;i++)a_arr[inds[i]]=a;
  printf("%lli\n",tot);
  for(I i=0;i<n;i++)printf("%i ",max(a_arr[i],low));
}