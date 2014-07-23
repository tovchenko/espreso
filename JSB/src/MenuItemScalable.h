
#ifndef MenuItemScalable_H
#define MenuItemScalable_H

#include "cocos2d.h"
using namespace cocos2d;

namespace es {
    
    class MenuItemScalable : public MenuItemSprite {
    public:
        MenuItemScalable()
        : cocos2d::MenuItemSprite() {
        }
        
        static auto create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite=nullptr)->MenuItemSprite*;
        static auto create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback)->MenuItemSprite*;
        
        virtual auto selected()->void override;
        virtual auto unselected()->void override;
        
    protected:
        bool    _isCalled = false;
    };
}

#endif // MenuItemScalable_H

