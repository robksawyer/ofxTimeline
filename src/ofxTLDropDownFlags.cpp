/**
 * ofxTimeline
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ofxTLDropDownFlags.h"
#include "ofxTimeline.h"
#include "ofxHotKeys.h"

//flagssss
ofxTLDropDownFlags::ofxTLDropDownFlags() {
    enteringText = false;
    clickedTextField = NULL;

}

void ofxTLDropDownFlags::draw(){

//    if(timeline->isModal())
//    {
//        ofSetColor(255,0,0);
//        ofCircle(0,0,50);
//    }
//    else
//    {
//        ofSetColor(255);
//        ofCircle(0,0,50);
//    }
    
    if(bounds.height < 2){
        return;
    }
    
    ofPushStyle();
    
    ofxTLBangs::draw();
    
    ofFill();
    ofSetLineWidth(5);
    for(int i = keyframes.size()-1; i >= 0; i--){
        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
        if(isKeyframeIsInBounds(key)){
            int screenX = millisToScreenX(key->time);
            int textHeight = bounds.y + 10 + ( (20*i) % int(MAX(bounds.height-15, 15)));
            
//            ofSetColor(timeline->getColors().backgroundColor);
//            key->display = ofRectangle(MIN(screenX+3, bounds.getMaxX() - key->textField.bounds.width),
//                                       textHeight-10, 180, 30);
//            ofRect(key->display);
//            
//            ofSetColor(timeline->getColors().textColor);
            
            int x = MIN(screenX+3, bounds.getMaxX());// - key->textField.bounds.width);
            int y = textHeight - 10;

            //key->textField.draw();
            
            
            //DatGUI
            key->menu->setPosition(x,y);
            key->menu->draw();
            

        }
    }
    ofPopStyle();
}

void ofxTLDropDownFlags::mouseMoved(ofMouseEventArgs& args, long millis)
{
    
}


//main function to get values out of the timeline, operates on the given value range
bool ofxTLDropDownFlags::mousePressed(ofMouseEventArgs& args, long millis)
{
    
    ofxTLDropDownFlag* key = NULL;
    
    if(active)
    {
        /////////////////
        // GET STATE
        /////////////////
        // IS ANY DROPDOWIN IN FOCUS ? (the main button) ?
        /////////////////
        whichIsInFocus = -1;
        whichIsInFocus = isAnyDropDownInFocus();
        
        /////////////////
        // IS ANY OPTION IN THE DROPDOWN IN FOCUS
        /////////////////
        aChildrenIsFocused = -1;
        int childrenInFocus = -2;
        int whichOptionWasSelected = -3;
//        cout << "how many keys ? " << keyframes.size() << endl;
        for(int i = 0; i < keyframes.size(); i++)
        {
            
            key = (ofxTLDropDownFlag*)keyframes[i];
            
            childrenInFocus = isAnyOptionInFocus(key);
//            cout << "looking for a chidrenInFocus ... " << childrenInFocus << " and i is ? "<< i << endl;
            
            // false ! ..> // 0 is the top button of the dropdown ... do not consider it .. it's the father not a children.
            if (childrenInFocus >= 0 )
            {
                whichOptionWasSelected = childrenInFocus;
                aChildrenIsFocused = i;
//                cout << "assigned aChildrenIsFocused to " << i << endl;
            }
        }
        
//        cout << "achildrenIsFocused ??????? " << aChildrenIsFocused <<endl;
        // if clicked on the dropdown button ...
        if(whichIsInFocus!=-1)
        {
            key = (ofxTLDropDownFlag*)keyframes[whichIsInFocus];
            
            if(key->menu->getIsExpanded())
            {
                // the dropdown is expanded yet .... so we might dismiss modal
//                cout << " we are expanded ... dropdown should colapse ? DISMISSED MODAL !!  " << whichIsInFocus << " _ A Children in Focus ? : " << aChildrenIsFocused << endl;
                //key->menu->collapse();
                timeline->dismissedModalContent();
//                timeline->collectStateBuffers();
//                getXMLStringForKeyframes(key);
            }
            else
            {
                // the dropdown is already expanded .... so we present modal
//                cout << "we're collapsed ... some dropdown is in focus so ... PRESENT MODAL" << endl;
                timeline->presentedModalContent(this);


            }
            
        }
        
        if(aChildrenIsFocused!=-1)
        {
            key = (ofxTLDropDownFlag*)keyframes[aChildrenIsFocused];
            // the gui might be expanded ...
            if(key->menu->getIsExpanded())
            {
//                cout << "we clicked over a dropdown option .... so we need to collapse . aChildrenIsInFocus : " << aChildrenIsFocused  << endl;
                //key->menu->collapse();
                timeline->dismissedModalContent();
                key->menu->select(whichOptionWasSelected);
            }
        }
    
        if ( ( whichIsInFocus==-1) && (aChildrenIsFocused==-1) )
        {
             if(!timeline->isModal())
             {
                 ofxTLBangs::mousePressed(args, millis);
             }
        }
    }// if active
        
}// end
    
    
    //if we aren't entering text and someone has the shift key held down don't let us go into modal
    //    if(!enteringText && ofGetModifierSelection()){
    //        return ofxTLBangs::mousePressed(args, millis);
    //    }
    //
    //    clickedTextField = NULL;
    //    //look at each keyframe to see if a text field was clicked
    //    for(int i = 0; i < keyframes.size(); i++)
    //    {
    //        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
    //
    //        //try to know if you're clicking an option of the DropDown ...
    //        bool dropDownIsInFocus = key->menu->getFocused();
    //        if (dropDownIsInFocus) cout << "DropDownIsInFocus" << endl;
    //
    //
    //        if(key->display.inside(args.x, args.y)){
    //            clickedTextField = key;
    //            break;
    //        }
    //
    //    }

    //	cout << "text field? " << (clickedTextField == NULL ? "NULL" : clickedTextField->textField.text) << endl;
    //if so, select that text field and key and present modally
    //so that keyboard input all goes to the text field.
    //selection model is designed so that you can type into
    //mulitple fields at once
    
    //    if(clickedTextField != NULL)
    //    {
    //        cout << " PRESENT MODAL" << endl;
    //        timeline->presentedModalContent(this);
    //        enteringText=true;
    
    
    
    //        cout << " a textfiled was pressed ... present MODAL !! " << endl;
    //        // !!!!!!!!!!!!!!!!!!!!!
    //        timeline->presentedModalContent(this);
    //        // !!!!!!!!!!!!!!!!!!!!!
    //        if(!ofGetModifierSelection())
    //        {
    //            cout << " no modifer key so unselectAll!! " << endl;
    //
    //            timeline->unselectAll();
    //        }
    //
    //        if(ofGetModifierSelection() && clickedTextField->textField.getIsEditing())
    //        {
    //            // is SHIFT and we where editing ... end editing !!
    //            clickedTextField->textField.endEditing();
    //        }
    //        else{
    //            cout << " text field BEGIN EDIT !! and select the keyframe as we're editing it !! " << endl;
    //
    //            clickedTextField->textField.beginEditing();
    //            enteringText = true;
    //            //make sure this key is selected
    //            selectKeyframe(clickedTextField);
    //        }
    //        return false;
    //    }
    
    
    //        if(enteringText && !isHovering())
    //        {
    //            for(int i = 0; i < selectedKeyframes.size(); i++){
    //                ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.endEditing();
    //            }
    //            enteringText = false;
    //            // DIMISS MODAL CONTENT !!
    //            timeline->dismissedModalContent();
    //            cout << " mouse Press :: dismissing MODAL # # #  !!! " << endl;
    //
    //        }
    
    
    //    if(!enteringText)
    //    {
    //        //if we get all the way here we didn't click on a text field and we aren't
    //        //currently entering text so proceed as normal
    //        return ofxTLBangs::mousePressed(args, millis);
    //    }
    //    return false;



void ofxTLDropDownFlags::mouseDragged(ofMouseEventArgs& args, long millis){
    if(!enteringText){
        ofxTLBangs::mouseDragged(args, millis);
    }
    

}

//if we didn't click on a text field and we are entering txt
//take off the typing mode. Hitting enter will also do this
void ofxTLDropDownFlags::mouseReleased(ofMouseEventArgs& args, long millis){

    if(false)
//        if(enteringText)
    {
        //if we clicked outside of the rect, definitely deslect everything
        if(clickedTextField == NULL && !ofGetModifierSelection()){
            for(int i = 0; i < selectedKeyframes.size(); i++)
            {
                //((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.endEditing();
            }
            enteringText = false;
        }
        //otherwise check if still have a selection
        else{
            //enteringText = false;
            //for(int i = 0; i < selectedKeyframes.size(); i++)
            {
                //enteringText = enteringText || ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.getIsEditing();
            }
        }
        
        if(!enteringText){
            timeline->dismissedModalContent();
            timeline->flagTrackModified(this);
        }
    }
    else {
        
//        if(aChildrenIsFocused!=-1)
//        {
//            save();
//            cout << "track saved" << endl;
//        }
        
        ofxTLBangs::mouseReleased(args, millis);
    }
}

void ofxTLDropDownFlags::keyPressed(ofKeyEventArgs& args){
    
//    if(enteringText){
        if(false){
        //enter key submits the values
        //This could be done be responding to the event from the text field itself...
        if(args.key == OF_KEY_RETURN){
            enteringText = false;
            timeline->dismissedModalContent();
            timeline->flagTrackModified(this);
        }
    }
    //normal behavior for nudging and deleting and stuff
    else{
        ofxTLBangs::keyPressed(args);
    }
}

ofxTLKeyframe* ofxTLDropDownFlags::newKeyframe(){
    ofxTLDropDownFlag* key = new ofxTLDropDownFlag();
    return key;
}

void ofxTLDropDownFlags::unselectAll(){
//    for(int i = 0; i < selectedKeyframes.size(); i++){
//        ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.disable();
//    }
    ofxTLKeyframes::unselectAll();
}

void ofxTLDropDownFlags::restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLDropDownFlag* triggerKey = (ofxTLDropDownFlag*)key;
    triggerKey->menu->select(xmlStore.getValue("option",0));
}

void ofxTLDropDownFlags::storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLDropDownFlag* triggerKey = (ofxTLDropDownFlag*)key;
    //xmlStore.addValue("flag", triggerKey->textField.text);
    int selInd =  triggerKey->menu->getSelectedIndex();
    xmlStore.addValue("option",selInd);
}

void ofxTLDropDownFlags::willDeleteKeyframe(ofxTLKeyframe* keyframe){
    ofxTLDropDownFlag* flag = (ofxTLDropDownFlag*)keyframe;
//    if(flag->textField.getIsEditing()){
//        timeline->dismissedModalContent();
//        timeline->flagTrackModified(this);
//    }
//    flag->textField.disable();
}

void ofxTLDropDownFlags::bangFired(ofxTLKeyframe* key){
    ofxTLBangEventArgs args;
    args.sender = timeline;
    args.track = this;
    //play solo change
    //    args.currentMillis = timeline->getCurrentTimeMillis();
    args.currentMillis = currentTrackTime();
    args.currentPercent = timeline->getPercentComplete();
    args.currentFrame = timeline->getCurrentFrame();
    args.currentTime = timeline->getCurrentTime();
    
    // in flags was :
    //args.flag = ((ofxTLFlag*)key)->textField.text;

    //args.flag = ((ofxTLDropDownFlag*)key)->menu->getSelectedIndex();
    
    string selectedLabel;
    ofxDatGuiDropdown* fl = ((ofxTLDropDownFlag*)key)->menu;
    selectedLabel = fl->getSelected()->getLabel();
    args.flag = selectedLabel;
    
    
    ofNotifyEvent(events().bangFired, args);
    
}

string ofxTLDropDownFlags::getTrackType(){
    return "DropDownFlags";
}

void ofxTLDropDownFlags::addFlag(string key) {
//    addFlagAtTime(key, timeline->getCurrentTimeMillis());
}

void ofxTLDropDownFlags::addFlagAtTime(string key, unsigned long long time){
/*
    //	cout << "***ADDING FLAG WITH TIME " << time << endl;
    if(time > 2000000){
        cout << "***UNITITED VAR " << time << endl;
        return;
    }
    ofxTLKeyframe* keyFrame = newKeyframe();
    ofxTLDropDownFlag* flag = (ofxTLDropDownFlag*)keyFrame;
    setKeyframeTime(keyFrame, time);
//    flag->textField.text = key;
    keyframes.push_back(keyFrame);
    updateKeyframeSort();
    timeline->flagTrackModified(this);
*/
 }

ofxTLDropDownFlag* ofxTLDropDownFlags::getFlagWithKey(string key){
//    for(int i = 0; i < keyframes.size(); i++){
//        ofxTLDropDownFlag* flag = (ofxTLDropDownFlag*)keyframes[i];
////        if( flag->textField.text == key ){
////            return flag;
////        }
//    }
//    return NULL;
}

void ofxTLDropDownFlags::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "DropDownFlags got the event " << endl;
}

void ofxTLDropDownFlags::update()
{
    ofxTLBangs::update();
    
//    if (enteringText) cout << "TLDropDown :: Editing Text : " << ofGetElapsedTimef() << endl;
    for(int i = keyframes.size()-1; i >= 0; i--)
    {
        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
        if(isKeyframeIsInBounds(key))
        {
            key->menu->update(true);
            /*
            if(timeline->isModal())
            {
                key->menu->update(true);
            }
            else
            {
                key->menu->update(false);
            }
             */
        }
    }
}



void ofxTLDropDownFlags::collapseAllFlags()
{
    for(int i = 0; i < keyframes.size(); i++)
    {
        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
        key->menu->collapse();
    }
}


int ofxTLDropDownFlags::isAnyOptionInFocus(ofxTLDropDownFlag* key)
{
    int res = -11;
    
    //try to know if you're clicking an option of the DropDown ...
    bool dropDownIsInFocus = key->menu->getFocused();
    //if (dropDownIsInFocus) cout << "Menu DropDown Is In Focus ?? here ??" << ofGetElapsedTimef() <<endl;
    
    for(int i=0;i<key->menu->children.size();i++)
    {
        bool childrenFocus = key->menu->getChildAt(i)->hitTest(ofPoint(ofGetMouseX(), ofGetMouseY()));
        if (childrenFocus)
        {
            res = i;
            return res;
        }
        
    }
    //cout << "res = " << res << endl;
    return res;
}

int ofxTLDropDownFlags::isAnyDropDownInFocus()
{
    int result=-1;

    for(int i = 0; i < keyframes.size(); i++)
    {
        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
        bool dropDownIsInFocus = key->menu->hitTest(ofPoint(ofGetMouseX(), ofGetMouseY()));
        
        if (dropDownIsInFocus)
        {
            //cout << "Menu DropDown Is In Focus" << ofGetElapsedTimef() <<endl;
            result = i;
        }

    }
    
    return result;
}