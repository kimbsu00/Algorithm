var N: Int = 0
var K: Int = 0

fun Int.nextPos() = this.minus(1).let { num -> if (num >= 0) num else N.times(2).plus(num) }

fun Int.moveForward() = this.plus(1).mod(N.times(2))

fun solve(belt: IntArray): Int {
    val robot: ArrayDeque<Int> = ArrayDeque()

    var startPos: Int = 0
    var endPos: Int = belt.size / 2 - 1
    var cnt: Int = 0
    var ret: Int = 0

    while (cnt < K) {
        ret += 1

        // 1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
        startPos = startPos.nextPos()
        endPos = endPos.nextPos()
        if (robot.firstOrNull() == endPos) {
            robot.removeFirst()
        }

        // 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다. 만약 이동할 수 없다면 가만히 있는다.
        // 2.1. 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1 이상 남아 있어야 한다.
        val loopCnt = robot.size
        for (idx in 0 until loopCnt) {
            val curRobotPos = robot.first()
            robot.removeFirst()

            val frontRobotPos = robot.lastOrNull() ?: -1

            val nextPos = curRobotPos.moveForward()
            // 로봇이 한 칸 앞으로 이동할 수 있는 경우
            if (nextPos != frontRobotPos && belt[nextPos] >= 1) {
                belt[nextPos] -= 1
                if (belt[nextPos] == 0) {
                    cnt += 1
                }

                // 로봇이 컨베이어 벨트에서 내려옴
                if (nextPos == endPos) {
                    // do nothing
                }
                // 로봇이 한 칸 앞으로 이동함
                else {
                    robot.add(nextPos)
                }
            }
            // 이동할 수 없는 경우
            else {
                robot.add(curRobotPos)
            }
        }

        // 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
        if (!robot.contains(startPos) && belt[startPos] >= 1) {
            belt[startPos] -= 1
            if (belt[startPos] == 0) {
                cnt += 1
            }
            robot.add(startPos)
        }

        // 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.
    }

    return ret
}

fun main() {
    readLine()?.split(' ')?.let { input ->
        N = input[0].toInt()
        K = input[1].toInt()
    }

    val belt: IntArray = IntArray(2 * N) { 0 }
    readLine()?.split(' ')?.let { input ->
        for (idx in input.indices) {
            belt[idx] = input[idx].toInt()
        }
    }

    val answer = solve(belt)
    println(answer)
}
