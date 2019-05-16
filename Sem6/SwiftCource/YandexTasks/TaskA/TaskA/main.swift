//
//  main.swift
//  TaskA
//
//  Created by Ivan Kozlov on 21/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//
import Foundation

let jewlery = readLine()!
let stones = readLine()!
var count = 0

for chr in stones{
    if (jewlery.contains(chr)) {count += 1}
}

print(count)

