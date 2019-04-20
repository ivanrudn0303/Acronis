//
//  Functions.swift
//  HelloWorld
//
//  Created by Ivan Kozlov on 10/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation

class PrimeFinder
{
    var lock = NSLock()
    var stopped = true
    var sem = DispatchSemaphore(value: 0)
    var grid = [Bool]()
    var gridReady = false
    
    func EratBoundary(_ N:Int?) -> Int
    {
        guard var tmp = N else {return -1}
        if(tmp < 6) {tmp = 6}
        return tmp * Int(log(Double(tmp)) + 1) + tmp * Int(log(log(Double(tmp))) + 1)
    }

    func EratPrime(_ n:Int?) -> Int
    {
        guard let N = n else {return -1}
        if (N < 1) {return -1}
        let size = EratBoundary(N)
        if ((size <= grid.count) && gridReady) {return Find(N)}
        gridReady = false
        grid = Array(repeating: true, count: size)
        var counter = 0
        var start = 2
        while (counter != N)
        {
            if (grid[start])
            {
                counter += 1
                for i in stride(from: start * start, to: size, by: start) {
                    grid[i] = false
                    if(stopped) {return -1}
                }
                if(stopped) {return -1}
            }
            start += 1
        }
        gridReady = true
        return start - 1
    }
    func Find(_ n: Int) -> Int
    {
        var num = n
        var start = 2
        while (num > 0)
        {
            if(grid[start]) {num -= 1}
            start += 1
            if(stopped) {return -1}
        }
        return start - 1
    }
}
