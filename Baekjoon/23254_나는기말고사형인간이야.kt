import java.util.PriorityQueue

private var N: Int = 0
private var M: Int = 0
private lateinit var minScore: IntArray
private lateinit var scorePerHour: IntArray

/** 오름차순 정렬을 위한 데이터 클래스 */
data class ScoreData(var score: Int, var scorePerHour: Int, val idx: Int) : Comparable<ScoreData> {

    fun addScorePerHour() {
        if (score + scorePerHour <= 100) {
            this.score += scorePerHour
        } else {
            this.score = 100
        }
    }

    private fun getAvailableScore(): Int {
        return if (score + scorePerHour <= 100) scorePerHour else 100 - score
    }

    override fun compareTo(other: ScoreData): Int {
        return other.getAvailableScore() - this.getAvailableScore()
    }
}

fun solve(): Int {
    var ret: Int = 0
    val pq = PriorityQueue<ScoreData>()

    for (idx in minScore.indices) {
        pq.add(ScoreData(minScore[idx], scorePerHour[idx], idx))
    }

    while (N > 0 && pq.isNotEmpty()) {
        val top = pq.poll()

        top.addScorePerHour()

        if (top.score < 100) {
            pq.add(top)
        } else {
            ret += 100
        }

        N -= 1
    }

    while (pq.isNotEmpty()) {
        val top = pq.poll()
        ret += top.score
    }

    return ret
}

fun main() {
    readLine()?.split(' ')?.let { input ->
        N = input[0].toInt() * 24
        M = input[1].toInt()
    }

    minScore = IntArray(M) { 0 }
    scorePerHour = IntArray(M) { 0 }

    readLine()?.split(' ')?.let { input ->
        for (idx in input.indices) {
            val num = input[idx].toInt()
            minScore[idx] = num
        }
    }

    readLine()?.split(' ')?.let { input ->
        for (idx in input.indices) {
            val num = input[idx].toInt()
            scorePerHour[idx] = num
        }
    }

    println(solve())
}
