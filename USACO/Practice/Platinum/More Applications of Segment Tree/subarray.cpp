#include<iostream>
#include<cstdio>
#include<tuple>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const I LOGN=18;
const I FIXN=1<<LOGN;

struct Nod{I pfx,sfx;Lli val;};

I x_arr[N];
Lli fens[N+1];
Nod segs[2*FIXN];
I n;

void upd1(I i,Lli val){
  for(i++;i<=n;i+=i&-i)fens[i]+=val;
}

void bld1(){
  for(I i=0;i<n;i++)upd1(i,x_arr[i]);
}

Lli qry1(I i){
  Lli res=0;
  for(;i;i-=i&-i)res+=fens[i];
  return res;
}

Nod cmb2(Nod a,Nod b){
  if(a.pfx==-1)return b;
  if(b.pfx==-1)return a;
  Lli val1=qry1(a.pfx),val2=qry1(b.pfx);
  Lli val3=qry1(a.sfx),val4=qry1(b.sfx);
  return{
    val1<val2?a.pfx:b.pfx,
    val3>val4?a.sfx:b.sfx,
    max(max(a.val,b.val),val4-val1)
  };
}

void upd2(I i){
  for(i+=FIXN;i>1;i>>=1)
    segs[i>>1]=cmb2(segs[i&~1],segs[i|1]);
}

void bld2(){
  for(I i=0;i<FIXN;i++)segs[i+FIXN]={min(i,n),min(i,n),0};
  for(I i=FIXN-1;i>0;i--)
    segs[i]=cmb2(segs[i<<1],segs[i<<1|1]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  bld1(),bld2();
  while(m--){
    I k,x;cin>>k>>x,k--;
    upd1(k,x-x_arr[k]);
    upd2(k+1);
    x_arr[k]=x;
    printf("%lli\n",max((Lli)0,segs[1].val));
  }
  return 0;
}