//
//  main.swift
//  TaskF
//
//  Created by Ivan Kozlov on 23/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation
func method1()->Void{
 let k = Int(readLine()!)!
 
 var elements = Array(repeating: 0, count: 101)
 
 for _ in 0..<k{
    let elems = readLine()!.split(separator: " ")
    let size = Int(elems[0])!
    for i in 0..<size {
        let tmp = Int(elems[i+1])!
        elements[tmp] += 1
    }
 }
 var str = ""
 for i in 0..<elements.count where (elements[i] > 0){
 for _ in 0..<elements[i] {str += "\(i) "}
 }
    print(str)
 }

func merge(input: [Int], index1: Int, index2: Int, size: Int)->[Int]{
    var i = 0
    var k = 0
    var out = input
    while (i < index2) && (k < size-index2)
    {
        if(input[i + index1] < input[k + index2])
        {
            out[index1 + i + k] = input[i+index1]
            i += 1
        } else{
            out[index1 + i + k] = input[k + index2]
            k += 1
        }
    }
    
    while(i < index2 - index1) {
        out[index1 + i + k] = input[i+index1]
        i += 1
    }
    while(k < size-index2) {
        out[index1 + i + k] = input[k+index2]
        k += 1
    }
    return out
}

func powerOf2(_ i: Int)->Int{
    var step = 1
    while step < i {step *= 2}
    return step
}

func method2()->Void{
    //    let k = 4
    guard let k = Int(readLine()!) else {return}
    var arr = [Int]()
    var index = Array(repeating: 0, count: powerOf2(k)+1)
    var start = 0
    
    for i in 0..<k{
        index[i] = start
        let elems = readLine()!.split(separator: " ")
        let size = Int(elems[0])!
        for i in 0..<size {arr.append(Int(elems[i + 1])!)}
        start += size
    }
    for i in k...powerOf2(k) {index[i] = start}

    var step = 1
    while (step < k)
    {
        for i in stride(from: 0, to: k-step+1, by: 2*step){
            arr = merge(input: arr, index1: index[i], index2: index[i + step], size: index[i+2 * step] - index[i])
        }
        step *= 2
    }
    for elem in arr {print(elem, terminator: " ")}
}

method1()

