private fun solve(num: Int, cache: MutableList<Int>) {
    var ret: Int = Int.MAX_VALUE

    var size = 10
    while (size <= num) {
        var tmp = num

        while (tmp > 0) {
            val subset = tmp % size
            tmp /= 10

            if (0 < subset && cache[num - subset] == 0) {
                ret = if (ret > subset) subset else ret
            }
        }

        size *= 10
    }

    cache[num] = if (ret == Int.MAX_VALUE) 0 else ret
}

fun main() {
    val N: Int = readLine()?.toInt() ?: 0
    val cache: MutableList<Int> = MutableList(N + 5) { 0 }

    for (num in 10..N) {
        solve(num, cache)
    }

    print("${if(cache[N] == 0) -1 else cache[N]}\n")
}
