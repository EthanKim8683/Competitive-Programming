#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I L=1e5;
const Lli MOD=1e9+7;

Lli fibs[L+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fibs[0]=fibs[1]=1;
  for(I i=2;i<=L;i++)fibs[i]=(fibs[i-1]+fibs[i-2])%MOD;
  S s;cin>>s;
  I n=s.size();
  Lli res=1;
  for(I r=0;r<n;){
    if(s[r]=='w'||s[r]=='m'){printf("0\n");return 0;}
    if(s[r]!='u'&&s[r]!='n'){r++;continue;}
    I l=r;
    while(s[++r]==s[l]);
    (res*=fibs[r-l])%=MOD;
  }
  printf("%lli\n",res);
  return 0;
}