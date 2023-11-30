//
//  LoginModel.swift
//  Gradify
//
//  Created by Андрiй on 29.11.2023.
//

import Foundation
import SwiftUI
import Firebase

class LoginModel: ObservableObject
{
    @Published var userName:    String = ""
    @Published var password:    String = ""
    
    @Published var authStatus: Bool = true
    @Published var isLoading:   Bool = false
    
    
    func loginUser()
    {
        Auth.auth().signIn(withEmail: userName, password: password)
        { result, error in
            if error != nil
            {
                print(error!.localizedDescription)
                self.authStatus = false
            }
            else
            {
                if let _ = result
                {
                    self.authStatus = true
                    print("true")
                }
            }
        }// auth to firebase :)

        
        
        isLoading = true
        
        DispatchQueue.main.asyncAfter(deadline: .now() + 1.5)
        {
            withAnimation
            {
                self.isLoading = false
            }
        }
        
        
    }// func loginUser()
    
    
    
    func resetPassword()
    {
        
    }// func resetPassword()
    
    
}
