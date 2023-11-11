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
    var screen = NSScreen.main?.visibleFrame

    var body: some Scene
    {
        WindowGroup
        {
            AuthView()
                .frame(minWidth: screen!.width / 1.8, minHeight: screen!.height - 200)
        }
        .windowStyle(HiddenTitleBarWindowStyle())
        .windowResizability(.automatic)
        .commands
        {
            SidebarCommands()
        }

    }
    
    func useStyleMiniWindow(status: Bool)
    {
        NSApp.windows.first?.standardWindowButton(.zoomButton)?.isHidden = status
        NSApp.windows.first?.standardWindowButton(.miniaturizeButton)?.isHidden = status
        NSApp.windows.first?.titlebarAppearsTransparent = status
        //NSApp.windows.first?.backgroundColor = .clear
    }
}

/* use after make auth view
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
                 StartView(isShowingMainWindow: $isMainWindowOpen)
                     .onAppear
                     {
                         useStyleMiniWindow(status: true)
                     }
             }
         }
         .windowResizability(.contentSize)
         .commands
         {
             SidebarCommands()
         }
 
 */
