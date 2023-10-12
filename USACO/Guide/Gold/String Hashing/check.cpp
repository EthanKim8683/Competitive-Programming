#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using B=bool;
const I M=1e6;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
Lli pows[M+1];
Lli pres[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=M;i++)pows[i]=pows[i-1]*BAS%MOD;
  S s;cin>>s;
  S t;cin>>t;
  I n=s.size(),m=t.size();
  for(I i=0;i<m;i++)pres[i+1]=(pres[i]*BAS+t[i])%MOD;
  I cnt1=0,cnt2=0;
  for(I i=0;i<n;i++)cnt1+=s[i]=='0',cnt2+=s[i]=='1';
  I res=0;
  for(I i=1;i<=m;i++){
    I j=m-i*cnt1;
    if(j<=0)break;
    if(j%cnt2!=0)continue;
    j/=cnt2;
    B vld=1;
    Lli hsh1=-1,hsh2=-1;
    for(I k=0,l=0;k<n;k++){
      if(s[k]=='0'){
        I hsh=((pres[l+i]-pres[l]*pows[i])%MOD+MOD)%MOD;
        if(hsh1==-1)hsh1=hsh;
        if(hsh1!=hsh){vld=0;break;}
        l+=i;
      }
      if(s[k]=='1'){
        I hsh=((pres[l+j]-pres[l]*pows[j])%MOD+MOD)%MOD;
        if(hsh2==-1)hsh2=hsh;
        if(hsh2!=hsh){vld=0;break;}
        l+=j;
      }
    }
    vld&=hsh1!=hsh2;
    res+=vld;
  }
  printf("%i\n",res);
}