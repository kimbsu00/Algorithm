package baekjoon

fun calculate(
    leftEquation: IntArray,
    rightEquation: IntArray,
    alphabetMap: IntArray,
): Int {
    var leftAnswer = 0
    leftEquation.forEachIndexed { idx, multiplier ->
        leftAnswer += multiplier * alphabetMap[idx]
    }

    var rightAnswer = 0
    rightEquation.forEachIndexed { idx, multiplier ->
        rightAnswer += multiplier * alphabetMap[idx]
    }

    return if (leftAnswer == rightAnswer) 1 else 0
}

fun solve(
    keyIdx: Int,
    keys: List<Char>,
    leftEquation: IntArray,
    rightEquation: IntArray,
    alphabetMap: IntArray,
    canBeZero: List<Boolean>,
    used: MutableList<Boolean>
): Int {
    if (keyIdx >= keys.size) {
        return calculate(leftEquation, rightEquation, alphabetMap)
    }

    val ch = keys[keyIdx]
    val chIdx = ch - 'A'

    var ret = 0
    if (canBeZero[chIdx] && !used[0]) {
        used[0] = true
        alphabetMap[chIdx] = 0
        ret += solve(keyIdx + 1, keys, leftEquation, rightEquation, alphabetMap, canBeZero, used)
        alphabetMap[chIdx] = 0
        used[0] = false
    }
    for (num in 1..9) {
        if (!used[num]) {
            used[num] = true
            alphabetMap[chIdx] = num
            ret += solve(keyIdx + 1, keys, leftEquation, rightEquation, alphabetMap, canBeZero, used)
            alphabetMap[chIdx] = 0
            used[num] = false
        }
    }

    return ret
}

fun main() {
    val answer = arrayListOf<Int>()
    // 좌우변 모두 합한 HashMap
    val keys = HashSet<Char>()

    while (true) {
        keys.clear()
        // 좌변
        val leftEquation = IntArray(26) { 0 }
        // 우변
        val rightEquation = IntArray(26) { 0 }
        val alphabetMap = IntArray(26) { 0 }

        val N = readlnOrNull()?.toInt() ?: 0
        if (N == 0) break

        val canBeZero = MutableList<Boolean>(26) { true }
        for (idx in 0..<N - 1) {
            readlnOrNull()?.let {
                var multiplier = 1
                for (pos in it.length - 1 downTo 0) {
                    val ch = it[pos]
                    val chIdx = ch - 'A'
                    keys.add(ch)
                    leftEquation[chIdx] += multiplier
                    multiplier *= 10
                }

                if (it.length > 1) {
                    canBeZero[it.first() - 'A'] = false
                }
            }
        }

        val wordN = readlnOrNull() ?: ""
        var multiplier = 1
        for (pos in wordN.length - 1 downTo 0) {
            val ch = wordN[pos]
            val chIdx = ch - 'A'
            keys.add(ch)
            rightEquation[chIdx] += multiplier
            multiplier *= 10
        }
        if (wordN.length > 1) {
            canBeZero[wordN.first() - 'A'] = false
        }

        val used = MutableList<Boolean>(10) { false }
        answer.add(solve(0, keys.toList(), leftEquation, rightEquation, alphabetMap, canBeZero, used))
    }

    for (ans in answer) {
        print("$ans\n")
    }
}
