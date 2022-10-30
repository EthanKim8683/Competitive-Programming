#include<bits/stdc++.h>

using namespace std;

using I=int;

vector<I>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I c=n;
    ress.clear();
    for(I i=2;ress.size()<3&&i*i<=n;i++){
      I j=i,t=n;
      while(t%j==0){
        ress.push_back(j);
        t/=j,j*=i;
      }
      while(n%i==0)n/=i;
    }
    if(n>2)ress.push_back(n);
    if(ress.size()<2){printf("NO\n");continue;}
    I a=ress[0],b=ress[1];
    c/=a*b;
    if(c>=2&&!binary_search(ress.begin(),ress.end(),c))ress.push_back(c);
    if(ress.size()<3){printf("NO\n");continue;}
    printf("YES\n");
    printf("%i %i %i\n",a,b,c);
  }
}