//
//  GradifyApp.swift
//  Gradify
//
//  Created by Андрiй on 25.10.2023.
//

import SwiftUI

@main
struct GradifyApp: App
{
    @State private var isMainWindowOpen = false
    
    var body: some Scene
    {
        WindowGroup
        {
            if isMainWindowOpen
            {
                MainMenuView()
                    .onAppear
                    {
                        useStyleMiniWindow(status: false)
                    }
            }
            else
            {
                LoginView(isShowingMainWindow: $isMainWindowOpen)
                    .onAppear
                    {
                        useStyleMiniWindow(status: true)
                    }
            }
            
        }
        .windowResizability(.contentSize)
    }
    
    func useStyleMiniWindow(status: Bool)
    {
        NSApp.windows.first?.standardWindowButton(.zoomButton)?.isHidden = status
        NSApp.windows.first?.standardWindowButton(.miniaturizeButton)?.isHidden = status
        NSApp.windows.first?.titlebarAppearsTransparent = status
    }
}
