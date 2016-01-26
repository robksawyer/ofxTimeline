
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

#pragma once
#include "ofMain.h"
#include "ofxTLBangs.h"
#include "ofxDatGui.h"

//int DROP_WIDTH = 180;

class ofxTLDropDownFlag : public ofxTLKeyframe {
public:
    
    ofxTLDropDownFlag()
    {
        //theme = new ofxDatGuiThemeWireframe();
        //theme->layout.width = 120;
        
        vector<string> vecPresets;
        vecPresets.push_back("1 COLORITO");
        vecPresets.push_back("2 GORGORITO");
        vecPresets.push_back("3 XIRINGUITO");
        vecPresets.push_back("4 MENGUANTIO");
        vecPresets.push_back("5 MANOLITO");
        
        menu = new ofxDatGuiDropdown("Preset ?", vecPresets);
        menu->setWidth(140);
        menu->setOpacity(1.0);
        ofColor c1 = ofColor(0,0,0);
        ofColor c2 = ofColor(60,60,60);
        ofColor c3 = ofColor(80,80,80);
        ofColor c4 = ofColor(0,255,255);
        
        menu->setBackgroundColors(c1,c2,c3);
        //menu->setLabelColor(c4);

        //menu->expand();
        //menu->onDropdownEvent(this, &ofxTLDropDownFlags::onDropdownEvent);
        //menu->setTheme(theme);
    }
    
    vector<ofColor> colors;
    ofxDatGuiDropdown* menu;
    ofxDatGuiTheme* theme;
    

    
    
    
    //	virtual ~ofxTLFlag();
};



class ofxTLDropDownFlags : public ofxTLBangs {
public:
    ofxTLDropDownFlags();
    
    virtual void draw();
    virtual void update();
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    virtual void mouseMoved(ofMouseEventArgs& args, long millis);
    virtual bool mousePressed(ofMouseEventArgs& args, long millis);
    virtual void mouseDragged(ofMouseEventArgs& args, long millis);
    virtual void mouseReleased(ofMouseEventArgs& args, long millis);
    
    virtual void keyPressed(ofKeyEventArgs& args);
    virtual void unselectAll();
    
    virtual string getTrackType();
    
    virtual void addFlag(string key);
    virtual void addFlagAtTime(string key, unsigned long long time);
    virtual ofxTLDropDownFlag* getFlagWithKey(string key);
    
    //datGui related
    void collapseAllFlags();
    int isAnyOptionInFocus(ofxTLDropDownFlag* f);
    int isAnyDropDownInFocus();
    
    // to do : to work out the mouse interaction (now is dirty!)
    int aChildrenIsFocused;
    int whichIsInFocus;

protected:
    
    virtual ofxTLKeyframe* newKeyframe();
    virtual void restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);
    virtual void storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);
    virtual void bangFired(ofxTLKeyframe* key);
    virtual void willDeleteKeyframe(ofxTLKeyframe* keyframe);
    
    //only set per mousedown/mouseup cycle
    ofxTLDropDownFlag* clickedTextField;
    bool enteringText;
    
    vector<ofColor> colors;
    ofxDatGuiDropdown* menu;

    
};