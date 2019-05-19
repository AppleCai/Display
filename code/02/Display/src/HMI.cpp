#include "head.hpp"
void HMI::DisplayFrame(ServerEx *serv)
{
  if ((this->_showEn == TRUE)&&(serv->revOK == TRUE))
  {
    //cout<<"DisplayFrame vec size="<<serv->_myRecv->vec.size()<<endl;
    //cv::Mat img_decode = cv::imdecode(serv->_myRecv->vec, CV_LOAD_IMAGE_COLOR);
    //serv->_myRecv->vec.clear();
    //std::vector<uchar>(serv->_myRecv->vec).swap(serv->_myRecv->vec);
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