#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I MAX=1e9;

B unds[10];
I cnts[2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    for(I i=0;i<10;i++)unds[i]=s[i]=='?';
    I res=10;
    for(I i=0;i<(1<<10);i++){
      for(I j=0;j<10;j++)if(unds[j])s[j]=(i>>j&1)+'0';
      cnts[0]=cnts[1]=0;
      for(I j=0;j<10;j++){
        cnts[j%2]+=s[j]=='1';
        if(cnts[0]-cnts[1]>(10-(j+0))/2)res=min(res,j+1);
        if(cnts[1]-cnts[0]>(10-(j+1))/2)res=min(res,j+1);
      }
    }
    printf("%i\n",res);
  }
}