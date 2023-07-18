fun main() {
    val input = readLine()?.split(' ') ?: listOf()
    val T = input[0].toInt()
    val S = input[1].toInt()

    val answer =
            if (S == 1) {
                280
            } else {
                when {
                    T in 12 until 17 -> 320
                    else -> 280
                }
            }
    println(answer)
}
