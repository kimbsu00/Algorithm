private var N: Int = 0
private lateinit var graph: MutableList<MutableList<Int>>
private lateinit var visited: MutableList<Boolean>

private fun solve(pNode: Int) {
    visited[pNode] = true

    for (next in graph[pNode]) {
        if (!visited[next]) {
            solve(next)
        }
    }
}

fun main() {
    readLine()?.let { input -> N = input.toInt() }
    graph = MutableList(N) { mutableListOf<Int>() }
    visited = MutableList(N) { false }

    for (idx in 0 until N - 2) {
        readLine()?.split(' ')?.let { input ->
            val castleA = input[0].toInt() - 1
            val castleB = input[1].toInt() - 1

            graph[castleA].add(castleB)
            graph[castleB].add(castleA)
        }
    }

    val answer: MutableList<Int> = mutableListOf()
    for (node in 0 until N) {
        if (!visited[node]) {
            solve(node)
            answer.add(node + 1)
        }
    }

    println("${answer[0]} ${answer[1]}")
}
