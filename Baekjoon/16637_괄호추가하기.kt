// URL: https://www.acmicpc.net/problem/16637

data class Expression(
    val exp: CharArray,
    val index: Int,
    var sum: Int = 0,
) {
    val isEmpty: Boolean
        get() = index >= exp.size
}

fun main() {
    readln().toInt().let { N ->        
        val exp =  readln().toCharArray().let { chars ->
            CharArray(N + 1) { index ->
                if (index == 0) {
                    '+'
                } else {
                    chars[index - 1]
                }
            }
        }
        val expression = Expression(exp, 0, 0)
        val expressionQ = ArrayDeque<Expression>().apply { add(expression) }

        var answer = Int.MIN_VALUE
        while (expressionQ.isNotEmpty()) {
            val current = expressionQ.removeFirst()

            if (current.isEmpty) {
                answer = maxOf(answer, current.sum)
            } else {
                val curIdx = current.index
                // 괄호 안 치는 경우
                val operator = current.exp[curIdx]
                val number = current.exp[curIdx + 1].digitToInt()
                val newSum = when (operator) {
                    '+' -> current.sum + number
                    '-' -> current.sum - number
                    '*' -> current.sum * number
                    else -> current.sum 
                }
                expressionQ.add(Expression(current.exp, curIdx + 2, newSum))

                // 괄호 치는 경우
                if (curIdx + 3 < current.exp.size) {
                    val nextOperator = current.exp[curIdx + 2]
                    val nextNumber = current.exp[curIdx + 3].digitToInt()
                    val bracketResult = when (nextOperator) {
                        '+' -> number + nextNumber
                        '-' -> number - nextNumber
                        '*' -> number * nextNumber
                        else -> number
                    }
                    val newBracketSum = when (operator) {
                        '+' -> current.sum + bracketResult
                        '-' -> current.sum - bracketResult
                        '*' -> current.sum * bracketResult
                        else -> current.sum 
                    }
                    expressionQ.add(Expression(current.exp, curIdx + 4, newBracketSum))
                }
            }
        }

        println(answer)
    }
}
