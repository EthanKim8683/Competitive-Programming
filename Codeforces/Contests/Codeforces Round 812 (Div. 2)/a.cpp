#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I xl=0,yl=0,xu=0,yu=0;
    for(I i=0;i<n;i++){
      I x,y;cin>>x>>y;
      if(x==0)yl=min(yl,y),yu=max(yu,y);
      if(y==0)xl=min(xl,x),xu=max(xu,x);
    }
    printf("%i\n",2*(xu+yu-xl-yl));
  }
  return 0;
}