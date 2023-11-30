//
//  LoadingScreen.swift
//  Gradify
//
//  Created by Андрiй on 28.11.2023.
//

import SwiftUI

struct LoadingScreen: View
{
    var body: some View
    {
        ZStack
        {
            Color.black.opacity(0.25)
            
            ProgressView()
                .frame(width: 70, height: 70)
                .background(Color("BackgroundProgressView"))
                .cornerRadius(10)
                .shadow(radius: 10)
                //.colorScheme(.dark)
        }// ZStack
        .ignoresSafeArea()
    }
}

#Preview
{
    LoadingScreen()
}
