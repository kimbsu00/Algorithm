package baekjoon

fun main() {
    val N = readlnOrNull()?.toInt() ?: 0

    val hashMap = hashMapOf<String, ArrayList<String>>()
    val wordList = arrayListOf<String>()
    for (idx in 0..<N) {
        readlnOrNull()?.let { word ->
            wordList.add(word)
            for (size in 1..word.length) {
                val substr = word.substring(0, size)

                if (hashMap.containsKey(substr)) {
                    hashMap[substr]?.add(word)
                } else {
                    hashMap[substr] = arrayListOf(word)
                }
            }
        }
    }

    var prefixLength = 0
    var answer: List<String> = wordList
    for ((key, value) in hashMap) {
        if (prefixLength < key.length && value.size > 1) {
            prefixLength = key.length
            answer = value
        } else if (prefixLength == key.length && value.size > 1) {
            val originIdx = wordList.indexOf(answer.first())
            val newIdx = wordList.indexOf(value.first())

            if (newIdx < originIdx) {
                answer = value
            }
        }
    }

    print("${answer[0]}\n${answer[1]}\n")
}
