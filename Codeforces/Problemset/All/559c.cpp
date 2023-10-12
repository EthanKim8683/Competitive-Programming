#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const I H=1e5;
const I W=1e5;
const Lli MOD=1e9+7;
pair<I,I>cels[N];
Lli facs[H+W+1];
Lli ress[N];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
Lli dis(I a,I b){
  return bin(a+b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I h,w,n;cin>>h>>w>>n;
  facs[0]=1;
  for(I i=1;i<=w+h;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<n;i++){
    I r,c;cin>>r>>c,r--,c--;
    cels[i]={r,c};
  }
  sort(cels,cels+n);
  for(I i=n-1;i>=0;i--){
    auto[r1,c1]=cels[i];
    (ress[i]+=dis(h-1-r1,w-1-c1))%=MOD;
    for(I j=i+1;j<n;j++){
      auto[r2,c2]=cels[j];
      if(r2<r1||c2<c1)continue;
      (ress[i]-=dis(r2-r1,c2-c1)*ress[j])%=MOD;
    }
  }
  Lli res=dis(h-1,w-1);
  for(I i=0;i<n;i++){
    auto[r,c]=cels[i];
    (res-=dis(r,c)*ress[i])%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}