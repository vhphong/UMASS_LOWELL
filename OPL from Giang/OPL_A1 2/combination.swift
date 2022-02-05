//
//  main.swift
//  Swift Combintation
//
//  Created by Hilton Carboo and Muhammad Muneebon 2/3/18.
//  Copyright © 2018 BlaqCo. All rights reserved.
//

import Foundation

// adding combinations
func addCombo(prevCombo: [Int], pivotList: [Int]) -> [([Int], [Int])]
{
    var pivotList = pivotList
    return (0..<pivotList.count).map {_ -> ([Int], [Int]) in (prevCombo + [pivotList.remove(at: 0)], pivotList)}
}

// get the length
func combosOfLength(n: Int, m: Int) -> [[Int]]
{
    return [Int](1...m).reduce([([Int](), [Int](0..<n))]){(accum, _) in accum.flatMap(addCombo)}.map {$0.0}
}


// print N
print("Enter a N: ", terminator: "")
let N = Int(readLine()!)

// print K
print("Enter a K: ", terminator: "")
let K = Int(readLine()!)

// print out the result
print(combosOfLength(n: N!, m: K!))

