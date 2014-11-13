#include "app.h"
#include "ofMain.h"

int main(){
    
    ofAppiPhoneWindow * window = new ofAppiPhoneWindow();
    
    window->enableDepthBuffer();
	
    ofSetupOpenGL(window,1024,768, OF_FULLSCREEN);
	
    ofRunApp(new app);
}