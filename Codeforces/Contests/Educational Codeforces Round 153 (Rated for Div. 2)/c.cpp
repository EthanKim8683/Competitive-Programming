#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
I p_arr[N];
I fens[2][N+1];
I n;
void upd(I t,I i,I val){
  for(;i<=n;i+=i&-i)fens[t][i]+=val;
}
I qry(I t,I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[t][i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    for(I i=0;i<2;i++)fill_n(fens[i],n,0);
    I res=0;
    for(I i=0;i<n;i++){
      I p=p_arr[i]-1;
      if(qry(0,p)){
        if(qry(1,p)==qry(0,p)){
          res++;
        }else{
          upd(1,p+1,1);
        }
      }else{
        upd(1,p+1,1);
      }
      upd(0,p+1,1);
    }
    printf("%i\n",res);
  }
}