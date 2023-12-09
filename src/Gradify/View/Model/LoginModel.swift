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
    @Published var userName:        String = ""
    @Published var password:        String = ""
    @Published var emailForReset:   String = ""
    
    @Published var currentAuth:     Bool = false
    @Published var statusAuth:      Bool = false
    @Published var isLoading:       Bool = false
    
    func loginUser() async
    {
        isLoading = true
        
        do
        {
            let result = try await Auth.auth().signIn(withEmail: userName, password: password)
            
            self.statusAuth = false
            self.currentAuth = true
            print("true") // debug
        }
        catch
        {
            print("Error : \(error.localizedDescription)") // also debug
            self.statusAuth = true
        }

        withAnimation
        {
            self.isLoading = false
        }
    }// func loginUser() async

    
    
    func resetPassword() async
    {
        do
        {
            try await Auth.auth().sendPasswordReset(withEmail: emailForReset)
            {
                error in
            }
        }
        catch
        {
            print("Error : \(error.localizedDescription)") // also debug
        }
        
    }// func resetPassword()
    
    
}
