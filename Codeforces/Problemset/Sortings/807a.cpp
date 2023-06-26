#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000;
I rats[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  B res=0;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    res|=a!=b;
    rats[i]=a;
  }
  if(res)printf("rated"),exit(0);
  res=1;
  for(I i=0;i+1<n;i++)res&=rats[i+1]<=rats[i];
  printf("%s",res?"maybe":"unrated");
}