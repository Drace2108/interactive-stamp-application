# interactive-stamp-application

1.	Extract the flowers from the image. <br>
I have applied Otsu thresholding to extract flowers from the image. Since the flower has relatively more red colors the thresholding were applied to bgr[2] which is red channel. After merging bfr to result we get flower with black background. After that I converted BGR (Blue, Green, Red) to BGRA (Blue, Green, Red, Alpha) where alpha represents pixel transparency. I set black pixles to transparent pixels to show flower only.  <br>
    im.load("flower.jpg");<br>
    mat = toCv(im);<br>
    
    //apply otsu tresholding<br>
    Mat result;<br>
    Mat mask;<br>
    vector<Mat> bgr;<br>
    split(mat, bgr);<br>
    threshold(bgr[2], mask, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);<br>
    bitwise_and(bgr[0], mask, bgr[0]);<br>
    bitwise_and(bgr[1], mask, bgr[1]);<br>
    bitwise_and(bgr[2], mask, bgr[2]);<br>
    merge(bgr, result);<br>
    //make black background transparent<br>
    cvtColor(result, resultBGRA, COLOR_BGR2BGRA);<br>
    for(int y = 0; y < resultBGRA.rows; y++) {<br>
        for(int x = 0; x < resultBGRA.cols; x++) {<br>
            Vec4b & pixel = resultBGRA.at<Vec4b>(y, x);<br>
            if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) {<br>
                pixel[3] = 0;<br>
            }
        }
    }<br>
2.	The extracted content follows the mouse position in the program window.<br>
Inside mouseMoved function I change global variables posY and posX to the cursor position. Then I drew the matrix of the flower and put the cursor in the centre. Before that I made I created the copy of matrix and turned parts beyond the image area to transparent. So extracted flower is only visible within the original image area.<br>
    Mat resultBGRAcopy = resultBGRA.clone();<br>
    for(int y = 0; y < resultBGRA.rows; y++) {<br>
        for(int x = 0; x < resultBGRA.cols; x++) {<br>
            Vec4b & pixel = resultBGRAcopy.at<Vec4b>(y, x);<br>
            if(posX-(im.getWidth()/2)+x >= im.getWidth() || posY-(im.getHeight()/2)+y >= im.getHeight()) {<br>
                pixel[3] = 0;<br>
            }
        }
    }<br>
    drawMat(resultBGRAcopy, posX-(im.getWidth()/2), posY-(im.getHeight()/2));<br>
3.	When you click the mouse, the program creates a copy of the extracted content on the image.<br>
In mousePressed I set pressed variable to true and in mouseReleased its false. When pressed is true it pushes current copy of flower matrix (which might be changed to fit into the original image area) and points into vectors. After that I traversed through the vectors and draw matrices stored in the matrices vector on position hold in points vector.<br>
    if (pressed){<br>
        matrices.push_back(resultBGRAcopy);<br>
        points.push_back(ofPoint(posX, posY));<br>
    }<br>
    
    for (int i = 0; i < points.size(); i++){<br>
        drawMat(matrices[i], points[i].x-(im.getWidth()/2), points[i].y-(im.getHeight()/2))<br>
}<br>
