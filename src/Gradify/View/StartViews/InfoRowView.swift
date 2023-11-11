//
//  InfoRowView.swift
//  Gradify
//
//  Created by Андрiй on 31.10.2023.
//

import SwiftUI

struct InfoRowView: View
{
    @Binding var isAnimated: Bool
    @State var startAnimate = true

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
                .symbolEffect(.bounce, value: startAnimate)
                .onAppear
                {
                    animateIcon()
                }

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

    func animateIcon()
    {
        if isAnimated
        {
            startAnimate.toggle()
            
            DispatchQueue.global(qos: .background).asyncAfter(deadline: .now() + 5)
            {
                DispatchQueue.main.async
                {
                    animateIcon()
                }
            }
        }
    }// animateIcon func

}


struct InfoRowView_Previews: PreviewProvider
{
    @State static var isAnimated = false
    static var imageName = "questionmark"
    static var mainText = "Test"
    static var bodyText = "Body_text!"

    static var previews: some View
    {
        InfoRowView(isAnimated: $isAnimated, imageName: imageName, mainText: mainText, bodyText: bodyText)
    }
}
