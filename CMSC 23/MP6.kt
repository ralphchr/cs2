package lib

fun doubledInt(x: Int): Int {
    return x * 2
}

fun largest(x: Float, y: Float): Float {
    if (x >= y)
        return x
    else
        return y
    return 0.0f
}
fun isVertical(a: Pair<Float, Float>, b: Pair<Float, Float>): Boolean {
    var result: Boolean = a.first == b.first && a.second != b.second
    return result
}


fun primes(n: Int): List<Int> {
    var result: List<Int> = emptyList()
    var num = 2

    while (result.size < n){
        var checker = true

        for (i in 2 until num){
            if (num % i == 0){
                checker = false
                break
            }
        }

        if (checker == true)
            result = result + num
        num++
    }
    return result
}


fun fibonacci(n: Int): List<Int> {
    var result: List<Int> = emptyList()

    var a = 0
    var b = 1

    while (result.size < n){
        result = result + a
        var c: Int = a + b
        a = b
        b = c
    }

    return result
}

fun sortedIntegers(l: List<Int>): List<Int> {
    val result = l.toMutableList()
    for (i in 0 until result.size){
        for (j in 0 until result.size - i - 1){
            if (result[j] >= result[j+1]){
                var temp: Int = result[j]
                result[j] = result[j+1]
                result[j+1] = temp
            }
        }
    }

    return result
}


fun sublists(l: List<Int>): List<List<Int>> {
    var result: List<List<Int>> = listOf(emptyList())

    for (i in 0 until l.size){
        var temp: List<Int> = emptyList()

        for (j in i until l.size){
            temp = temp + l[j]
            result = result + listOf(temp)
        }
    }

    return result
}
