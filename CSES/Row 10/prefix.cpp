#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

const I N=2e5;

I x_arr[N];
I bits1[N+1];
I bits2[N+1];
I n;

void upd1(I i,I val){
  for(i++;i<=n;i+=i&-i)bits1[i]+=val;
}

void upd2(I i,I val){
  for(i++;i<=n;i+=i&-i)bits2[i]+=val;
}

void upd3(I i,I val){
  upd1(0,val),upd1(i+1,-val);
  upd2(i+1,i*val);
}

void upd(I l,I r,I val){
  upd3(l,val),upd3(r+1,-val);
}

I qry1(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=bits1[i];
  return res;
}

I qry2(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=bits2[i];
  return res;
}

I qry3(I i){
  return qry1(i)*i+qry2(i);
}

I qry(I l,I r){
  return qry3(r+1)-qry3(l);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  
  return 0;
}