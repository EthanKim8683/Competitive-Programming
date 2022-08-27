#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1000;
const I MAX=1e9;

I p_arr[2*N];
I n;

B chk(){
  for(I i=0;i<2*n;i++)if(p_arr[i]!=i)return false;
  return true;
}

void ope(B b){
  if(b)for(I i=0;i<n;i++)swap(p_arr[i],p_arr[i+n]);
  else for(I i=0;i<n;i++)swap(p_arr[i*2],p_arr[i*2+1]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<2*n;i++){I p;cin>>p,p_arr[i]=p-1;}
  I res=MAX;
  for(I i=0;i<2*n;i++,ope(i%2))
    if(chk())res=min(res,i);
  for(I i=0;i<2*n;i++,ope((i+1)%2))
    if(chk())res=min(res,i);
  if(res==MAX)printf("-1\n");
  else printf("%i\n",res);
  return 0;
}