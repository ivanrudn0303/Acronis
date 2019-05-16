//
//  main.swift
//  TaskE
//
//  Created by Ivan Kozlov on 23/04/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import Foundation

if let str1 = readLine(), let str2 = readLine(){
    
    var alphabet1 = [Character:Int]()
    var alphabet2 = [Character:Int]()
    
    for chr in str1{
        if alphabet1[chr] != nil {
            alphabet1[chr]! += 1
        } else{
            alphabet1[chr] = 1
        }
    }
    
    for chr in str2{
        if alphabet2[chr] != nil{
            alphabet2[chr]! += 1
        } else{
            alphabet2[chr] = 1
        }
    }
    
    if(alphabet1 == alphabet2) {
        print("1")
    } else{
        print("0")
    }
}

