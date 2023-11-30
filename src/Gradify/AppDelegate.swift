//
//  AppDelegate.swift
//  Gradify
//
//  Created by Андрiй on 22.11.2023.
//

import Foundation
import SwiftUI

class AppDelegate: NSObject, NSApplicationDelegate
{
    func applicationDidFinishLaunching(_ notification: Notification)
    {
        let _ = NSApplication.shared.windows.map { $0.tabbingMode = .disallowed }
    }
}
