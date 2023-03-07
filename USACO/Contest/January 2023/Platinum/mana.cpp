#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=18;
I m_arr[N];
vector<pair<I,I>>adjs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>m_arr[i];
  for(I i=0;i<m;i++){
    I a,b,t;cin>>a>>b>>t,a--,b--;
    adjs[a].push_back({b,t});
  }
  I q;cin>>q;
  while(q--){
    I s,e;cin>>s>>e,e--;
    /*
    t * a + (t + ab) * b + (t + ab + bc) * c
    do not pause in between
    for each set of same values, go for min time
    if multiple min time, go for max value

    tim = x1 + x2 + x3 + ... xn
    sum = 0 * (x1 + x2 + x3 + ... xn) + m1 * (x2 + x3 + ... xn)
    rat = (m1 + m2 + m3 + ... mn) * (t - (x1 + x2 + x3 + ... xn))

    rat * (s - tim) + sum
    convex hull?
    */
  }
}