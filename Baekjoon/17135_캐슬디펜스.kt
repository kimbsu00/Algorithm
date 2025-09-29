// URL: https://www.acmicpc.net/problem/17135

typealias ArchorPosition = Triple<Int, Int, Int>

fun main() {
    readln().split(" ").map { it.toInt() }.let { (N, M, D) -> 
        val map = Array(N) {
            readln().split(" ").map { it.toInt() }.toIntArray()
        }

        val archorPositionQ = ArrayDeque<ArchorPosition>().apply {
            add(Triple(0, 1, 2))
        }
        val archorPositionSet = mutableSetOf<ArchorPosition>().apply {
            add(Triple(0, 1, 2))
        }

        var maxKillCount = 0
        while (archorPositionQ.isNotEmpty()) {
            val (first, second, third) = archorPositionQ.removeFirst()

            val killCount = solve(N, M, D, map, Triple(first, second, third))
            maxKillCount = maxOf(maxKillCount, killCount)

            // 세 번째 궁수를 오른쪽으로 이동시킬 수 있는 경우
            if (third + 1 < M) {
                val thirdMoveCase = archorPositionSet.find { it == ArchorPosition(first, second, third + 1) }
                if (null == thirdMoveCase) {
                    archorPositionQ.add(ArchorPosition(first, second, third + 1))
                    archorPositionSet.add(ArchorPosition(first, second, third + 1))
                }
            }
            // 두 번째 궁수를 오른쪽으로 이동시킬 수 있는 경우
            if (second + 1 < third) {
                val secondMoveCase = archorPositionSet.find { it == ArchorPosition(first, second + 1, third) }
                if (null == secondMoveCase) {
                    archorPositionQ.add(ArchorPosition(first, second + 1, third))
                    archorPositionSet.add(ArchorPosition(first, second + 1, third))
                }
            }
            // 첫 번째 궁수를 오른쪽으로 이동시킬 수 있는 경우
            if (first + 1 < second) {
                val firstMoveCase = archorPositionSet.find { it == ArchorPosition(first + 1, second, third) }
                if (null == firstMoveCase) {
                    archorPositionQ.add(ArchorPosition(first + 1, second, third))
                    archorPositionSet.add(ArchorPosition(first + 1, second, third))
                }
            }
        }

        println(maxKillCount)
    }
}

fun solve(N: Int, M: Int, D: Int, map: Array<IntArray>, archorPositions: ArchorPosition): Int {
    var killCount = 0
    val copyMap = Array(N) { row -> 
        IntArray(M) { col -> 
            map[row][col]
        }
    }

    var turn = 0
    for (row in 0 until N) {
        for (col in 0 until M) {
            if (copyMap[row][col] == 1) {
                turn = N - row
                break
            }
        }
        if (turn != 0) break
    }

    for (idx in 0 until turn) {
        val targets = mutableSetOf<Pair<Int, Int>>()
        val (first, second, third) = archorPositions
        val archorRow = N - idx

        findClosestEnemy(N, M, D, copyMap, archorRow, first)?.let { targets.add(it) }
        findClosestEnemy(N, M, D, copyMap, archorRow, second)?.let { targets.add(it) }
        findClosestEnemy(N, M, D, copyMap, archorRow, third)?.let { targets.add(it) }
        
        targets.forEach { (row, col) ->
            if (copyMap[row][col] == 1) {
                killCount += 1
                copyMap[row][col] = 0
            }
        }

        for (col in 0 until M) {
            copyMap[archorRow - 1][col] = 0
        }
    }

    return killCount
}

fun findClosestEnemy(
    N: Int, 
    M: Int, 
    D: Int, 
    map: Array<IntArray>, 
    archerRow: Int, 
    archerCol: Int
): Pair<Int, Int>? {
    val visited = Array(N) { BooleanArray(M) { false } }
    val posQ = ArrayDeque<Pair<Int, Int>>().apply {
        add(archerRow to archerCol)
    }

    val delta = listOf(
        0 to -1, // left
        -1 to 0, // up
        0 to 1,  // right
    )
    while (posQ.isNotEmpty()) {
        val (row, col) = posQ.removeFirst()

        delta.forEach { (dr, dc) -> 
            val (nextRow, nextCol) = (row + dr) to (col + dc)
            val distance = calcDistance(archerRow, archerCol, nextRow, nextCol)

            if (nextRow in 0 until N && nextCol in 0 until M && !visited[nextRow][nextCol] && distance <= D) {
                if (1 == map[nextRow][nextCol]) {
                    return nextRow to nextCol
                }
                posQ.add(nextRow to nextCol)
                visited[nextRow][nextCol] = true
            }
        }
    }

    return null
}

fun calcDistance(r1: Int, c1: Int, r2: Int, c2: Int): Int {
    return kotlin.math.abs(r1 - r2) + kotlin.math.abs(c1 - c2)
}
