
#ifndef EspresoButton_H
#define EspresoButton_H

#include "cocos2d.h"
#include "ui/UIButton.h"
using namespace cocos2d;

namespace es {

    class EspresoButton : public ui::Button {
    DECLARE_CLASS_GUI_INFO
    public:
        static auto create()->EspresoButton*;
        
    protected:
        virtual auto onPressStateChangedToNormal()->void override;
        virtual auto onPressStateChangedToPressed()->void override;
        
        auto getPressedCoef() const->double;
        auto getPressAction(double sx, double sy) const->Action*;
    };
}

#endif // EspresoButton_H

