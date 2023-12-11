//
//  WindowController.swift
//  Gradify
//
//  Created by Андрiй on 11.12.2023.
//

import AppKit
import SwiftUI

class WindowController: NSWindowController //NSWindowDelegate
{
    convenience init() 
    {
        let window = NSWindow(
            contentRect: NSRect(x: 0, y: 0, width: 480, height: 270),
            styleMask: [.miniaturizable, .closable, .resizable, .titled],
            backing: .buffered, defer: false)

        window.isMovableByWindowBackground = true
        window.center()
        window.styleMask.update(with: .fullSizeContentView)

        self.init(window: window)
    }// func convenience init

    func setMainWindow()
    {
        let hostingController = NSHostingController(rootView: MainMenuView())
        window?.contentView = NSHostingView(rootView: hostingController.rootView)
    }// func setMainWindow

    func useMiniWindowStyle(status: Bool)
    {
        window?.standardWindowButton(.zoomButton)?.isHidden = status
        window?.standardWindowButton(.miniaturizeButton)?.isHidden = status
        window?.titlebarAppearsTransparent = status
    }// func useMiniWindowStyle(status: Bool)

    
    func windowWillClose(_ notification: Notification)
    {
        // Additional cleanup or actions when the window is closed.
    }// func windowWillClose
}

