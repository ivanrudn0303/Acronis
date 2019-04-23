//
//  main.swift
//  TaskF
//
//  Created by Ivan Kozlov on 23/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation

let k = Int(readLine()!)!

var elements = Array(repeating: 0, count: 101)

for _ in 0..<k{
    let size = Int(readLine()!)!
    for _ in 0..<size {
        let tmp = Int(readLine()!)!
        elements[tmp] += 1
    }
}

for i in 0..<elements.count where (elements[i] > 0){
    for _ in 0..<elements[i] {print("\(i)", terminator: " ")}
}
