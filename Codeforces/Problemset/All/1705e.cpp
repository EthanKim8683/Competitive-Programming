#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I A=2e5;
const I LOGA=18;
const I FIXA=1<<LOGA;
I a_arr[N];
I vals[2*FIXA],dels[2*FIXA];
I siz(I i){
  return 1<<(__builtin_clz(i)-31+LOGA);
}
void app(I i,I val){
  vals[i]+=val*siz(i);
  if(i<FIXA)dels[i]+=val;
}
void dwn(I i){
  if(dels[i])app(i<<1,dels[i]),app(i<<1|1,dels[i]),dels[i]=0;
}
void psh(I i){
  for(I j=LOGA;j>=0;j--)dwn((i+FIXA)>>j);
}
void pll(I i){
  for(i+=FIXA;i>>=1;)vals[i]=vals[i<<1]+vals[i<<1|1]+dels[i]*siz(i);
}
void upd(I l,I r,I val){
  psh(l),psh(r-1);
  for(I i=l+FIXA,j=r+FIXA;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
I qry(I l,I r){
  psh(l),psh(r-1);
  I res=0;
  for(I i=l+FIXA,j=r+FIXA;i<j;i>>=1,j>>=1){
    if(i&1)res+=vals[i++];
    if(j&1)res+=vals[--j];
  }
  return res;
}
void add(I a){
  if(qry(a,a+1)==1){
    I l=a+1,r=FIXA;
    while(l<r){
      I m=l+(r-l+1)/2;
      qry(a,m)==m-a?l=m:r=m-1;
    }
    upd(a,l,-1),upd(l,l+1,1);
  }else{
    upd(a,a+1,1);
  }
}
void rem(I a){
  if(qry(a,a+1)==0){
    I l=a+1,r=FIXA;
    while(l<r){
      I m=l+(r-l+1)/2;
      qry(a,m)==0?l=m:r=m-1;
    }
    upd(a,l,1),upd(l,l+1,-1);
  }else{
    upd(a,a+1,-1);
  }
}
I wlk(){
  I i=1;
  while(i<FIXA){
    dwn(i),i<<=1;
    if(vals[i|1]>0)i|=1;
  }
  return i-FIXA;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)add(a_arr[i]);
  while(q--){
    I k,l;cin>>k>>l,k--;
    rem(a_arr[k]),a_arr[k]=l,add(a_arr[k]);
    printf("%i\n",wlk());
  }
}
/*
for each update l we can use a range update range sum data structure to find
the greatest number x possible based on the parities of l, l + 1, ... x
*/