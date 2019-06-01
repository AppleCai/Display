#include "HMI.hpp"

void HMI::ROIhandler(cv::Mat &img,int page)
{
    /* Add logo ROI */
    cv::Mat mylogo = cv::imread("./pic/logo.png");
    cv::Mat imgROIlogo = img(cv::Rect(0, 0, mylogo.cols, mylogo.rows));
    mylogo.copyTo(imgROIlogo, mylogo);

    std::string suffix = ".png";
    /* int to string */
    std::string res = std::to_string(page);
    /* stuff zero on the right*/
    while (res.size() < 4)
    {
      res = "0" + res;
    }
    /* setting number ROI get each item in string */
    cv::Mat numthousand = cv::imread("./pic/" + res.substr(0, 1) + suffix);
    cv::Mat imgROInumthousand = img(cv::Rect(mylogo.cols + 10, 0, numthousand.cols, numthousand.rows));
    numthousand.copyTo(imgROInumthousand, numthousand);

    cv::Mat numhundred = cv::imread("./pic/" + res.substr(1, 1) + suffix);
    cv::Mat imgROInumhundred = img(cv::Rect(mylogo.cols + 30, 0, numhundred.cols, numhundred.rows));
    numhundred.copyTo(imgROInumhundred, numhundred);

    cv::Mat numtens = cv::imread("./pic/" + res.substr(2, 1) + suffix);
    cv::Mat imgROInumtens = img(cv::Rect(mylogo.cols + 50, 0, numtens.cols, numtens.rows));
    numtens.copyTo(imgROInumtens, numtens);

    cv::Mat numunits = cv::imread("./pic/" + res.substr(3, 1) + suffix);
    cv::Mat imgROInumunits = img(cv::Rect(mylogo.cols + 70, 0, numunits.cols, numunits.rows));
    numunits.copyTo(imgROInumunits, numunits);
}

void HMI::DisplayFrame(cv::Mat &img,int page,int save)
{
  //if ((this->_showEn == TRUE) && (serv->revOK == TRUE))

    ROIhandler(img,page);
    /* show picture */
    cv::imshow("pic", img);
    if (TRUE==save)
    {
      cv::imwrite("now.jpg",img);
      std::cout<<"save success!"<<std::endl;
    }
    cv::waitKey(1);

}
HMI::HMI(display *disp)
{
  disp->_myHMI = this;
  _showEn = TRUE;
}
void HMI::SetShowEn(bool cmd)
{
  _showEn = cmd;
}