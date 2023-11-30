//
//  FastTutorialView.swift
//  Gradify
//
//  Created by Андрiй on 05.11.2023.
//

import SwiftUI

struct FastTutorialView: View
{
    
    @State private var selectedTab = 0
    let tabCount = 3  // Замените это на количество ваших вкладок

    
    var body: some View
    {
        Text("Tab \(selectedTab + 1) Content")

        HStack
        {
            ForEach(0..<tabCount, id: \.self)
            { index in
                Button(action: {
                    withAnimation(Animation.easeInOut(duration: 0.5))
                    {
                        selectedTab = index

                    }
                })
                {
                    Circle()
                        .foregroundColor(index == selectedTab ? .blue : .gray)
                        .frame(width: 10, height: 10)
                }
                .buttonStyle(PlainButtonStyle())
            }
        }
        .frame(maxWidth: .infinity)
        .padding(10)
        
        
        HStack
        {
            Button
            {
                withAnimation(Animation.easeInOut(duration: 0.25))
                {
                    selectedTab -= 1
                }
            }
            label:
            {
                Text("Назад")
                    .padding(.horizontal)
                    .padding(.vertical, 2)

            }// Back button
            .keyboardShortcut(.cancelAction)
            
            Button
            {
                withAnimation(Animation.easeInOut(duration: 0.25))
                {
                    selectedTab += 1
                }
            }
            label:
            {
                Text("Вперед")
                    .padding(.horizontal)
                    .padding(.vertical, 2)
            }// Go button
            .keyboardShortcut(.defaultAction)


        }// HStack with button toogle
        //.font(.body.bold())
        .toolbar {
                        // This seems to cause strange behavior
            ToolbarItem(placement: .status) {
                            Text("Bottom Bar Content")
                        }
                    }


        //.tabViewStyle(.segmented) // Use an appropriate style for macOS here
        //.indexViewStyle(PageIndexViewStyle(backgroundDisplayMode: .always)) // You might need to change this for macOS as well
    }
}

#Preview
{
    FastTutorialView()
}
