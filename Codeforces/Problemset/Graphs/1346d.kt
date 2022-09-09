import java.util.Scanner;
import java.lang.Math;
 
val N=200000;
val M=200000;
 
val maxs=IntArray(N);
val edgs=Array(M){IntArray(3)};
 
fun main() {
  var rea=Scanner(System.`in`);
  var t=rea.nextInt();
  while(t-->0){
    var n=rea.nextInt();
    var m=rea.nextInt();
    for(i in 0..n-1)maxs[i]=0;
    for(i in 0..m-1){
      var u=rea.nextInt()-1;
      var v=rea.nextInt()-1;
      var w=rea.nextInt();
      edgs[i][0]=u;
      edgs[i][1]=v;
      edgs[i][2]=w;
      maxs[u]=Math.max(maxs[u],w);
      maxs[v]=Math.max(maxs[v],w);
    }
    var res:Boolean=true;
    for(i in 0..m-1){
      var u=edgs[i][0];
      var v=edgs[i][1];
      var w=edgs[i][2];
      if(Math.min(maxs[u],maxs[v])!=w)
        res=false;
    }
    if(res==false){
      println("NO");
      continue;
    }
    println("YES");
    for(i in 0..n-1)
      print("${maxs[i]} ");
    println();
  }
}