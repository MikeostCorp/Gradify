//
//  GradifyApp.swift
//  Gradify
//
//  Created by Андрiй on 25.10.2023.
//

import SwiftUI
import Firebase
import Cocoa

@main
struct GradifyApp: App
{
    @State private var isLogined: Bool = false
        
    var screen = NSScreen.main?.visibleFrame
        
    init()
    {
        FirebaseApp.configure()
    }
    
    var body: some Scene
    {
        WindowGroup
        {
            MainMenuView()
                .onAppear
                {
                    let window = WindowController()
                    window.setMainWindow()
                    window.showWindow(nil)
                }
        }
        .commandsRemoved()
        .windowResizability(.contentSize)

        

    }
    
}


