package baekjoon

data class Pos(val row: Int, val col: Int)

// left, top, right, bottom
val dr = intArrayOf(0, -1, 0, 1)
val dc = intArrayOf(-1, 0, 1, 0)
var rowMax: Int = 0
var colMax: Int = 0

fun min(left: Int, right: Int): Int = if (left < right) left else right

fun checkRange(row: Int, col: Int): Boolean = (row in 0..<rowMax) && (col in 0..<colMax)

fun main() {
    readlnOrNull()?.split(" ")?.let {
        rowMax = it[0].toInt()
        colMax = it[1].toInt()
    }

    val maze = Array<IntArray>(rowMax) { IntArray(colMax) { 0 } }
    val fireMap = Array<IntArray>(rowMax) { IntArray(colMax) { 0 } }
    val pos = ArrayDeque<Pos>()
    val firePos = ArrayDeque<Pos>()

    for (row in 0..<rowMax) {
        readlnOrNull()?.let {
            for (col in 0..<colMax) {
                val ch = it[col]
                when (ch) {
                    // 벽
                    '#' -> {
                        maze[row][col] = -1
                        fireMap[row][col] = -1
                    }
                    // 빈 공간
                    '.' -> {
                        maze[row][col] = 0
                        fireMap[row][col] = 0
                    }
                    // 출발 위치
                    'J' -> {
                        pos.add(Pos(row, col))
                        maze[row][col] = 1
                        fireMap[row][col] = 0
                    }
                    // 불
                    'F' -> {
                        firePos.add(Pos(row, col))
                        maze[row][col] = 0
                        fireMap[row][col] = 1
                    }
                }
            }
        }
    }

    while (firePos.isNotEmpty()) {
        val (row, col) = firePos.first()
        firePos.removeFirst()

        for (idx in 0..3) {
            val nextRow = row + dr[idx]
            val nextCol = col + dc[idx]

            if (checkRange(nextRow, nextCol) && maze[nextRow][nextCol] != -1 && fireMap[nextRow][nextCol] == 0) {
                fireMap[nextRow][nextCol] = fireMap[row][col] + 1
                firePos.add(Pos(nextRow, nextCol))
            }
        }
    }

    var answer = -1
    while (pos.isNotEmpty()) {
        val (row, col) = pos.first()
        pos.removeFirst()

        val curTime = maze[row][col]
        if (row == 0 || row == rowMax - 1 || col == 0 || col == colMax - 1) {
            answer = curTime
            break
        }

        for (idx in 0..3) {
            val nextRow = row + dr[idx]
            val nextCol = col + dc[idx]

            if (checkRange(nextRow, nextCol) &&
                maze[nextRow][nextCol] == 0 &&
                (curTime.plus(1) < fireMap[nextRow][nextCol] || fireMap[nextRow][nextCol] == 0)
            ) {
                maze[nextRow][nextCol] = curTime + 1
                pos.add(Pos(nextRow, nextCol))
            }
        }
    }

    if (answer == -1) {
        print("IMPOSSIBLE\n")
    } else {
        print("$answer\n")
    }

}
