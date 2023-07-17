val posList: ArrayList<Pair<Int, Int>> = arrayListOf()
val lineList: ArrayDeque<Int> = ArrayDeque()

fun solve(idx: Int): Boolean {
    if (idx == posList.size) {
        return lineList.size <= 3
    }

    if (lineList.size > 3) {
        return false
    }

    val pos = posList[idx]

    var ret: Boolean
    val xLine = lineList.find { it -> it == pos.first }
    if (xLine == null) {
        lineList.add(pos.first)
        ret = solve(idx + 1)
        lineList.removeLast()
    } else {
        ret = solve(idx + 1)
    }

    if (ret) {
        return true
    }

    if (pos.first != (-pos.second)) {
        val yLine = lineList.find { it -> it == -pos.second }
        if (yLine == null) {
            lineList.add(-pos.second)
            ret = solve(idx + 1)
            lineList.removeLast()
        } else {
            ret = solve(idx + 1)
        }
    }

    return ret
}

fun main() {
    val N = readLine()?.toInt() ?: 0

    for (idx in 0 until N) {
        val input: List<Int> =
                readLine()?.split(' ')?.let { it -> listOf(it[0].toInt(), it[1].toInt()) }
                        ?: listOf()
        posList.add(Pair(input[0], input[1]))
    }

    val answer = solve(0)
    println(if (answer) 1 else 0)
}
