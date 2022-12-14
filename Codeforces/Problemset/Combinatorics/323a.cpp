#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  if(k%2)printf("-1\n"),exit(0);
  for(I i=0;i<k;i++){
    for(I j=0;j<k;j++){
      for(I l=0;l<k;l++)printf("%c",(i&1)^(j/2&1)^(l/2&1)?'b':'w');
      printf("\n");
    }
    printf("\n");
  }
}