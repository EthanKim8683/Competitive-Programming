#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e6;
const I M=1e6;
I a_arr[M];
I fens[N+1];
I typs[N];
B rems[N];
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I ith(I i){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry(m)<=i?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++)cin>>a_arr[i];
  I len=0;
  for(I i=0;i<n;i++){
    I t;cin>>t;
    if(t==-1){
      I u=0;
      for(;u<m;u++)if(a_arr[u]-1>=len)break;
      for(I j=u-1;j>=0;j--){
        I k=ith(a_arr[j]-1);
        rems[k]=0,upd(k+1,-1),len--;
      }
    }
    if(t==0)typs[i]=0,rems[i]=1,upd(i+1,1),len++;
    if(t==1)typs[i]=1,rems[i]=1,upd(i+1,1),len++;
  }
  I cnt=0;
  for(I i=0;i<n;i++)if(rems[i])printf("%i",typs[i]),cnt++;
  if(!cnt)printf("Poor stack!");
}