if(!window.ComponentArt_ItemLook_Loaded){window.ComponentArt_ItemLookCollection=function(_1){if(window.ComponentArt_Atlas){ComponentArt.Web.UI.ItemLookCollection.initializeBase(this);this.getDescriptor=function(){return _qE4(this);};}for(var i=0;i<_1.length;i++){var _3=_1[i];var _4=_3[1];this[_4]=this[i]=_q124(ComponentArt_ItemLook,_3);}this.length=_1.length;};window.ComponentArt_ItemLook=function(){if(window.ComponentArt_Atlas){ComponentArt.Web.UI.ItemLook.initializeBase(this);this.getDescriptor=function(){return _qE4(this);};}};ComponentArt_ItemLookCollection.prototype.PublicProperties=[];ComponentArt_ItemLookCollection.prototype.PublicMethods=[["GetProperty",,Object,[["propName",String]]],["SetProperty",,null,[["propName",String],["propValue",Object]]]];window.ComponentArt.Web.UI.ItemLookCollection=ComponentArt_ItemLookCollection;_qE3(ComponentArt_ItemLookCollection);if(window.ComponentArt_Atlas){ComponentArt.Web.UI.ItemLookCollection.registerClass("ComponentArt.Web.UI.ItemLookCollection");if(Sys.TypeDescriptor){Sys.TypeDescriptor.addType("componentArtWebUI","itemLookCollection",ComponentArt.Web.UI.ItemLookCollection);}}ComponentArt_ItemLookCollection.prototype.GetProperty=function(_5){return this[_5];};ComponentArt_ItemLookCollection.prototype.SetProperty=function(_6,_7){this[_6]=_7;};ComponentArt_ItemLook.prototype.PublicProperties=[["ActiveCssClass",String],["ActiveImageUrl",String],["ActiveLeftIconUrl",String],["ActiveRightIconUrl",String],["CssClass",String],["ExpandedCssClass",String],["ExpandedImageUrl",String],["ExpandedLeftIconUrl",String],["ExpandedRightIconUrl",String],["HoverCssClass",String],["HoverImageUrl",String],["HoverLeftIconUrl",String],["HoverRightIconUrl",String],["ImageHeight",Number],["ImageUrl",String],["ImageWidth",Number],["LabelPaddingBottom",Number],["LabelPaddingLeft",Number],["LabelPaddingRight",Number],["LabelPaddingTop",Number],["LeftIconHeight",Number],["LeftIconUrl",String],["LeftIconVisibility",Number],["LeftIconWidth",Number],["LookId",String],["RightIconHeight",Number],["RightIconUrl",String],["RightIconVisibility",Number],["RightIconWidth",Number]];ComponentArt_ItemLook.prototype.PublicMethods=[["ApplyTo",,null,[["destinationLook",ComponentArt_ItemLook]]],["ApplyFrom",,null,[["sourceLook",ComponentArt_ItemLook]]],["CopyTo",,null,[["destinationLook",ComponentArt_ItemLook]]],["CopyFrom",,null,[["sourceLook",ComponentArt_ItemLook]]],["GetProperty",,Object,[["propName",String]]],["IsEmpty",,Boolean],["SetProperty",,null,[["propName",String],["propValue",Object]]]];window.ComponentArt.Web.UI.ItemLook=ComponentArt_ItemLook;_qE3(ComponentArt_ItemLook);if(window.ComponentArt_Atlas){ComponentArt.Web.UI.ItemLook.registerClass("ComponentArt.Web.UI.ItemLook");if(Sys.TypeDescriptor){Sys.TypeDescriptor.addType("componentArtWebUI","itemLook",ComponentArt.Web.UI.ItemLook);}}ComponentArt_ItemLook.prototype.GetProperty=function(_8){return this[_8];};ComponentArt_ItemLook.prototype.SetProperty=function(_9,_a){this[_9]=_a;};ComponentArt_ItemLook.prototype.TransitoryProperties=ComponentArt_ItemLook.TransitoryProperties=[];ComponentArt_ItemLook.prototype.PermanentProperties=ComponentArt_ItemLook.PermanentProperties=["LookId",,"CssClass",,"HoverCssClass",,"ImageHeight",,"ImageWidth",,"LabelPaddingBottom",,"LabelPaddingLeft",,"LabelPaddingRight",,"LabelPaddingTop",,"ActiveCssClass",,"ExpandedCssClass",,"LeftIconUrl",,"HoverLeftIconUrl",,"LeftIconWidth",,"LeftIconHeight",,"ActiveLeftIconUrl",,"ExpandedLeftIconUrl",,"RightIconUrl",,"HoverRightIconUrl",,"RightIconWidth",,"RightIconHeight",,"ActiveRightIconUrl",,"ExpandedRightIconUrl",,"ImageUrl",,"HoverImageUrl",,"ActiveImageUrl",,"ExpandedImageUrl",,"RightIconVisibility",,"LeftIconVisibility",];ComponentArt_ItemLook.prototype.PropertyList=ComponentArt_ItemLook.PropertyList={"CssClass":0,"HoverCssClass":0,"ImageHeight":0,"ImageWidth":0,"LabelPaddingBottom":0,"LabelPaddingLeft":0,"LabelPaddingRight":0,"LabelPaddingTop":0,"ActiveCssClass":0,"ExpandedCssClass":0,"LeftIconUrl":0,"HoverLeftIconUrl":0,"LeftIconWidth":0,"LeftIconHeight":0,"ActiveLeftIconUrl":0,"ExpandedLeftIconUrl":0,"RightIconUrl":0,"HoverRightIconUrl":0,"RightIconWidth":0,"RightIconHeight":0,"ActiveRightIconUrl":0,"ExpandedRightIconUrl":0,"ImageUrl":0,"HoverImageUrl":0,"ActiveImageUrl":0,"ExpandedImageUrl":0,"RightIconVisibility":0,"LeftIconVisibility":0};ComponentArt_ItemLook.prototype.ApplyTo=function(_b){for(var i=0;i<this.PermanentProperties.length;i+=2){var _d=this.PermanentProperties[i];if(_b[_d]==null){_b[_d]=this[_d];}}};ComponentArt_ItemLook.prototype.ApplyFrom=function(_e){for(var i=0;i<this.PermanentProperties.length;i+=2){var _10=this.PermanentProperties[i];if(this[_10]==null){this[_10]=_e[_10];}}};ComponentArt_ItemLook.prototype.CopyTo=function(_11){for(var i=0;i<this.PermanentProperties.length;i+=2){var _13=this.PermanentProperties[i];_11[_13]=this[_13];}};ComponentArt_ItemLook.prototype.CopyFrom=function(_14){for(var i=0;i<this.PermanentProperties.length;i+=2){var _16=this.PermanentProperties[i];this[_16]=_14[_16];}};ComponentArt_ItemLook.prototype.IsEmpty=function(){for(var i=0;i<this.PermanentProperties.length;i+=2){var _18=this.PermanentProperties[i];if(this[_18]!=null){return false;}}return true;};window.ComponentArt_ItemLook_Loaded=true;}
