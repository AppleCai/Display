#include "HMI.hpp"

void HMI::ROIhandler(ServerEx *serv)
{
    /* Add logo ROI */
    cv::Mat mylogo = cv::imread("./pic/logo.png");
    cv::Mat imgROIlogo = serv->Img(cv::Rect(0, 0, mylogo.cols, mylogo.rows));
    mylogo.copyTo(imgROIlogo, mylogo);

    std::string suffix = ".png";
    /* int to string */
    std::string res = std::to_string(serv->page);
    /* stuff zero on the right*/
    while (res.size() < 4)
    {
      res = "0" + res;
    }
    /* setting number ROI get each item in string */
    cv::Mat numthousand = cv::imread("./pic/" + res.substr(0, 1) + suffix);
    cv::Mat imgROInumthousand = serv->Img(cv::Rect(mylogo.cols + 10, 0, numthousand.cols, numthousand.rows));
    numthousand.copyTo(imgROInumthousand, numthousand);

    cv::Mat numhundred = cv::imread("./pic/" + res.substr(1, 1) + suffix);
    cv::Mat imgROInumhundred = serv->Img(cv::Rect(mylogo.cols + 30, 0, numhundred.cols, numhundred.rows));
    numhundred.copyTo(imgROInumhundred, numhundred);

    cv::Mat numtens = cv::imread("./pic/" + res.substr(2, 1) + suffix);
    cv::Mat imgROInumtens = serv->Img(cv::Rect(mylogo.cols + 50, 0, numtens.cols, numtens.rows));
    numtens.copyTo(imgROInumtens, numtens);

    cv::Mat numunits = cv::imread("./pic/" + res.substr(3, 1) + suffix);
    cv::Mat imgROInumunits = serv->Img(cv::Rect(mylogo.cols + 70, 0, numunits.cols, numunits.rows));
    numunits.copyTo(imgROInumunits, numunits);
}

void HMI::DisplayFrame(ServerEx *serv)
{
  if ((this->_showEn == TRUE) && (serv->revOK == TRUE))
  {
    ROIhandler(serv);
    /* show picture */
    cv::imshow("pic", serv->Img);
    cv::waitKey(1);
  }
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