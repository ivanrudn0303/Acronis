//
//  ViewController.swift
//  HelloWorld
//
//  Created by Ivan Kozlov on 28/03/2019.
//  Copyright © 2019 Ivan Kozlov. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    
    @IBOutlet weak var Output: UILabel!
    @IBOutlet weak var Input: UITextField!
    @IBOutlet weak var Butt: UIButton!
    
    var finder = PrimeFinder()
    
    @IBAction func Interrupt(_ sender: Any) {
        finder.lock.lock()
        if(!finder.stopped) {
            finder.stopped = true
            finder.lock.unlock()
            finder.sem.wait()
            finder.stopped = false
        } else{
            finder.stopped = false
            finder.lock.unlock()
        }
        guard let input = self.Input.text else {return}
        
        let queue = DispatchQueue.global(qos: .userInitiated)
        queue.async(execute: {[weak this = self] in
                guard let that = this else{return}
                let res = that.finder.EratPrime(Int(input))
                var resStr = ""
                that.finder.lock.lock()
                if that.finder.stopped{
                    resStr = String("Stopped")
                    that.finder.sem.signal()
                } else{
                    resStr = String("Answer \(res)")
                    that.finder.stopped = true
                }
                that.finder.lock.unlock()
                DispatchQueue.main.sync {
                    that.Output.text = resStr
                }
            })
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
}
