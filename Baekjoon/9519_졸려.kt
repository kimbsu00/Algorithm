package baekjoon

fun solve(x: Int, mixedWord: String): String {
    val length = mixedWord.length
    val isOdd = length.mod(2) == 1

    val rotation = arrayListOf<String>(mixedWord)
    var loop = 0

    val word = mixedWord.toMutableList()
    while (true) {
        val last = rotation.lastOrNull() ?: mixedWord

        var wordIdx = 0
        for (idx in 0..<length step 2) {
            word[wordIdx] = last[idx]
            wordIdx += 1
        }

        val back = if (isOdd) length - 2 else length - 1
        for (idx in back downTo 1 step 2) {
            word[wordIdx] = last[idx]
            wordIdx += 1
        }

        val result = word.joinToString(separator = "")
        if (result == mixedWord) {
            break
        }

        rotation.add(result)
        loop += 1
    }
//    print(rotation.toString() + "\n")

    val modNum = x.mod(rotation.size)
    return rotation[modNum]
}

fun main() {
    val x = readlnOrNull()?.toInt() ?: 0
    val mixedWord = readlnOrNull() ?: ""

    val answer = solve(x, mixedWord)
    print("$answer\n")
}
