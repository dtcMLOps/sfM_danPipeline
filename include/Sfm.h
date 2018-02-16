//----------------------------------------------
//HEADERS
//----------------------------------------------

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/viz.hpp"
#include "opencv2/viz/vizcore.hpp"
#include "opencv2/viz/viz3d.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <math.h>

class StructFromMotion{

  cv::Mat_<cv::Vec3b> image1, image2;

  public:

  //----------------------------------------------
  //CONSTRUCTOR
  //----------------------------------------------
  StructFromMotion(){}
  StructFromMotion(cv::Mat& img1,cv::Mat& img2);

  //----------------------------------------------
  //PIPELINE FUNCTIONS
  //----------------------------------------------

  void recon( std::ifstream& file);

  int sizeTxtFile( std::ifstream& file);

  std::vector<cv::KeyPoint> obtenerKeypoints (cv::Mat& image);

  std::vector<cv::DMatch> obtenerMatches(cv::Mat& img1,cv::Mat& img2,
                                         std::vector<cv::KeyPoint>& keypoints1,
                                         std::vector<cv::KeyPoint>& keypoints2);

  cv::Mat imageMatching(cv::Mat& img1,std::vector<cv::KeyPoint>& keypoints1,
                        cv::Mat& img2, std::vector<cv::KeyPoint>& keypoints2,
                        std::vector<cv::DMatch>& matches);

  void matchingImShow(cv::Mat& matchImage);

  std::vector<cv::Point2f> keypoints2F(std::vector<cv::KeyPoint>& keypoints,std::vector<cv::DMatch>& matches);

  cv::Mat_<double> getCameraMatrix();

  cv::Mat_<double> findEssentialMatrix(std::vector<cv::Point2f>& points1,
                                       std::vector<cv::Point2f>& points2,cv::Mat_<double>& cameraMatrix);

  void cameraPose(std::vector<cv::Point2f>& points1,std::vector<cv::Point2f>& points2,
                  double& fx,double cx,double cy,cv::Mat& rot,cv::Mat& tra,
                  cv::Mat& inliers,cv::Mat_<double>& essentialMatrix );

  void projection(const cv::Mat& relativeRotationCam,const cv::Mat& relativeTranslaCam,
                  cv::Mat_<double>& projection1, cv::Mat_<double>& projection2);

  std::vector<cv::Point3d> triangulation(std::vector<cv::Point2f>& points1,
                                         std::vector<cv::Point2f>& points2,
                                         cv::Mat_<double>& projection1,
                                         cv::Mat_<double>& projection2,cv::Mat& inliers);

  void visualizerPointCloud(cv::Matx33d& cameraMatrix,cv::Mat& img1,
                            cv::Mat& img2,cv::Mat& cameraR,cv::Mat& cameraT,std::vector<cv::Point3d>& pointcloud);

  void setConstructor(cv::Mat& img1,cv::Mat& img2);

  //----------------------------------------------
  //TRIANGULATION FUNCTIONS
  //----------------------------------------------

  cv::Mat_<double> LinearLSTriangulation(cv::Point3d u,cv::Matx34d P,cv::Point3d u1,cv::Matx34d P1);

  cv::Mat_<double> IterativeLinearLSTriangulation(cv::Point3d u,cv::Matx34d P,cv::Point3d u1,cv::Matx34d P1);

  //----------------------------------------------
  //INVERSE MATRIX FUNCTION EIGEN
  //----------------------------------------------

  cv::Mat inverse(cv::Mat& matrix);

  double determinante(cv::Mat& relativeRotationCam);

  bool CheckCoherentRotation(cv::Mat_<double>& R);

};//Fin class


