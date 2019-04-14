//
//  Functions.swift
//  HelloWorld
//
//  Created by Ivan Kozlov on 10/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation

func EratBoundary(_ N:Int) -> Int
{
    var tmp = N
    if(tmp < 6) {tmp = 6}
    return tmp * Int(log(Double(tmp)) + 1) + tmp * Int(log(log(Double(tmp))) + 1)
}

func EratPrime(_ N:Int) -> Int
{
    if (N < 1) {return -1}
    let size = EratBoundary(N)
    var grid = Array(repeating: true, count: size)
    var counter = 0
    var start = 2
    while (counter != N)
    {
        if (grid[start])
        {
            counter += 1
            for i in stride(from: start * start, to: size, by: start) {grid[i] = false}
        }
        start += 1
    }
    return start - 1
}
