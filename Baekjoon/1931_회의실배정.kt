// https://www.acmicpc.net/problem/1931

data class Meeting(
    val start: Int, 
    val end: Int,
)

fun main() {
    readln().toInt().let { N -> 
        val meetings = Array(N) {
            readln().split(" ").map { it.toInt() }.let { (start, end) ->
                Meeting(start, end)
            }
        }

        meetings.sortWith(compareBy({ it.end }, { it.start }))

        var count = 0
        var lastEnd = 0
        meetings.forEach {
            if (lastEnd <= it.start) {
                count += 1
                lastEnd = it.end
            }
        }

        println(count)
    }
}
