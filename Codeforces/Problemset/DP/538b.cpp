#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I L=7;

I cnts[L+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I res=0,len=0;
  while(n){
    I d=n%10;
    res=max(res,cnts[len++]=d);
    n/=10;
  }
  printf("%i\n",res);
  for(I i=0;i<res;i++){
    I cur=0,dgt=1;
    for(I j=0;j<len;j++){
      if(cnts[j])cur+=dgt,cnts[j]--;
      dgt*=10;
    }
    printf("%i ",cur);
  }
  return 0;
}