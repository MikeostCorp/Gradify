//
//  InfoRowView.swift
//  Gradify
//
//  Created by Андрiй on 31.10.2023.
//

import SwiftUI

struct InfoRowView: View
{
     var imageName: String
     var mainText: String
     var bodyText: String

    var body: some View
    {
        HStack
        {
            Image(systemName: imageName)
                .foregroundColor(Color.blue)
                .aspectRatio(contentMode: .fit)
                .frame(width: 30, height: 30, alignment: .center)

            VStack
            {
                Text("\(mainText)")
                    .font(.body.bold())
                    .frame(maxWidth: .infinity, alignment: .leading) // Выравнивание текста слева


                Text("\(bodyText)")
                    .font(.callout)
                    .foregroundColor(.gray)
                    .frame(maxWidth: .infinity, alignment: .leading) // Выравнивание текста слева

            } // VStack with info
            .padding(.horizontal, 12)
            
            Spacer()
        } // Main HStack with info and image
        .padding(6)
        .padding(.horizontal, 12)
    }// body
}

struct InfoRowView_Previews: PreviewProvider
{
    static var imageName = "questionmark"
    static var mainText = "Test"
    static var bodyText = "Body_text!"

    static var previews: some View
    {
        InfoRowView(imageName: imageName, mainText: mainText, bodyText: bodyText)
    }
}
