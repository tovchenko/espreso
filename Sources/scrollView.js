/**
 * Created by mc309 on 3/14/14.
 */

var es = es || {};

es.ScrollView = cc.ScrollView.extend({

    ctor: function () {
        this._super();
    },

    onTouchMoved: function (touch, event) {
        if (!this.isVisible())
            return;

        if (this._touches.length === 1 && this._dragging) {
            this._touchMoved = true;
            var frame = this._getViewRect();
            var newPoint = this.convertTouchToNodeSpace(touch);
            var moveDistance = cc.pSub(newPoint, this._touchPoint);

            var dis = 0.0, locDirection = this._direction;
            if (locDirection === cc.SCROLLVIEW_DIRECTION_VERTICAL)
                dis = moveDistance.y;
            else if (locDirection === cc.SCROLLVIEW_DIRECTION_HORIZONTAL)
                dis = moveDistance.x;
            else
                dis = Math.sqrt(moveDistance.x * moveDistance.x + moveDistance.y * moveDistance.y);

            if (!this._touchMoved && Math.abs(cc.convertDistanceFromPointToInch(dis)) < MOVE_INCH) {
                return;
            }

            if (!this._touchMoved){
                moveDistance.x = 0;
                moveDistance.y = 0;
            }

            this._touchPoint = newPoint;
            this._touchMoved = true;

            if (cc.rectContainsPoint(frame, this.convertToWorldSpace(newPoint))) {
                switch (locDirection) {
                    case cc.SCROLLVIEW_DIRECTION_VERTICAL:
                        moveDistance.x = 0.0;
                        break;
                    case cc.SCROLLVIEW_DIRECTION_HORIZONTAL:
                        moveDistance.y = 0.0;
                        break;
                    default:
                        break;
                }

                // new code
                var locPosition = this._container.getPosition();
                var newX = locPosition.x + moveDistance.x;
                var newY = locPosition.y + moveDistance.y;

                var locSize = cc.size(this._container.getContentSize().width * this._container.getScale(),
                    this._container.getContentSize().height * this._container.getScale());
                if (newX > 0)
                    newX = moveDistance.x = 0;
                if (newY > 0)
                    newY = moveDistance.y = 0;
                if (newX + locSize.width < frame.width) {
                    var offset = frame.width - (newX + locSize.width);
                    newX += offset;
                    moveDistance.x += offset;
                }
                if (newY + locSize.height < frame.height) {
                    var offset = frame.height - (newY + locSize.height);
                    newY += offset;
                    moveDistance.y += offset;
                }
                // new code end

                this._scrollDistance = moveDistance;
                this.setContentOffset(cc.p(newX, newY));
            }

            var contP = this._container.getPosition();
            var contS = this._container.getContentSize();

        } else if (this._touches.length === 2 && !this._dragging) {
            var len = cc.pDistance(this._container.convertTouchToNodeSpace(this._touches[0]),
                this._container.convertTouchToNodeSpace(this._touches[1]));
            this.setZoomScale(this.getZoomScale() * len / this._touchLength);

            // new code
            var frame = this._getViewRect();
            var locPosition = cc.p(this._container.getPosition().x, this._container.getPosition().y);
            var locSize = cc.size(this._container.getContentSize().width * this._container.getScale(),
                this._container.getContentSize().height * this._container.getScale());

            if (locPosition.x > 0)
                locPosition.x = 0;
            if (locPosition.y > 0)
                locPosition.y = 0;
            if (locPosition.x + locSize.width < frame.width)
                locPosition.x += frame.width - (locPosition.x + locSize.width);

            if (locPosition.y + locSize.height < frame.height)
                locPosition.y += frame.height - (locPosition.y + locSize.height);

            this.setContentOffset(cc.p(locPosition.x, locPosition.y));
            // new code end
        }
    }
});

es.ScrollView.create = function (size, container) {
    var pRet = new es.ScrollView();
    if (arguments.length == 2) {
        if (pRet && pRet.initWithViewSize(size, container))
            return pRet;
    } else {
        if (pRet && pRet.init())
            return pRet;
    }
    return null;
};