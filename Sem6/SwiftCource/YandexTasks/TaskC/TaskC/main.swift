//
//  main.swift
//  TaskC
//
//  Created by Ivan Kozlov on 21/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation

let n = Int(readLine()!)!
var tmp = 0
var prev:Int?

for _ in 0..<n{
    tmp = Int(readLine()!)!
    if(tmp != prev){
        print(String(tmp))
        prev = tmp
    }
}

