package baekjoon

private fun max(left: Int, right: Int): Int = if (left > right) left else right

/**
 * @param left      inclusive left index
 * @param right     inclusive right index
 */
fun IntArray.getRangeSum(left: Int, right: Int): Int {
    return if (left !in this.indices && right !in this.indices) {
        0
    } else if (left == 0) {
        this[right]
    } else {
        this[right] - this[left - 1]
    }
}

fun main() {
    val N = readlnOrNull()?.toInt() ?: 0
    val honey = IntArray(N) { 0 }
    val prefixSum = IntArray(N) { 0 }

    readlnOrNull()?.split(' ')?.let { input ->
        for (idx in 0..<N) {
            val num = input[idx].toInt()
            honey[idx] = num

            if (idx > 0) {
                prefixSum[idx] = prefixSum[idx - 1] + num
            } else {
                prefixSum[idx] = num
            }
        }
    }

    var answer = 0
    // 통벌벌
    for (idx in 1..N - 2) {
        val sum = prefixSum.getRangeSum(0, idx) + prefixSum.getRangeSum(0, N - 1) - honey[idx].times(2) - honey[N - 1]
        answer = max(answer, sum)
    }

    // 벌통벌
    for (idx in 1..N - 2) {
        val sum = prefixSum.getRangeSum(0, idx) + prefixSum.getRangeSum(idx, N - 1) - honey[0] - honey[N - 1]
        answer = max(answer, sum)
    }

    // 벌벌통
    for (idx in 1..N - 2) {
        val sum = prefixSum.getRangeSum(0, N - 1) + prefixSum.getRangeSum(idx, N - 1) - honey[0] - honey[idx].times(2)
        answer = max(answer, sum)
    }

    print("$answer\n")
}
