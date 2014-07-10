/**
 * @module espreso
 */
var cc = cc || {};

/**
 * @class EspresoAction
 */
cc.Action = {

/**
 * @method startWithTarget
 * @param {cc.Node} arg0
 */
startWithTarget : function (
node 
)
{
},

/**
 * @method reverse
 * @return {cc.Action}
 */
reverse : function (
)
{
    return cc.Action;
},

/**
 * @method setOriginalTarget
 * @param {cc.Node} arg0
 */
setOriginalTarget : function (
node 
)
{
},

/**
 * @method clone
 * @return {cc.Action}
 */
clone : function (
)
{
    return cc.Action;
},

/**
 * @method getOriginalTarget
 * @return {cc.Node}
 */
getOriginalTarget : function (
)
{
    return cc.Node;
},

/**
 * @method stop
 */
stop : function (
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method getTarget
 * @return {cc.Node}
 */
getTarget : function (
)
{
    return cc.Node;
},

/**
 * @method setTag
 * @param {int} arg0
 */
setTag : function (
int 
)
{
},

/**
 * @method getTag
 * @return {int}
 */
getTag : function (
)
{
    return 0;
},

/**
 * @method setTarget
 * @param {cc.Node} arg0
 */
setTarget : function (
node 
)
{
},

/**
 * @method isDone
 * @return {bool}
 */
isDone : function (
)
{
    return false;
},

/**
 * @method create
 * @return {es::EspresoAction}
 */
create : function (
)
{
    return es::EspresoAction;
},

/**
 * @method EspresoAction
 * @constructor
 */
EspresoAction : function (
)
{
},

};

/**
 * @class EspresoComponent
 */
cc.Component = {

/**
 * @method setEnabled
 * @param {bool} arg0
 */
setEnabled : function (
bool 
)
{
},

/**
 * @method setName
 * @param {String} arg0
 */
setName : function (
str 
)
{
},

/**
 * @method isEnabled
 * @return {bool}
 */
isEnabled : function (
)
{
    return false;
},

/**
 * @method serialize
 * @param {void} arg0
 * @return {bool}
 */
serialize : function (
void 
)
{
    return false;
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method getOwner
 * @return {cc.Node}
 */
getOwner : function (
)
{
    return cc.Node;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setOwner
 * @param {cc.Node} arg0
 */
setOwner : function (
node 
)
{
},

/**
 * @method getName
 * @return {String}
 */
getName : function (
)
{
    return ;
},

/**
 * @method create
 * @return {es::EspresoComponent}
 */
create : function (
)
{
    return es::EspresoComponent;
},

/**
 * @method EspresoComponent
 * @constructor
 */
EspresoComponent : function (
)
{
},

};

/**
 * @class OrientationManager
 */
cc.OrientationManager = {

/**
 * @method getOrientation
 * @return {es::OrientationManager::Orientation}
 */
getOrientation : function (
)
{
    return es::OrientationManager::Orientation;
},

/**
 * @method getInstance
 * @return {es::OrientationManager}
 */
getInstance : function (
)
{
    return es::OrientationManager;
},

};
