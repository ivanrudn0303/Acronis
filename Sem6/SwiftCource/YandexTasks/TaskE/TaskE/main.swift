//
//  main.swift
//  TaskE
//
//  Created by Ivan Kozlov on 23/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation

let str1 = readLine()!
let str2 = readLine()!

let alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "w", "x", "y", "z"]
//26 letters in alphabet
var letters1 = Array(repeating: 0, count: alphabet.count)
var letters2 = letters1

for chr in str1{
    letters1[alphabet.index(of: String(chr))!] += 1
}

for chr in str2{
    letters2[alphabet.index(of: String(chr))!] += 1
}

if(letters1 == letters2) {
    print("1")
} else{
    print("0")
}
