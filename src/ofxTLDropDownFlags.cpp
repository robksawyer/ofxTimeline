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
            
            ofSetColor(timeline->getColors().backgroundColor);
            int textHeight = bounds.y + 10 + ( (20*i) % int(MAX(bounds.height-15, 15)));
            key->display = ofRectangle(MIN(screenX+3, bounds.getMaxX() - key->textField.bounds.width),
                                       textHeight-10, 180, 15);
            ofRect(key->display);
            
            ofSetColor(timeline->getColors().textColor);
            
            key->textField.bounds.x = key->display.x;
            key->textField.bounds.y = key->display.y;
            key->textField.draw();
            
            
            //DatGUI
            key->menu->setPosition(key->display.x,key->display.y);
            key->menu->draw();
            

        }
    }
    ofPopStyle();
}

//main function to get values out of the timeline, operates on the given value range
bool ofxTLDropDownFlags::mousePressed(ofMouseEventArgs& args, long millis){
    
    //if we aren't entering text and someone has the shift key held down don't let us go into modal
    //    if(!enteringText && ofGetModifierSelection()){
    //        return ofxTLBangs::mousePressed(args, millis);
    //    }
    
    clickedTextField = NULL;
    //look at each keyframe to see if a text field was clicked
    for(int i = 0; i < keyframes.size(); i++){
        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
        if(key->display.inside(args.x, args.y)){
            clickedTextField = key;
            break;
        }
    }
    
    //	cout << "text field? " << (clickedTextField == NULL ? "NULL" : clickedTextField->textField.text) << endl;
    //if so, select that text field and key and present modally
    //so that keyboard input all goes to the text field.
    //selection model is designed so that you can type into
    //mulitple fields at once
    if(clickedTextField != NULL)
    {
        cout << " a textfiled was pressed ... present MODAL !! " << endl;
        // !!!!!!!!!!!!!!!!!!!!!
        timeline->presentedModalContent(this);
        // !!!!!!!!!!!!!!!!!!!!!
        if(!ofGetModifierSelection())
        {
            cout << " no modifer key so unselectAll!! " << endl;

            timeline->unselectAll();
        }
        
        if(ofGetModifierSelection() && clickedTextField->textField.getIsEditing())
        {
            // is SHIFT and we where editing ... end editing !!
            clickedTextField->textField.endEditing();
        }
        else{
            cout << " text field BEGIN EDIT !! and select the keyframe as we're editing it !! " << endl;

            clickedTextField->textField.beginEditing();
            enteringText = true;
            //make sure this key is selected
            selectKeyframe(clickedTextField);
        }
        return false;
    }
    else{
        if(enteringText && !isHovering()){
            for(int i = 0; i < selectedKeyframes.size(); i++){
                ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.endEditing();
            }
            enteringText = false;
            // DIMISS MODAL CONTENT !! 
            timeline->dismissedModalContent();
            cout << " mouse Press :: dismissing MODAL # # #  !!! " << endl;

        }
    }
    
    if(!enteringText){
        //if we get all the way here we didn't click on a text field and we aren't
        //currently entering text so proceed as normal
        return ofxTLBangs::mousePressed(args, millis);
    }
    return false;
}

void ofxTLDropDownFlags::mouseDragged(ofMouseEventArgs& args, long millis){
    if(!enteringText){
        ofxTLBangs::mouseDragged(args, millis);
    }
}

//if we didn't click on a text field and we are entering txt
//take off the typing mode. Hitting enter will also do this
void ofxTLDropDownFlags::mouseReleased(ofMouseEventArgs& args, long millis){
    if(enteringText)
    {
        //if we clicked outside of the rect, definitely deslect everything
        if(clickedTextField == NULL && !ofGetModifierSelection()){
            for(int i = 0; i < selectedKeyframes.size(); i++)
            {
                ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.endEditing();
            }
            enteringText = false;
        }
        //otherwise check if still have a selection
        else{
            enteringText = false;
            for(int i = 0; i < selectedKeyframes.size(); i++){
                enteringText = enteringText || ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.getIsEditing();
            }
        }
        
        if(!enteringText){
            timeline->dismissedModalContent();
            timeline->flagTrackModified(this);
        }
    }
    else {
        ofxTLBangs::mouseReleased(args, millis);
    }
}

void ofxTLDropDownFlags::keyPressed(ofKeyEventArgs& args){
    
    if(enteringText){
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
    key->textField.setFont(timeline->getFont());
    return key;
}

void ofxTLDropDownFlags::unselectAll(){
    for(int i = 0; i < selectedKeyframes.size(); i++){
        ((ofxTLDropDownFlag*)selectedKeyframes[i])->textField.disable();
    }
    ofxTLKeyframes::unselectAll();
}

void ofxTLDropDownFlags::restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLDropDownFlag* triggerKey = (ofxTLDropDownFlag*)key;
    triggerKey->textField.text = xmlStore.getValue("flag", "");
}

void ofxTLDropDownFlags::storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLDropDownFlag* triggerKey = (ofxTLDropDownFlag*)key;
    xmlStore.addValue("flag", triggerKey->textField.text);
}

void ofxTLDropDownFlags::willDeleteKeyframe(ofxTLKeyframe* keyframe){
    ofxTLDropDownFlag* flag = (ofxTLDropDownFlag*)keyframe;
    if(flag->textField.getIsEditing()){
        timeline->dismissedModalContent();
        timeline->flagTrackModified(this);
    }
    flag->textField.disable();
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
    args.flag = ((ofxTLDropDownFlag*)key)->textField.text;
    ofNotifyEvent(events().bangFired, args);
}

string ofxTLDropDownFlags::getTrackType(){
    return "DropDownFlags";
}

void ofxTLDropDownFlags::addFlag(string key) {
    addFlagAtTime(key, timeline->getCurrentTimeMillis());
}

void ofxTLDropDownFlags::addFlagAtTime(string key, unsigned long long time){
    //	cout << "***ADDING FLAG WITH TIME " << time << endl;
    if(time > 2000000){
        cout << "***UNITITED VAR " << time << endl;
        return;
    }
    ofxTLKeyframe* keyFrame = newKeyframe();
    ofxTLDropDownFlag* flag = (ofxTLDropDownFlag*)keyFrame;
    setKeyframeTime(keyFrame, time);
    flag->textField.text = key;
    keyframes.push_back(keyFrame);
    updateKeyframeSort();
    timeline->flagTrackModified(this);
}

ofxTLDropDownFlag* ofxTLDropDownFlags::getFlagWithKey(string key){
    for(int i = 0; i < keyframes.size(); i++){
        ofxTLDropDownFlag* flag = (ofxTLDropDownFlag*)keyframes[i];
        if( flag->textField.text == key ){
            return flag;
        }
    }
    return NULL;
}

void ofxTLDropDownFlags::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "DropDownFlags got the event " << endl;
}

void ofxTLDropDownFlags::update()
{
    for(int i = keyframes.size()-1; i >= 0; i--)
    {
        ofxTLDropDownFlag* key = (ofxTLDropDownFlag*)keyframes[i];
        if(isKeyframeIsInBounds(key))
        {
            key->menu->update();
        }
    }
}


