//
//  MainMenuView.swift
//  Gradify
//
//  Created by Андрiй on 29.10.2023.
//

import SwiftUI

struct MainMenuView: View
{
    @State private var selection: String? = "Item1"
    @State private var columnVisibility = NavigationSplitViewVisibility.detailOnly

    var body: some View
    {
        NavigationSplitView(columnVisibility: $columnVisibility)
        {
            List
            {
                Section("Test item")
                {
                    NavigationLink(destination: Text("Item 1"), tag: "Item1", selection: $selection)
                    {
                        Label("Item 1", systemImage: "circle.fill")
                    }
                    
                    NavigationLink(destination: Text("Item 2"), tag: "Item2", selection: $selection)
                    {
                        Label("Item 2", systemImage: "square.fill")
                    }
                    
                    NavigationLink(destination: ScrollView{Text("Item 3").frame(maxWidth: .infinity, maxHeight: .infinity)}, tag: "Item3", selection: $selection)
                    {
                        Label("Item 3", systemImage: "triangle.fill")
                    }
                }// Section 1
            } // List
            .safeAreaInset(edge: .bottom)
            {
                Button
                {
                    print("test setting")
                }
                label:
                {
                    Image(systemName: "gearshape.fill")
                    Text("Налаштування")
                }
                //.keyboardShortcut(.defaultAction)
                .padding(.bottom)
                .buttonStyle(.borderless)
                .foregroundColor(.accentColor)
            } // button auth for test
            
        }
        detail:
        {
            Text("Go auth Mishanya")
                .frame(maxWidth: .infinity, maxHeight: .infinity)
        }//detail if no selected
        .navigationTitle("Gradify dev build")

        //.frame(minWidth: 550)
    }
}

#Preview
{
    MainMenuView()
}
