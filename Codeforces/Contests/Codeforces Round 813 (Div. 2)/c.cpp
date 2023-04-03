#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I A=N;

I a_arr[N];
I maxs[A+1];
B opds[A+1];
I upp=0;
I res=0;

void cmb(I& a,I b){
  a=max(a,b);
}

I qry(I a){
  return opds[a]?0:a;
}

void upd(I a){
  if(opds[a])return;
  opds[a]=true;
  cmb(upp,maxs[a]);
  res++;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(maxs,n+1,0);
    fill_n(opds,n+1,false);
    upp=0,res=0;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cmb(maxs[a_arr[i]],i+1);
    I low=0;
    for(I i=0;i+1<n;){
      I a=qry(a_arr[i]),b=qry(a_arr[i+1]);
      if(b<a){
        upd(a);
        for(I j=low;j<upp;j++)upd(a_arr[j]);
        i=upp;
        low=upp;
      }else i++;
    }
    printf("%i\n",res);
  }
  return 0;
}