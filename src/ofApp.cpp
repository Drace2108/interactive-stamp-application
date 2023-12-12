#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup(){
    im.load("flower.jpg");
    mat = toCv(im);
    
    //apply otsu tresholding
    Mat result;
    Mat mask;
    vector<Mat> bgr;
    split(mat, bgr);
    threshold(bgr[2], mask, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    bitwise_and(bgr[0], mask, bgr[0]);
    bitwise_and(bgr[1], mask, bgr[1]);
    bitwise_and(bgr[2], mask, bgr[2]);
    merge(bgr, result);
    
    //make black background transparent
    cvtColor(result, resultBGRA, COLOR_BGR2BGRA);
    for(int y = 0; y < resultBGRA.rows; y++) {
        for(int x = 0; x < resultBGRA.cols; x++) {
            Vec4b & pixel = resultBGRA.at<Vec4b>(y, x);
            if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) {
                pixel[3] = 0;
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawMat(mat, 0, 0);
    
    //create copy of flower with invisible parts beyond the original image area
    Mat resultBGRAcopy = resultBGRA.clone();
    for(int y = 0; y < resultBGRA.rows; y++) {
        for(int x = 0; x < resultBGRA.cols; x++) {
            Vec4b & pixel = resultBGRAcopy.at<Vec4b>(y, x);
            if(posX-(im.getWidth()/2)+x >= im.getWidth() || posY-(im.getHeight()/2)+y >= im.getHeight()) {
                pixel[3] = 0;
            }
        }
    }
    
    //draw flower on the cursor
    drawMat(resultBGRAcopy, posX-(im.getWidth()/2), posY-(im.getHeight()/2));
    
    //when clicked it stores the position and matrix
    if (pressed){
        matrices.push_back(resultBGRAcopy);
        points.push_back(ofPoint(posX, posY));
    }
    
    //draw clicked flowers
    for (int i = 0; i < points.size(); i++){
        drawMat(matrices[i], points[i].x-(im.getWidth()/2), points[i].y-(im.getHeight()/2));
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    posX = x;
    posY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    pressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
