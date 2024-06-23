private data class Node(val pos1: Int, val pos2: Int, val result: String)

fun solve(s1: String, s2: String): String {
    val queue = ArrayDeque<Node>().apply {
        add(Node(0, 0, ""))
    }

    var ret: String = s1 + s2

    while (queue.isNotEmpty()) {
        val node = queue.first()
        queue.removeFirst()

        if (node.pos1 == s1.length && node.pos2 == s2.length) {
            if (ret.length > node.result.length) {
                ret = node.result
            }
            continue
        } else if (node.pos1 == s1.length) {
            val suffix = s2.substring(node.pos2).replace("*", "")
            val prefix = s2.substring(0, node.pos2).replace("*", "")
            if (node.result.endsWith(suffix) && !(suffix.isNotEmpty() && prefix.endsWith(suffix))) {
                val result = node.result + suffix
                if (ret.length > result.length) {
                    ret = result
                }
            }
            continue
        } else if (node.pos2 == s2.length) {
            val suffix = s1.substring(node.pos1).replace("*", "")
            val prefix = s1.substring(0, node.pos1).replace("*", "")
            if (node.result.endsWith(suffix) && !(suffix.isNotEmpty() && prefix.endsWith(suffix))) {
                val result = node.result + suffix
                if (ret.length > result.length) {
                    ret = result
                }
            }
            continue
        }

        val ch1 = s1[node.pos1]
        val ch2 = s2[node.pos2]

        if (ch1 == ch2) {
            val result = if (ch1 == '*') node.result else node.result + ch1
            queue.add(Node(node.pos1 + 1, node.pos2 + 1, result))

            if (ch1 == '*') {
                queue.add(Node(node.pos1 + 1, node.pos2, result))
                queue.add(Node(node.pos1, node.pos2 + 1, result))
            }
        }
        if (ch1 == '*' && ch2 != '*') {
            val result = node.result + ch2
            queue.add(Node(node.pos1, node.pos2 + 1, result))
            queue.add(Node(node.pos1 + 1, node.pos2 + 1, result))

            // '*'을 빈 문자열로 없애는 경우
            queue.add(Node(node.pos1 + 1, node.pos2, node.result))
        }
        if (ch1 != '*' && ch2 == '*') {
            val result = node.result + ch1
            queue.add(Node(node.pos1 + 1, node.pos2, result))
            queue.add(Node(node.pos1 + 1, node.pos2 + 1, result))

            // '*'을 빈 문자열로 없애는 경우
            queue.add(Node(node.pos1, node.pos2 + 1, node.result))
        }
    }

    return if (ret == s1 + s2) "-1" else ret
}

fun main() {
    val s1 = readlnOrNull() ?: ""
    val s2 = readlnOrNull() ?: ""

    val answer =
        // 같은 문자열인 경우
        if (s1.replace("*", "") == s2.replace("*", "")) {
            s1.replace("*", "")
        }
        // s2에서 '*'을 제거한 문자열이 정답
        else if (s1 == "*") {
            s2.replace("*", "")
        }
        // s1에서 '*'을 제거한 문자열이 정답
        else if (s2 == "*") {
            s1.replace("*", "")
        }
        // 이제 생각을 해보자
        else {
            solve(s1, s2)
        }

    print("$answer\n")
}

/*
반례 모음

12% 반례
HE*LLO
HE*L
-1

51% 반례
HE*LLO
HEKKKKLLO*
HEKKKKLLO

61% 반례
*SUFIX
*SUFIXIX
-1

 */
