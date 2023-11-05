//
//  InfoRowView.swift
//  Gradify
//
//  Created by Андрiй on 31.10.2023.
//

import SwiftUI

struct InfoRowView: View
{
    @State private var isBouncing = false

     var imageName: String
     var mainText:  String
     var bodyText:  String

    var body: some View
    {
        HStack
        {
            Image(systemName: imageName)
                .foregroundColor(Color.blue)
                .aspectRatio(contentMode: .fit)
                .frame(width: 30, height: 30, alignment: .center)
            
                .onAppear
                {
                    withAnimation(Animation.easeInOut(duration: 0.5))
                    {
                        isBouncing.toggle()
                    }
                }
                .symbolEffect(.bounce.wholeSymbol, value: isBouncing)


            VStack
            {
                Text("\(mainText)")
                    .font(.body.bold())
                    .frame(maxWidth: .infinity, alignment: .leading)

                Text("\(bodyText)")
                    .font(.callout)
                    .foregroundColor(.gray)
                    .frame(maxWidth: .infinity, alignment: .leading)

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
