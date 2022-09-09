val MAX=1000000000

fun main(){
  val(n,m,k)=readLine()!!.split(" ").map{it.toInt()}
  val ress=IntArray(n){MAX}
  ress[k-1]=0
  for(i in 1..m){
    var(a,b)=readLine()!!.split(" ").map{it.toInt()-1}
    val ta=ress[a]
    val tb=ress[b]
    ress[a]=minOf(ta+1,tb)
    ress[b]=minOf(tb+1,ta)
  }
  for(i in 0..n-1){
    if(ress[i]==MAX)print("-1")
    else print(ress[i])
    print(" ")
  }
}