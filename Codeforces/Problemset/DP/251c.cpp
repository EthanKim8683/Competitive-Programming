#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I K=15;
const I N=8648640;
const I M=9;
const I X=6;
const I Y=30030;
const I MAX=1e9;
I facs[]{2,3,4,5,7,8,9,11,13};
I bits[]{1,2,6,24,120,840,6720,60480,665280,8648640};
I encs[N],decs[N];
I diss[N];
queue<pair<I,I>>ques;
I m,n;
I enc(Lli x){
  return encs[(x%n+n)%n];
}
I dec(I x){
  return decs[x];
}
void add(I a,I dis){
  if(dis>=diss[a])return;
  ques.push({diss[a]=dis,a});
}
Lli gcd(Lli a,Lli b){
  return b?gcd(b,a%b):a;
}
Lli lcm(Lli a,Lli b){
  return a*b/gcd(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli a,b;I k;cin>>a>>b>>k;
  for(I i=0;i<M;i++)if(facs[i]<=k)m=i+1,n=bits[m];
  fill_n(decs,n,-1);
  for(I i=n-1;i>=0;i--){
    I enc=0;
    for(I j=0;j<m;j++)enc+=i%facs[j]*bits[j];
    decs[enc]=i,encs[i]=enc;
  }
  Lli cyc=1;
  for(I i=0;i<m;i++)cyc=lcm(cyc,facs[i]);
  Lli res=0;
  if(a/cyc==b/cyc){
    fill_n(diss,n,MAX);
    add(enc(a),0);
    while(ques.size()){
      auto[dis,a]=ques.front();ques.pop();
      for(I i=2;i<=k;i++)add(enc(dec(a)/i*i),dis+1);
      add(enc(dec(a)-1),dis+1);
    }
    res+=diss[enc(b)];
  }else{
    fill_n(diss,n,MAX);
    add(enc(a),0);
    while(ques.size()){
      auto[dis,a]=ques.front();ques.pop();
      for(I i=2;i<=k;i++)add(enc(dec(a)/i*i),dis+1);
      add(enc(dec(a)-1),dis+1);
    }
    res+=diss[0]+1;
    fill_n(diss,n,MAX);
    add(enc(n-1),0);
    while(ques.size()){
      auto[dis,a]=ques.front();ques.pop();
      for(I i=2;i<=k;i++)add(enc(dec(a)/i*i),dis+1);
      add(enc(dec(a)-1),dis+1);
    }
    res+=(diss[0]+1)*(a/cyc-b/cyc-1);
    res+=diss[enc(b)];
  }
  printf("%lli\n",res);
}