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

    @IBAction func Interrupt(_ sender: Any) {
        if let input = self.Input.text
        {
            self.Output.text = "Answer \(EratPrime(Int(input)!))"
        }
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }


}
