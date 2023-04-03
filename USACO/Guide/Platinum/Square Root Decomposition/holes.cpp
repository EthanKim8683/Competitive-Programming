#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
I a_arr[N];
tuple<I,I,I>jmps[N];
I siz;
I n;
void upd(I i){
  I low=i*siz,upp=min((i+1)*siz,n);
  for(I j=upp-1;j>=low;j--){
    I k=j+a_arr[j];
    if(k>=upp){jmps[j]={k,j,1};continue;}
    auto[x,y,z]=jmps[k];
    jmps[j]={x,y,z+1};
  }
}
pair<I,I>qry(I i){
  I res1=i,res2=0;
  while(i<n){
    auto[x,y,z]=jmps[i];
    i=x,res1=y,res2+=z;
  }
  return{res1,res2};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  siz=sqrt(n);
  for(I i=0;i<(n+siz-1)/siz;i++)upd(i);
  while(m--){
    I t;cin>>t;
    if(t==0){
      I a,b;cin>>a>>b,a--;
      a_arr[a]=b,upd(a/siz);
    }
    if(t==1){
      I a;cin>>a,a--;
      auto[res1,res2]=qry(a);
      printf("%i %i\n",res1+1,res2);
    }
  }
}