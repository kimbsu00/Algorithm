// URL: https://www.acmicpc.net/problem/2638

enum class State {
    AIR,
    CHEESE,
}

typealias Position = Pair<Int, Int>

fun main() {
    readln().split(" ").map { it.toInt() }.let { (N, M) ->
        val map = Array(N) { Array<State>(M) { State.AIR } }

        var totalCheese = 0
        for (row in 0 until N) {
            readln().split(" ").map { it.toInt() }.forEachIndexed { col, value ->
                map[row][col] = State.entries.find { it.ordinal == value } ?: State.AIR
                if (map[row][col] == State.CHEESE) {
                    totalCheese += 1
                }
            }
        }

        var time = 0
        var meltingCheese = 0
        while (meltingCheese < totalCheese) {
            meltingCheese += solve(N, M, map)
            time += 1
        }
        println(time)
    }
}

fun solve(N: Int, M: Int, map: Array<Array<State>>): Int {
    val posQ = ArrayDeque<Position>().apply { add(0 to 0) }
    val cheeseMap = mutableMapOf<Position, Int>()
    val visited = Array(N) { BooleanArray(M) { false } }
    visited[0][0] = true

    val delta = listOf(
        0 to -1, 
        -1 to 0, 
        0 to 1, 
        1 to 0
    )

    while (posQ.isNotEmpty()) {
        val (row, col) = posQ.removeFirst()

        delta.forEach { (dr, dc) ->
            val (nextRow, nextCol) = (row + dr) to (col + dc)

            if (nextRow in 0 until N && nextCol in 0 until M && !visited[nextRow][nextCol]) {
                if (State.AIR == map[nextRow][nextCol]) {
                    posQ.add(nextRow to nextCol)
                    visited[nextRow][nextCol] = true
                } else if (State.CHEESE == map[nextRow][nextCol]) {
                    cheeseMap[nextRow to nextCol] = (cheeseMap[nextRow to nextCol] ?: 0) + 1
                }
            }
        }
    }

    var meltingCheese = 0
    cheeseMap.forEach { (pos, count) ->
        if (count >= 2) {
            val (row, col) = pos
            map[row][col] = State.AIR
            meltingCheese += 1
        }
    }

    return meltingCheese
}
