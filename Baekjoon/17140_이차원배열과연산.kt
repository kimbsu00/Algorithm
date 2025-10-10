// URL: https://www.acmicpc.net/problem/17140

fun main() {
    readln().split(" ").map { it.toInt() }.let { (R, C, K) ->
        val array = Array(100) { IntArray(100) { 0 } }

        readln().split(" ").map { it.toInt() }.forEachIndexed { col, value ->
            array[0][col] = value
        }

        readln().split(" ").map { it.toInt() }.forEachIndexed { col, value ->
            array[1][col] = value
        }

        readln().split(" ").map { it.toInt() }.forEachIndexed { col, value ->
            array[2][col] = value
        }

        var (maxRow, maxCol) = 3 to 3
        var time = 0
        while (time <= 100) {
            if (array[R - 1][C - 1] == K) {
                println(time)
                break
            }

            val (newMaxRow, newMaxCol) = solve(array, maxRow, maxCol)
            maxRow = newMaxRow
            maxCol = newMaxCol
            time += 1
        }

        if (time > 100) {
            println(-1)
        }
    }
}

fun solve(array: Array<IntArray>, maxRow: Int, maxCol: Int): Pair<Int, Int> {
    var newMaxRow = maxRow
    var newMaxCol = maxCol

    // R 연산
    if (maxRow >= maxCol) {
        for (row in 0 until maxRow) {
            val countMap = mutableMapOf<Int, Int>()
            for (col in 0 until maxCol) {
                val value = array[row][col]
                if (value != 0) {
                    countMap[value] = (countMap[value] ?: 0) + 1
                }
            }

            val sortedList = countMap.entries.sortedWith(compareBy({ it.value }, { it.key }))

            var colIndex = 0
            for ((num, count) in sortedList) {
                if (colIndex < 100) {
                    array[row][colIndex] = num
                    colIndex += 1
                }
                if (colIndex < 100) {
                    array[row][colIndex] = count
                    colIndex += 1
                }
            }

            if (newMaxCol < colIndex) {
                newMaxCol = colIndex
            } else {
                for (col in colIndex until maxCol) {
                    array[row][col] = 0
                }
            }
        }
    }
    // C 연산
    else {
        for (col in 0 until maxCol) {
            val countMap = mutableMapOf<Int, Int>()
            for (row in 0 until maxRow) {
                val value = array[row][col]
                if (value != 0) {
                    countMap[value] = (countMap[value] ?: 0) + 1
                }
            }

            val sortedList = countMap.entries.sortedWith(compareBy({ it.value }, { it.key }))

            var rowIndex = 0
            for ((num, count) in sortedList) {
                if (rowIndex < 100) {
                    array[rowIndex][col] = num
                    rowIndex += 1
                }
                if (rowIndex < 100) {
                    array[rowIndex][col] = count
                    rowIndex += 1
                }
            }

            if (newMaxRow < rowIndex) {
                newMaxRow = rowIndex
            } else {
                for (row in rowIndex until maxRow) {
                    array[row][col] = 0
                }
            }
        }
    }

    return newMaxRow to newMaxCol
}
