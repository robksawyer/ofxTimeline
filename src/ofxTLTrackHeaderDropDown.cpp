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

#include "ofxTLTrackHeaderDropDown.h"
#include "ofxTimeline.h"

ofxTLTrackHeaderDropDown::ofxTLTrackHeaderDropDown()
{
    ofxTLTrackHeader::ofxTLTrackHeader();
    
//	track = NULL;
//	draggingSize = false;
//	hoveringFooter = false;
//	footerHeight = FOOTER_HEI

//    //trackName = new ofxDatGuiLabel("TRACK'S NAME");
//    //trackName->setLabel("TRACK NAME");
//
////    gui = new ofxDatGui();
////    gui->setWidth(150);
////    gui->setOpacity(0.0);
//    
//    trackNameToggle = new ofxDatGuiToggle("TEST TOGGLE",true);
//    trackNameToggle->setWidth(150);
//    trackOscAddress = new ofxDatGuiTextInput("OSC Addr :");
//    trackOscAddress->setWidth(250,90);

    trackDelay = new ofxDatGuiTextInput("Delay Ms :");
    trackDelay->setWidth(250,90);
//    guiComponents.push_back(trackDelay);

}

ofxTLTrackHeaderDropDown::~ofxTLTrackHeaderDropDown(){
	
}


float ofxTLTrackHeaderDropDown::getTrackDelay()
{
    return ofToFloat(trackDelay->getText());
}

void ofxTLTrackHeaderDropDown::setTrackDelay(float f)
{
    trackDelay->setText(ofToString(f));
}


//void ofxTLTrackHeader::enable(){
//	if(!isEnabled()){
//		nameField.setFont(timeline->getFont());
//		ofxTLTrack::enable();
//    	ofAddListener(nameField.textChanged, this, &ofxTLTrackHeader::textFieldEnter);
//	}
//}
//
//void ofxTLTrackHeader::disable(){
//	if(isEnabled()){
//		ofxTLTrack::disable();
//		nameField.disable();
//	    ofRemoveListener(nameField.textChanged, this, &ofxTLTrackHeader::textFieldEnter);
//	}
//}
//
//void ofxTLTrackHeader::setTrack(ofxTLTrack* newTrack){
//	track = newTrack;
//}
//
//ofxTLTrack* ofxTLTrackHeader::getTrack(){
//	return track;    
//}
//
//void ofxTLTrackHeader::textFieldEnter(string& newText){
//
//    if(newText == ""){
//        nameField.text = name;
//    }
//    else{
//        if(track != NULL){
//            track->setDisplayName(newText);
//        }
//    }
//	track->getTimeline()->dismissedModalContent();
//}
//
//string ofxTLTrackHeader::getDisplayName(){
//	if(track != NULL){
//		return track->getDisplayName();
//	}
//	return "";
//}
//
//void ofxTLTrackHeader::draw(){
//	ofRectangle trackRect = track->getDrawRect();
//
//	float footerStartY = trackRect.y + trackRect.height;
//	footerRect = ofRectangle(bounds.x, footerStartY, bounds.width, footerHeight);
//	if(footerRect.width != footerStripeWidth){
//		recalculateFooterStripes();
//	}
//	
//	ofPushStyle();
//	
//	if(track->hasFocus()){
//		ofFill();
//		ofSetColor(timeline->getColors().highlightColor, 50);
//		ofRect(bounds.x, bounds.y, bounds.width, bounds.height);
//	}
//
//	// TODO: set these somewhere else instead of setting it every frame here
//    // set name if it's empty and we're not editing
//    if(nameField.text != track->getDisplayName() && !nameField.getIsEnabled()){
//    	nameField.text = track->getDisplayName();   
//    }
//    
//	if(timeline->areHeadersEditable() && !nameField.getIsEnabled()){
//		nameField.enable();
//	}
//	
//	if(!timeline->areHeadersEditable() && nameField.getIsEnabled()){
//		nameField.disable();
//	}
//	
//    if(nameField.getIsEditing()){
//    	track->getTimeline()->presentedModalContent(this);
//    }
//    
//	
//    nameField.bounds.x = bounds.x;
//    nameField.bounds.y = bounds.y;
//	ofNoFill();
//	if(bounds.height == 0){
//		ofSetColor(getTimeline()->getColors().textColor, 100);
//	}
//	else{
//		ofSetColor(getTimeline()->getColors().textColor);
//	}
//
//	ofSetColor(track->getTimeline()->getColors().outlineColor);
//    ofFill();
//    ofSetColor(255,255,255,200);
//	ofRect(bounds);
//
//    ofSetColor(track->getTimeline()->getColors().textColor);
//    ofSetColor(0);
//    if(getTrack()->getDrawRect().height > 0 || bounds.height > 0){
//        nameField.draw();
//    }
//
//	//draw grippy lines on the footer draggable element
//	if(footerHeight > 0){
//		if(draggingSize){
//			footerStripes.setStrokeColor(track->getTimeline()->getColors().highlightColor);
//			footerStripes.draw(footerRect.x, footerRect.y);
//		}
//		else if(hoveringFooter){
//			footerStripes.setStrokeColor(track->getTimeline()->getColors().outlineColor);
//			footerStripes.draw(footerRect.x, footerRect.y);
//		}
//	}
//	ofPopStyle();
//    
//    // DATGUI
//    
//    ofSetColor(255);
//    //gui->setPosition(bounds.x,bounds.y);
//    trackNameToggle->draw();
//    trackOscAddress->draw();
//    //trackOscAddress->setPosition(bounds.x + gui->getWidth(),bounds.y);
//    
//}
//
//void ofxTLTrackHeader::recalculateFooterStripes(){
//	
//	if(footerHeight == 0){
//		return;
//	}
//	footerStripes.clear();
//	footerStripes.setStrokeWidth(1.0);
//
//	for(float l = 0; l < bounds.width; l+=footerHeight){
//		footerStripes.moveTo(l, footerHeight);
//		footerStripes.lineTo(l+footerHeight, 0);
//	}
//	
//	footerStripeWidth = footerRect.width;
//}
//
//void ofxTLTrackHeader::mousePressed(ofMouseEventArgs& args){
//	if(footerHeight > 0 && footerRect.inside(ofPoint(args.x,args.y))){
//		dragOffset = args.y - footerRect.y;
//		draggingSize = true;
//	}
//}
//
//void ofxTLTrackHeader::mouseMoved(ofMouseEventArgs& args){
//	hoveringFooter = footerRect.inside(args.x, args.y);
//}
//
//void ofxTLTrackHeader::mouseDragged(ofMouseEventArgs& args){
//	if(draggingSize){
//		ofRectangle trackRect = track->getDrawRect();
//		trackRect.height = MAX(0, args.y - trackRect.y - dragOffset);
//		track->setDrawRect(trackRect);		
//		recalculateFooter();		
//	}
//}
//
//void ofxTLTrackHeader::collapseTrack(){
//	ofRectangle trackRect = track->getDrawRect();
//	trackRect.height = 0;
//	track->setDrawRect(trackRect);
//	recalculateFooter();
//}
//
//void ofxTLTrackHeader::setFooterHeight(float height){
//	if(height != footerHeight){
//		footerHeight = height;
//		recalculateFooter();
//	}
//}
//
//void ofxTLTrackHeader::recalculateFooter(){
//	ofRectangle trackRect = track->getDrawRect();
//	float footerStartY = trackRect.y + trackRect.height;
//	footerRect = ofRectangle(bounds.x, footerStartY, bounds.width, footerHeight);
//	
//	ofEventArgs a;
//	ofNotifyEvent(track->events().viewWasResized, a);
//}
//
//void ofxTLTrackHeader::mouseReleased(ofMouseEventArgs& args){
//	draggingSize = false;
//}
//
//ofRectangle ofxTLTrackHeader::getFooterRect(){
//	return footerRect;
//}
//
//void ofxTLTrackHeader::update()
//{
//    trackNameToggle->setPosition(bounds.x,bounds.y);
//    trackNameToggle->setLabel(track->getDisplayName());
//
//    trackNameToggle->update();
//    
//    trackOscAddress->setPosition(trackNameToggle->getX()+150,bounds.y);
//    trackOscAddress->update();
//    
//    ofxTLTrack::update();
//}