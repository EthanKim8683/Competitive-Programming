#include<bits/stdc++.h>
using namespace std;
using I=int;
const I M=1e5;
const I N=1e5;
const I MAX=1e9;
vector<I>p_arr[M];
I upps[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m,n;cin>>m>>n;
    for(I i=0;i<m;i++){
      p_arr[i].resize(n);
      for(I j=0;j<n;j++)cin>>p_arr[i][j];
    }
    fill_n(upps,n,0);
    for(I i=0;i<m;i++)for(I j=0;j<n;j++)upps[j]=max(upps[j],p_arr[i][j]);
    I upp=*min_element(upps,upps+n),res=0;
    for(I i=0;i<m;i++){
      sort(p_arr[i].begin(),p_arr[i].end());
      res=max(res,min(min(p_arr[i][n-1],p_arr[i][n-2]),upp));
    }
    printf("%i\n",res);
  }
}