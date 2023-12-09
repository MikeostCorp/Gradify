//
//  GradifyApp.swift
//  Gradify
//
//  Created by Андрiй on 25.10.2023.
//

import SwiftUI
import Firebase


struct WindowAccessor: NSViewRepresentable
{
   @Binding var window: NSWindow?

   func makeNSView(context: Context) -> NSView
   {
      let view = NSView()
      DispatchQueue.main.async {
         self.window = view.window
      }
      return view
   }

   func updateNSView(_ nsView: NSView, context: Context) {}
}


@main
struct GradifyApp: App
{
    init()
    {
        FirebaseApp.configure()
    }
    
    @State private var window: NSWindow?
    @State private var isLogined: Bool = false
    var screen = NSScreen.main?.visibleFrame

    var body: some Scene
    {
        WindowGroup(id: "startView")
        {
            StartView(isLogined: $isLogined)
                .onAppear
                {
                    useMiniWindowStyle(status: true)
                }
        }// startView window
        .windowResizability(.contentSize)
        .commands
        {
            // command if i need
        }

        WindowGroup(id: "loginView")
        {
            AuthView(currentLogin: $isLogined)
                .frame(minWidth: screen!.width / 1.8, minHeight: screen!.height - 200)
        } // loginView window
        .windowResizability(.contentSize)
        .windowStyle(HiddenTitleBarWindowStyle())
        .commands
        {
            // command if i need
        }

        WindowGroup(id: "mainWindow")
        {
            MainMenuView()
                .onAppear
            {
                useMiniWindowStyle(status: false)
            }
        }// mainView Window
        .commands
        {
            SidebarCommands()
        }

        

    }
    
    func useMiniWindowStyle(status: Bool)
    {
        NSApp.windows.first?.standardWindowButton(.zoomButton)?.isHidden = status
        NSApp.windows.first?.standardWindowButton(.miniaturizeButton)?.isHidden = status
        NSApp.windows.first?.titlebarAppearsTransparent = status
        
        //NSWindow.allowsAutomaticWindowTabbing = false
        //NSApp.windows.first?.backgroundColor = .clear
        
    }// func useMiniWindowStyle(status: Bool)
}

