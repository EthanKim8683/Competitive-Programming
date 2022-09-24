#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I a=-1,b=-1;
    for(I i=0;i<n;i++){
      if(a_arr[i]%2){
        if(a==-1)a=i;
        else if(b==-1)b=i;
      }else a=i,b=-2;
    }
    if(a<0){printf("-1\n");continue;}
    I sum=0;
    if(a>=0)sum+=a_arr[a];
    if(b>=0)sum+=a_arr[b];
    if(sum%2){printf("-1\n");continue;}
    printf("%i\n",(a>=0)+(b>=0));
    if(a>=0)printf("%i ",a+1);
    if(b>=0)printf("%i ",b+1);
    printf("\n");
  }
}