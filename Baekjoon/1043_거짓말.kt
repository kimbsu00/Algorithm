private var N: Int = 0
private var M: Int = 0
private val whoKnowsTruth: ArrayList<Int> = arrayListOf()
private val party: ArrayList<ArrayList<Int>> = arrayListOf()
private lateinit var graph: MutableList<MutableList<Int>>
private lateinit var visited: BooleanArray

fun dfs(node: Int) {
    visited[node] = true

    for (next in graph[node]) {
        if (!visited[next]) {
            dfs(next)
        }
    }
}

fun main() {
    readLine()?.split(' ')?.let { input ->
        N = input[0].toInt()
        M = input[1].toInt()
    }
    graph = MutableList(N) { mutableListOf() }

    readLine()?.split(' ')?.let { input ->
        for (idx in 1 until input.size) {
            val num = input[idx].toInt() - 1
            whoKnowsTruth.add(num)
        }

        for (idx in whoKnowsTruth.indices) {
            for (idx2 in idx + 1 until whoKnowsTruth.size) {
                val a = whoKnowsTruth[idx]
                val b = whoKnowsTruth[idx2]

                graph[a].add(b)
                graph[b].add(a)
            }
        }
    }

    for (cnt in 0 until M) {
        readLine()?.split(' ')?.let { input ->
            val list = arrayListOf<Int>()
            for (idx in 1 until input.size) {
                val num = input[idx].toInt() - 1
                list.add(num)
            }
            party.add(list)

            for (idx in list.indices) {
                for (idx2 in idx + 1 until list.size) {
                    val a = list[idx]
                    val b = list[idx2]

                    graph[a].add(b)
                    graph[b].add(a)
                }
            }
        }
    }

    if (whoKnowsTruth.isEmpty()) {
        println(M)
    } else {
        visited = BooleanArray(N) { false }

        for (node in whoKnowsTruth) {
            if (!visited[node]) {
                dfs(node)
            }
        }

        var answer = 0
        for (list in party) {
            var flag = true
            for (node in list) {
                if (visited[node]) {
                    flag = false
                    break
                }
            }

            if (flag) {
                answer += 1
            }
        }

        println(answer)
    }
}
