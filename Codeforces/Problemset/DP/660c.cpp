#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=3e5;

I a_arr[N];
I cnts[2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  tuple<I,I,I,I>res={0,-1,-1,-1};
  I l=0,r=0;
  cnts[0]=cnts[1]=0;
  cnts[a_arr[0]]=1;
  if(cnts[0]<=k)res=max(res,{r-l+1,l,r,1});
  while(l<r||r<n-1){
    if(r==n-1)cnts[a_arr[l++]]--;
    else if(l==r)cnts[a_arr[++r]]++;
    else if(cnts[0]>k)cnts[a_arr[l++]]--;
    else if(cnts[0]<=k)cnts[a_arr[++r]]++;
    if(cnts[0]<=k)res=max(res,{r-l+1,l,r,1});
  }
  auto[len,a,b,t]=res;
  for(I i=a;i<=b;i++)a_arr[i]=t;
  printf("%i\n",len);
  for(I i=0;i<n;i++)printf("%i ",a_arr[i]);
}