//
//  AuthView.swift
//  Gradify
//
//  Created by Андрiй on 09.11.2023.
//

import SwiftUI

struct AuthView: View
{
    @State private var login = ""
    @State private var password = ""
    @State private var rememberMe = false // do you remember the rain???

    var body: some View
    {
        HStack(spacing: 0)
        {
            VStack
            {
                Spacer()
                
                ZStack
                {
                    Image(systemName: "cloud.fill")
                        .resizable()
                        .aspectRatio(contentMode: .fit)
                        .frame(width: 100, height: 100)
                        .foregroundColor(Color("CloudLoginView"))
                    
                    Image(systemName: "arrow.down")
                        .resizable()
                        .aspectRatio(contentMode: .fit)
                        .frame(width: 45, height: 45)
                        .padding(.top, 65)
                        .foregroundColor(Color("ArrowCloudLoginView"))
                }// ZStack with hello photo
                
                Text("З поверненням!")
                    .font(.title.bold())
                
                Spacer()
                
                VStack(spacing: 16)
                {
                    VStack(spacing: 16)
                    {
                        TextField("Введіть логін", text: $login)
                            .textFieldStyle(PlainTextFieldStyle())
                            .padding(.vertical, 8)
                            .padding(.horizontal, 8)
                            .textContentType(.username)
                            .background(RoundedRectangle(cornerRadius: 8)
                                .stroke(style: StrokeStyle(lineWidth: 1))
                                .foregroundColor(.gray.opacity(0.7)))
                        
                        SecureField("Введіть пароль", text: $password)
                            .textFieldStyle(PlainTextFieldStyle())
                            .padding(.vertical, 8)
                            .padding(.horizontal, 8)
                            .textContentType(.password)
                            .background(RoundedRectangle(cornerRadius: 8)
                                .stroke(style: StrokeStyle(lineWidth: 1))
                                .foregroundColor(.gray.opacity(0.7)))
                    }// VStack with Textfield
                    //.padding(.vertical)
                    
                    HStack
                    {
                        Toggle("Запам'ятати мене", isOn: $rememberMe)
                            //.labelsHidden()
                            //.toggleStyle(CheckboxToggleStyle())
                        
                        Spacer()
                        
                        Button
                        {
                            print("forget pass")
                        }
                        label:
                        {
                            Text("Забули пароль?")
                                .foregroundColor(Color.blue)
                        }
                        .buttonStyle(PlainButtonStyle())
                        
                    }// HStack with remember me Toogle and button forget pass
                    
                    Button
                    {
                        print("auth!")
                    }
                    label:
                    {
                        Spacer()
                        
                        Text("Авторизуватись")
                            .padding(.vertical, 6)
                        
                        Spacer()
                        
                        Image(systemName: "arrow.right")
                    }// Auth Button
                    .keyboardShortcut(.defaultAction)
                }
                .padding(.horizontal, 32)
        
                Spacer()
            }// VStack with TextField for login
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            
            Spacer()
            
            VStack
            {
                Image(systemName: "swiftdata")
                    .resizable()
                    .aspectRatio(contentMode: .fit)
                    .padding(100)
                    .padding(.leading, -140)
            }// VStack with photo
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .background(Color("BackgroundRightLoginView"))
            
        }//Main HStack
        .ignoresSafeArea(.all, edges: .all)
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .background(Color("BackgroundLeftLoginView"))
        //.background(VisualEffectView())
    }
}

// maybe delete this
struct VisualEffectView: NSViewRepresentable
{
    func makeNSView(context: Context) -> NSVisualEffectView
    {
        let view = NSVisualEffectView()

        view.blendingMode = .behindWindow
        view.state = .active
        view.material = .underWindowBackground
        
        return view
    }

    func updateNSView(_ nsView: NSVisualEffectView, context: Context) { }
}// VisualEffectView: NSViewRepresentable


#Preview
{
    AuthView()
}
