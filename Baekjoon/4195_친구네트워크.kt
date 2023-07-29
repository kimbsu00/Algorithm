private val nameIdxMap: MutableMap<String, Int> = mutableMapOf()
private val parent: MutableList<Int> = mutableListOf()
private val unionCnt: MutableMap<Int, Int> = mutableMapOf()

fun name2Idx(name: String): Int {
    return nameIdxMap[name].let { idx ->
        if (idx != null) {
            idx
        } else {
            parent.add(-1)

            val newIdx = nameIdxMap.size
            nameIdxMap[name] = newIdx
            newIdx
        }
    }
}

fun whoIsYourParent(node: Int): Int =
        if (node == -1) -1 else if (parent[node] == node) node else whoIsYourParent(parent[node])

fun solve(nodeA: Int, nodeB: Int): Int {
    val parentA = whoIsYourParent(nodeA)
    val parentB = whoIsYourParent(nodeB)

    // 둘 다 처음 추가되는 경우
    return if (parentA == -1 && parentB == -1) {
        parent[nodeA] = nodeB
        parent[nodeB] = nodeB

        unionCnt[nodeB] = 2
        unionCnt[nodeB] ?: 0
    }
    // A의 부모를 B의 부모로 설정
    else if (parentA == -1) {
        parent[nodeA] = parentB

        unionCnt[parentB]?.let { cnt -> unionCnt[parentB] = cnt + 1 }
        unionCnt[parentB] ?: 0
    }
    // B의 부모를 A의 부모로 설정
    else if (parentB == -1) {
        parent[nodeB] = parentA

        unionCnt[parentA]?.let { cnt -> unionCnt[parentA] = cnt + 1 }
        unionCnt[parentA] ?: 0
    }
    // 합집합 구하기
    else {
        // A가 속한 집합을 B가 속한 집합에 추가
        if (parentA != parentB) {
            parent[parentA] = parentB

            val cntA = unionCnt[parentA] ?: 0
            unionCnt.remove(parentA)
            unionCnt[parentB]?.let { cnt -> unionCnt[parentB] = cnt + cntA }
        }
        unionCnt[parentB] ?: 0
    }
}

fun main() {
    val TC = readLine()?.toInt() ?: 0

    val answer: MutableList<Int> = mutableListOf()
    for (tc in 0 until TC) {
        val F = readLine()?.toInt() ?: 0

        nameIdxMap.clear()
        parent.clear()
        unionCnt.clear()

        for (idx in 0 until F) {
            readLine()?.split(' ')?.let { input ->
                val nameA = input[0]
                val nameB = input[1]

                val nodeA = name2Idx(nameA)
                val nodeB = name2Idx(nameB)
                answer.add(solve(nodeA, nodeB))
            }
        }
    }

    for (ans in answer) {
        println(ans)
    }
}
