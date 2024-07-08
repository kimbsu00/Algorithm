package baekjoon

import java.util.Collections

fun Char.toIndex(): Int {
    return when (this) {
        in 'a'..'z' -> {
            2 * (this - 'a') + 1
        }

        in 'A'..'Z' -> {
            2 * (this - 'A')
        }

        else -> {
            -1
        }
    }
}

sealed class Node20210 {
    data class CharNode(val ch: Char) : Node20210(), Comparable<CharNode> {
        override fun compareTo(other: CharNode): Int {
            val thisIdx = ch.toIndex()
            val otherIdx = other.ch.toIndex()
            return thisIdx.compareTo(otherIdx)
        }
    }

    data class NumNode(
        val strNum: String,
        val noneZeroPostfix: String,
        val prefixZeroCnt: Int
    ) : Node20210(), Comparable<NumNode> {
        override fun compareTo(other: NumNode): Int {
            return if (noneZeroPostfix.length > other.noneZeroPostfix.length) {
                1
            } else if (noneZeroPostfix.length < other.noneZeroPostfix.length) {
                -1
            } else if (noneZeroPostfix > other.noneZeroPostfix) {
                1
            } else if (noneZeroPostfix < other.noneZeroPostfix) {
                -1
            } else {
                if (prefixZeroCnt > other.prefixZeroCnt) {
                    1
                } else if (prefixZeroCnt < other.prefixZeroCnt) {
                    -1
                } else {
                    0
                }
            }
        }
    }
}

fun main() {
    val N = readlnOrNull()?.toInt() ?: 0

    val inputList = arrayListOf<ArrayList<Node20210>>()
    for (inputIdx in 0..<N) {
        readlnOrNull()?.let { input ->
            val list = arrayListOf<Node20210>()

            var idx: Int = 0
            while (idx < input.length) {
                val ch = input[idx]

                val newNode = if (ch in '0'..'9') {
                    val sb = StringBuilder()
                    var prefixZeroCnt = 0
                    while (idx < input.length && input[idx] == '0') {
                        prefixZeroCnt += 1
                        sb.append(input[idx])
                        idx += 1
                    }

                    val noneZeroPostfixSb = StringBuilder()
                    while (idx < input.length && input[idx] in '0'..'9') {
                        sb.append(input[idx])
                        noneZeroPostfixSb.append(input[idx])
                        idx += 1
                    }
                    val strLong = sb.toString()
                    val noneZeroPostfix = noneZeroPostfixSb.toString()
                    Node20210.NumNode(strLong, noneZeroPostfix, prefixZeroCnt)
                } else {
                    val chIdx = if (ch in 'a'..'z') {
                        2 * (ch - 'a') + 1
                    } else if (ch in 'A'..'Z') {
                        2 * (ch - 'A')
                    } else {
                        continue
                    }
                    idx += 1
                    Node20210.CharNode(ch)
                }
                list.add(newNode)
            }
            inputList.add(list)
        }
    }

    Collections.sort(inputList, Comparator<ArrayList<Node20210>> { left, right ->
        var leftIdx = 0
        var rightIdx = 0

        while (leftIdx < left.size && rightIdx < right.size) {
            val leftNode = left[leftIdx]
            val rightNode = right[rightIdx]

            when (leftNode) {
                is Node20210.CharNode -> {
                    when (rightNode) {
                        is Node20210.CharNode -> {
                            val cmp = leftNode.compareTo(rightNode)
                            if (cmp != 0) {
                                return@Comparator cmp
                            }
                        }

                        is Node20210.NumNode -> {
                            return@Comparator 1
                        }
                    }
                }

                is Node20210.NumNode -> {
                    when (rightNode) {
                        is Node20210.CharNode -> {
                            return@Comparator -1
                        }

                        is Node20210.NumNode -> {
                            val cmp = leftNode.compareTo(rightNode)
                            if (cmp != 0) {
                                return@Comparator cmp
                            }
                        }
                    }
                }
            }

            leftIdx += 1
            rightIdx += 1
        }

        if (leftIdx == left.size && rightIdx == right.size) {
            0
        } else {
            if (leftIdx == left.size) -1 else 1
        }
    })

    inputList.forEach { list ->
        val sb = StringBuilder()
        for (node in list) {
            when (node) {
                is Node20210.CharNode -> sb.append(node.ch)
                is Node20210.NumNode -> sb.append(node.strNum)
            }
        }
        print("${sb.toString()}\n")
    }
}
