


#include<visp3/core/vpImageConvert.h>
#include<visp3/klt/vpKltOpencv.h>
#include<visp3/gui/vpDisplayOpenCV.h>
#include<visp3/io/vpVideoReader.h>






int main(int argc, const char **argv)
{

  try {

    bool opt_init_by_click = false;
   
    vpVideoReader reader;
    reader.setFileName("src.mpeg");
    vpImage<unsigned char> I;
    reader.acquire(I);

 // opencv code
    cv::Mat cvI;
    vpImageConvert::convert(I, cvI);
    vpDisplayOpenCV d(I, 0, 0, "Klt tracking");
    vpDisplay::display(I);
    vpDisplay::flush(I);
    vpKltOpencv tracker;
    tracker.setMaxFeatures(200);
    tracker.setWindowSize(10);
    tracker.setQuality(0.01);
    tracker.setMinDistance(15);
    tracker.setHarrisFreeParameter(0.04);
    tracker.setBlockSize(9);
    tracker.setUseHarris(1);
    tracker.setPyramidLevels(3);
    
    // Initialise the tracking
    
    if (opt_init_by_click) {
      vpMouseButton::vpMouseButtonType button = vpMouseButton::button1;
      std::vector<cv::Point2f> feature;	
      vpImagePoint ip;
      do {
        vpDisplay::displayText(I, 10, 10,
                               "Left click to select a point, right to start tracking",
                               vpColor::red);
        if (vpDisplay::getClick(I, ip, button, false)) {
          if (button == vpMouseButton::button1) {
            feature.push_back(cv::Point2f((float)ip.get_u(), (float)ip.get_v()));
            vpDisplay::displayCross(I, ip, 12, vpColor::green);
          }
        }
        
        vpDisplay::flush(I);
        vpTime::wait(20);
        
      } while(button != vpMouseButton::button3);
      tracker.initTracking(cvI, feature);
    }
    else {
      tracker.initTracking(cvI);
    }
    std::cout << "Tracker initialized with " << tracker.getNbFeatures() << " features" << std::endl;
    while ( ! reader.end() )
    {
      reader.acquire(I);
      vpDisplay::display(I);
      vpImageConvert::convert(I, cvI);
      if (opt_init_by_click && reader.getFrameIndex() == reader.getFirstFrameIndex() + 20) {
        vpMouseButton::vpMouseButtonType button = vpMouseButton::button1;
        std::vector<cv::Point2f> feature;
        vpImagePoint ip;
        do {
          vpDisplay::displayText(I, 10, 10,
                                 "Left click to select a point, right to start tracking",
                                 vpColor::red);
          if (vpDisplay::getClick(I, ip, button, false)) {
            if (button == vpMouseButton::button1) {
              feature.push_back(cv::Point2f((float)ip.get_u(), (float)ip.get_v()));
              vpDisplay::displayCross(I, ip, 12, vpColor::green);
            }
          }
          vpDisplay::flush(I);
          vpTime::wait(20);
        } while(button != vpMouseButton::button3);
        tracker.initTracking(cvI, feature);
      }
      tracker.track(cvI);
      tracker.display(I, vpColor::red);
      vpDisplay::flush(I);
    }
    vpDisplay::getClick(I);
    return 0;
  }
  catch(vpException &e) {
    std::cout << "Catch an exception: " << e << std::endl;
  }	 

return EXIT_SUCCESS;
}
