#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template<class Key,class Compare=less<Key>>
using ordered_set=tree<Key,null_type,Compare,rb_tree_tag,tree_order_statistics_node_update>;
using I=int;
using Lli=long long int;
const I N=200000;
ordered_set<I>sets[N];
pair<Lli,I>dfs(){
  I p;cin>>p;
  if(p==0){
    auto[sum1,i1]=dfs();auto[sum2,i2]=dfs();
    if(sets[i1].size()<sets[i2].size())swap(i1,i2),swap(sum1,sum2);
    Lli cur1=0,cur2=0;
    for(auto val:sets[i2]){
      I ord=sets[i1].order_of_key(val);
      cur1+=ord,cur2+=sets[i1].size()-ord;
    }
    for(auto val:sets[i2])sets[i1].insert(val);
    return{sum1+sum2+min(cur1,cur2),i1};
  }
  if(p!=0){
    sets[p-1].insert(p);
    return{0,p-1};
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  printf("%lli\n",dfs().first);
}