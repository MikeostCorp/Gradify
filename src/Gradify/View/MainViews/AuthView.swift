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
    @State private var isRemberMe: Bool = false
    @State private var isWrongAuth: Bool = false
    @State private var forgetPassAlertShow: Bool = false
    @State private var isHoverOnButton: Bool = false
    @State private var isRegistration: Bool = false

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
                        .shadow(radius: 4)

                    Image(systemName: "arrow.down")
                        .resizable()
                        .aspectRatio(contentMode: .fit)
                        .frame(width: 45, height: 45)
                        .padding(.top, 65)
                        .foregroundColor(Color("ArrowCloudLoginView"))
                        .shadow(radius: 4)
                }// ZStack with hello photo
                
                Text("З поверненням!")
                    .font(.title.bold())
                
                Spacer()
                
                VStack(spacing: 16)
                {
                    Text(isWrongAuth ? "Помилка авторизації, не вірний пароль або логін!" : " ")
                            .foregroundColor(Color.red)
                            .transition(.move(edge: .bottom))

                    VStack(spacing: 16)
                    {
                        TextField("Введіть логін", text: $login)
                            .textFieldStyle(PlainTextFieldStyle())
                            .padding(.vertical, 8)
                            .padding(.horizontal, 8)
                            .textContentType(.username)
                            .background(RoundedRectangle(cornerRadius: 8)
                                .stroke(style: StrokeStyle(lineWidth: 1))
                                .foregroundColor(isWrongAuth ? Color.red.opacity(0.7) : Color.gray.opacity(0.7)))
                        
                        SecureField("Введіть пароль", text: $password)
                            .textFieldStyle(PlainTextFieldStyle())
                            .padding(.vertical, 8)
                            .padding(.horizontal, 8)
                            .textContentType(.password)
                            .background(RoundedRectangle(cornerRadius: 8)
                                .stroke(style: StrokeStyle(lineWidth: 1))
                                .foregroundColor(isWrongAuth ? Color.red.opacity(0.7) : Color.gray.opacity(0.7)))
                    }// VStack with Textfield
                    
                    HStack
                    {
                        Toggle("Запам'ятати мене", isOn: $isRemberMe)
                            //.labelsHidden()
                            //.toggleStyle(CheckboxToggleStyle())
                        
                        Spacer()
                        
                        Button
                        {
                            print("forget pass")
                            forgetPassAlertShow.toggle()
                        }
                        label:
                        {
                            Text("Забули пароль?")
                                .foregroundColor(Color.blue)
                                .underline(true, color: Color.blue)
                                .onHover
                                { isHovered in
                                    self.isHoverOnButton = isHovered
                                    changeCursor()
                                }
                        }
                        .buttonStyle(PlainButtonStyle())
                        .alert(isPresented: $forgetPassAlertShow)
                        {
                            Alert(
                                title: Text("Забули пароль?"),
                                message: Text("Якщо ви забули пароль, будь ласка, зверніться до адміністрації або напишіть на пошту support@gradify.online"),
                                primaryButton: .default(Text("Написати")){
                                    
                                    if let mailURL = URL(string: "mailto:support@gradify.online")
                                    {
                                        NSWorkspace.shared.open(mailURL)
                                    }
                                },//Primary button

                                secondaryButton: .cancel(Text("Скасувати"))
                            )
                        }
                        
                    }// HStack with remember me Toogle and button forget pass
                    
                    Button
                    {
                        // temp if
                        if login == "" || password == ""
                        {
                            print("auth!")
                            withAnimation(Animation.easeOut(duration: 0.25))
                            {
                                isWrongAuth.toggle()
                            }
                        }// if for auth
                    }
                    label:
                    {
                        Spacer()
                        
                        Text("Авторизуватись")
                            .padding(.vertical, 6)
                        
                        Spacer()
                        
                        Image(systemName: "arrow.right")
                    }// Auth Button
                    .shadow(radius: 6)
                    .keyboardShortcut(.defaultAction)
                    .onHover
                    { isHovered in
                        self.isHoverOnButton = isHovered
                        changeCursor()
                    }
                
                    HStack
                    {
                        Text("Відсутній аккаунту?")
                            .foregroundColor(Color.gray)
                        
                        Button
                        {
                            isRegistration.toggle()
                        }
                        label:
                        {
                            Text("Зареєструйтесь")
                                .foregroundColor(Color.blue)
                                .underline(true, color: Color.blue)
                                .onHover
                                { isHovered in
                                    self.isHoverOnButton = isHovered
                                    changeCursor()
                                }
                        }
                        .buttonStyle(PlainButtonStyle())
                        .alert(isPresented: $isRegistration)
                        {
                            Alert(
                                title: Text("Реєстрація"),
                                message: Text("Дякуємо за вибір нашого сервісу! Для створення облікового запису та отримання повного доступу, будь ласка, звертайтеся до нашої служби підтримки за електронною адресою support@gradify.online. Ми завжди готові допомогти!"),
                                primaryButton: .default(Text("Написати")){
                                    
                                    if let mailURL = URL(string: "mailto:support@gradify.online")
                                    {
                                        NSWorkspace.shared.open(mailURL)
                                    }
                                },//Primary button

                                secondaryButton: .cancel(Text("Скасувати"))
                            )
                        }
                    }// Hstack for register user
                                        
                }//VStack with TextField login, pass and button auth
                .padding(.horizontal, 32)
                .padding(.bottom, 20)
        
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
                    .shadow(radius: 14)
            }// VStack with photo
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .background(Color("BackgroundRightLoginView"))
            
        }//Main HStack
        .ignoresSafeArea(.all, edges: .all)
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .background(Color("BackgroundLeftLoginView"))
        //.background(VisualEffectView())
        
    }
    
    func changeCursor()
    {
        DispatchQueue.main.async
        {
            if (self.isHoverOnButton)
            {
                NSCursor.pointingHand.push()
            }
            else
            {
                NSCursor.pop()
            }
        }
    }// func changeCursor()
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
