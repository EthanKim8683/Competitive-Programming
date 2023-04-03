#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)printf("%i ",i+((n+i)%2?-1:1)+(i==0&&n%2)+1);
    printf("\n");
  }
  return 0;
}