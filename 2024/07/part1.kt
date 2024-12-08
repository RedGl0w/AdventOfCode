import java.io.File
import java.math.BigInteger // In input I had 276737138893 > 2147483647 = Int.MAX_VALUE

fun isValid(target: java.math.BigInteger, values: List<java.math.BigInteger>, startAt: Int = 0, stacked: java.math.BigInteger = 0.toBigInteger()): Boolean {
  if (startAt == values.size) {
    return stacked == target;
  }
  var head = values[startAt];
  if (startAt == 0) {
    return isValid(target, values, 1, head);
  }
  if (isValid(target, values, startAt+1, stacked*head)) {
    return true;
  }
  return isValid(target, values, startAt+1, stacked+head);
}

fun main() {
  var sum: java.math.BigInteger = 0.toBigInteger();
  File("input.txt").forEachLine {
    if(it != "") {
      var l = it.split(": ");
      var target = java.math.BigInteger(l[0]);
      var values = l[1].split(" ").map({java.math.BigInteger(it)});
      if (isValid(target, values)) {
        sum += target;
      }
    }
  };
  println(sum);
}

