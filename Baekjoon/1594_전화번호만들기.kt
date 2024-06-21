data class Node(val quality: Int, val str: String)

val cache = MutableList<Node>(1004) { Node(-1, "") }
val customOrder = listOf('-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9')

fun String.compare(other: String): Int {
    val lastIdx = if (length > other.length) other.length else length

    for (idx in 0 until lastIdx) {
        val leftCharOrder = customOrder.indexOf(this[idx])
        val rightCharOrder = customOrder.indexOf(other[idx])

        if (leftCharOrder < rightCharOrder) {
            return -1
        } else if (leftCharOrder > rightCharOrder) {
            return 1
        }
    }

    return if (length > other.length) 1 else if (length < other.length) -1 else 0
}

fun max(left: Node, right: Node): Node {
    return if (left.quality == right.quality) {
        if (left.str.compare(right.str) < 0) left else right
    } else if (left.quality > right.quality) {
        left
    } else {
        right
    }
}

fun solve(number: String, idx: Int): Node {
    if (idx == number.length - 2) {
        val first = number[idx]
        val second = number[idx + 1]

        return Node(if (first == second) 2 else 0, number.substring(idx, idx + 2))
    } else if (idx == number.length - 3) {
        val first = number[idx]
        val second = number[idx + 1]
        val third = number[idx + 2]

        val quality =
                when {
                    first == second && second == third -> 2
                    first == second || first == third || second == third -> 1
                    else -> 0
                }
        return Node(quality, number.substring(idx, idx + 3))
    } else if (idx > number.length - 2) {
        return Node(Int.MIN_VALUE, "")
    }

    if (cache[idx].quality != -1) {
        return cache[idx]
    }

    val first = number[idx]
    val second = number[idx + 1]
    val third = number[idx + 2]

    // 3개가 모두 같은 경우
    if (first == second && second == third) {
        val groupOh1 =
                solve(number, idx + 3).run {
                    copy(quality + 2, number.substring(idx, idx + 3) + "-" + str)
                }
        val groupOh2 =
                solve(number, idx + 2).run {
                    copy(quality + 2, number.substring(idx, idx + 2) + "-" + str)
                }
        cache[idx] = max(cache[idx], max(groupOh1, groupOh2))
    }
    // 첫 번째와 두 번째가 같은 경우
    if (first == second && second != third) {
        val groupOh =
                solve(number, idx + 2).run {
                    copy(quality + 2, number.substring(idx, idx + 2) + "-" + str)
                }
        val groupKang =
                solve(number, idx + 3).run {
                    copy(quality + 1, number.substring(idx, idx + 3) + "-" + str)
                }
        cache[idx] = max(cache[idx], max(groupOh, groupKang))
    }
    // 첫 번째와 세 번째가 같은 경우
    if (first == third && first != second) {
        val groupKang =
                solve(number, idx + 3).run {
                    copy(quality + 1, number.substring(idx, idx + 3) + "-" + str)
                }
        cache[idx] = max(cache[idx], groupKang)
    }
    // 두 번째와 세 번째가 같은 경우
    if (second == third && first != second) {
        val groupKang =
                solve(number, idx + 3).run {
                    copy(quality + 1, number.substring(idx, idx + 3) + "-" + str)
                }
        cache[idx] = max(cache[idx], groupKang)
    }
    // 3개가 모두 다른 경우
    val two =
            solve(number, idx + 2).run { copy(quality, number.substring(idx, idx + 2) + "-" + str) }
    val three =
            solve(number, idx + 3).run { copy(quality, number.substring(idx, idx + 3) + "-" + str) }
    cache[idx] = max(cache[idx], max(two, three))

    return cache[idx]
}

fun main() {
    val number = readLine() ?: ""
    val answer = solve(number, 0)
    print("${answer.str}\n")
}
