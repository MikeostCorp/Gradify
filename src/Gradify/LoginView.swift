//
//  LoginView.swift
//  Gradify
//
//  Created by Андрiй on 29.10.2023.
//

import SwiftUI
import AppKit

struct LoginView: View
{
    @Binding var isShowingMainWindow: Bool
        
    var body: some View
    {
        VStack
        {
            Image(systemName: "homekit")
                .resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 100, height: 100, alignment: .center)
                .accentColor(Color.white)
            
            Text("Зустрічайте")
            Text("Gradify")
                .foregroundColor(.blue)
            
            Spacer()
            
            Button
            {
                // go to auth
                isShowingMainWindow = true
                //NSApplication.shared.keyWindow?.close()

            }
            label:
            {
                Text("Далі")
                    .padding(.vertical, 6)
                    .padding(.horizontal, 34)
                    .font(.body)
            }// Button go to mainWindow or auth
            .background(Color.blue)
            .foregroundColor(Color.white)
            .cornerRadius(8)
            .padding()
            
        }// VStack
        .padding(.top, 64)
        .frame(minWidth: 375, maxWidth: 375,
               minHeight: 550, maxHeight: 550)
        
        .font(.largeTitle.bold())
        .background(Color("BackgroundLoginView"))
        //.ignoresSafeArea(.all, edges: .all)
        .navigationTitle("")
    }
}

struct LoginView_Previews: PreviewProvider
{
    @State static var isShowingMainWindow = false

    static var previews: some View
    {
        LoginView(isShowingMainWindow: $isShowingMainWindow)
    }
}
