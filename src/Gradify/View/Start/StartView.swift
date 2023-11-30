//
//  LoginView.swift
//  Gradify
//
//  Created by Андрiй on 29.10.2023.
//

import SwiftUI

struct StartView: View
{
    @State private var animateStatus: Bool = true
    
    @Binding var isLogined: Bool
    
    @Environment(\.openWindow) private var openWindow
    @Environment(\.dismiss) private var dismiss
        
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
            
            VStack(spacing: 25)
            {
                InfoRowView(isAnimated: $animateStatus, imageName: "opticaldiscdrive.fill", mainText: "Ефективний облік даних", bodyText: "Gradify забезпечує ефективний облік та збереження інформації про студентів")

                InfoRowView(isAnimated: $animateStatus, imageName: "speedometer", mainText: "Швидкий доступ до інформації", bodyText: "Зручний та швидкий доступ до важливих даних про студентів")

                InfoRowView(isAnimated: $animateStatus, imageName: "gearshape.2", mainText: "Оптимізація роботи", bodyText: "Оптимізує роботу та допомагає організувати інформацію для зручного доступу")

            }//VStack with info
            .padding(.top, 40)
            .padding(.horizontal, 12)
            
            Spacer()
            
            Button
            {
                // go to auth
                dismiss()
                openWindow(id: "loginView")
                animateStatus = false
            }
            label:
            {
                Text("Далі")
                    .padding(.vertical, 6)
                    .padding(.horizontal, 34)
                    .font(.body)
            }// Button go to mainWindow or auth
            .keyboardShortcut(.defaultAction)
            .padding()
            
        }// VStack
        .padding(.top, 12)
        .frame(minWidth: 390, maxWidth: 390,
               minHeight: 600, maxHeight: 600)
        .font(.largeTitle.bold())
        .background(Color("BackgroundLeftLoginView"))
        //.ignoresSafeArea(.all, edges: .all)
        .navigationTitle("")
        .onAppear
        {
            if isLogined
            {
                // need fix!!!!!
                //dismiss()
                //openWindow(id: "mainWindow")
            }
        }
        
    }
}

struct StartView_Previews: PreviewProvider
{
    @State static var isLogined = false

    static var previews: some View
    {
        StartView(isLogined: $isLogined)
    }
}

