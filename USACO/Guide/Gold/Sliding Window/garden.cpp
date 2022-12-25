#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I L=250;
const I W=250;
const I MAX=1e9;

I cels[L][W];
I ps[L][W+1];
I llows[L],lupps[L];
I wlows[W],wupps[W];

I rng(I i,I l,I r){
  return ps[i][r+1]-ps[i][l];
}

void cmb(I& a,I b){
  a=min(a,b);
}

void sto(I llow,I lupp,I wlow,I wupp){
  I per=(lupp-llow+1)+(wupp-wlow+1);
  cmb(llows[llow],per),cmb(lupps[lupp],per);
  cmb(wlows[wlow],per),cmb(wupps[wupp],per);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I l,w;cin>>l>>w;
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I l,w;cin>>l>>w;
    cels[l-1][w-1]++;
  }
  for(I i=0;i<l;i++)
    for(I j=0;j<w;j++)
      ps[i][j+1]=ps[i][j]+cels[i][j];
  fill_n(llows,l,MAX),fill_n(lupps,l,MAX);
  fill_n(wlows,w,MAX),fill_n(wupps,w,MAX);
  for(I i=0;i<w;i++){
    for(I j=i;j<w;j++){
      I a=0,b=0;
      I sum=rng(0,i,j);
      if(sum==k)sto(a,b,i,j);
      while(a<b||b<l-1){
        if(b==l-1)sum-=rng(a++,i,j);
        else if(a==b)sum+=rng(++b,i,j);
        else if(sum<k)sum+=rng(++b,i,j);
        else if(sum>=k)sum-=rng(a++,i,j);
        if(sum==k)sto(a,b,i,j);
      }
    }
  }
  for(I i=l-1;i-1>=0;i--)cmb(llows[i-1],llows[i]);
  for(I i=w-1;i-1>=0;i--)cmb(wlows[i-1],wlows[i]);
  for(I i=0;i+1<l;i++)cmb(lupps[i+1],lupps[i]);
  for(I i=0;i+1<w;i++)cmb(wupps[i+1],wupps[i]);
  I res=MAX;
  for(I i=0;i+1<l;i++)cmb(res,lupps[i]+llows[i+1]);
  for(I i=0;i+1<w;i++)cmb(res,wupps[i]+wlows[i+1]);
  if(res==MAX)printf("NO\n");
  else printf("%i\n",2*res);
  return 0;
}