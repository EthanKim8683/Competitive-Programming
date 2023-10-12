#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  Lli low=n/m,upp=low+1,cnt2=n%m,cnt1=m-cnt2,cnt3=n-(m-1);
  printf("%lli %lli\n",cnt1*low*(low-1)/2+cnt2*upp*(upp-1)/2,cnt3*(cnt3-1)/2);
}
/*
the minimum number of pairs can be achieved by distributing the participants
as evenly as possible

the maximum number of pairs can be achieved by distributing the participants
as unevenly as possible
*/