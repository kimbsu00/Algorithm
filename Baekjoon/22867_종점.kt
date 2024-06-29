package baekjoon

fun max(left: Int, right: Int): Int = if (left > right) left else right

fun main() {
    val N = readlnOrNull()?.toInt() ?: 0
    val hsMap = hashMapOf<String, Int>()

    for (idx in 0..<N) {
        readlnOrNull()?.split(" ")?.let { input ->
            val enter = input[0]
            val leave = input[1]

            hsMap[enter] = hsMap[enter]?.plus(1) ?: 1
            hsMap[leave] = hsMap[leave]?.minus(1) ?: -1
        }
    }

    var answer = 0
    var curValue = 0
    hsMap.toSortedMap().let { sortedMap ->
        for ((key, value) in sortedMap) {
            curValue += value
            answer = max(answer, curValue)
        }
    }

    print("$answer\n")
}
