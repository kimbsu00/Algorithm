// URL: https://www.acmicpc.net/problem/14499

enum class DiceDirection(val dx: Int, val dy: Int) {
    EAST(0, 1),
    WEST(0, -1),
    NORTH(-1, 0),
    SOUTH(1, 0);

    companion object {
        fun fromInt(value: Int): DiceDirection =
                when (value) {
                    1 -> EAST
                    2 -> WEST
                    3 -> NORTH
                    4 -> SOUTH
                    else -> throw IllegalArgumentException("Invalid direction value: $value")
                }
    }
}

class Dice(
    var row: Int,
    var col : Int,
    var top: Int,
    var bottom: Int,
    var north: Int,
    var south: Int,
    var east: Int,
    var west: Int,
) {
    fun canGo(direction: DiceDirection, maxRow: Int, maxCol: Int): Boolean {
        return when (direction) {
            DiceDirection.EAST -> {
                val nextCol = col + 1
                if (nextCol < maxCol) {
                    col = nextCol
                    true
                } else {
                    false
                }
            }
            DiceDirection.WEST -> {
                val nextCol = col - 1
                if (nextCol >= 0) {
                    col = nextCol
                    true
                } else {
                    false
                }
            }
            DiceDirection.NORTH -> {
                val nextRow = row - 1
                if (nextRow >= 0) {
                    row = nextRow
                    true
                } else {
                    false
                }
            }
            DiceDirection.SOUTH -> {
                val nextRow = row + 1
                if (nextRow < maxRow) {
                    row = nextRow
                    true
                } else {
                    false
                }
            }
        }
    }

    fun roll(direction: DiceDirection) {
        val t = top
        val b = bottom
        val n = north
        val s = south
        val e = east
        val w = west

        when (direction) {
            DiceDirection.EAST -> {
                top = e
                bottom = w
                east = b
                west = t
            }
            DiceDirection.WEST -> {
                top = w
                bottom = e
                east = t
                west = b
            }
            DiceDirection.NORTH -> {
                top = n
                bottom = s
                north = b
                south = t
            }
            DiceDirection.SOUTH -> {
                top = s
                bottom = n
                north = t
                south = b
            }
        }
    }
}

fun main() {
    readln().split(" ").map { it.toInt() }.let { (N, M, X, Y, K) ->
        val map = Array(N) { IntArray(M) { 0 } }

        for (row in 0 until N) {
            readln().split(" ").map { it.toInt() }.forEachIndexed { col, value ->
                map[row][col] = value
            }
        }

        val dice = Dice(X, Y, 0, 0, 0, 0, 0, 0)
        readln().split(" ").map { it.toInt() }.forEach { command ->
            val dir = DiceDirection.fromInt(command)
            val canGo = dice.canGo(dir, N, M)

            if (canGo) {
                dice.roll(dir)

                if (map[dice.row][dice.col] == 0) {
                    map[dice.row][dice.col] = dice.bottom
                } else {
                    dice.bottom = map[dice.row][dice.col]
                    map[dice.row][dice.col] = 0
                }

                println(dice.top)
            }
        }
    }
}
