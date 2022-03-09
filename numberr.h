#ifndef NUMBERR_H
#define NUMBERR_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct numberr
{
  numberr();
  numberr(double value);
  numberr(double value, double error);
  //~numberr();
  
  double v;
  double e;
  
  numberr operator+ (numberr x);
  numberr operator- (numberr x);
  numberr operator* (numberr x);
  numberr operator/ (numberr x);
  
  numberr topow(numberr x);
  
  void print();
  void to_file(string name);
  void to_file(string name, string einheit);
  void to_file(string name, string einheit, string text);
};
 // erray topow(erray x);                        //undefiniert


struct erray
{
  erray(int length);
  erray(string name); 
  
  int len;
  enum {N=5000};
  double v[N];
  double e[N];
  
  erray operator+ (numberr x); 
  erray operator- (numberr x); 
  erray operator* (numberr x);     
  erray operator/ (numberr x);   
  
  erray operator+ (erray x);
  erray operator- (erray x); 
  erray operator* (erray x);
  erray operator/ (erray x);
  
  erray topow(numberr x);
  erray topow(erray x);
  numberr mean();
  
  void print(); 
  void to_file(string name);
  void to_file(string name, string einheit);
  void to_file(string name, string einheit, string text);
  void to_tablerow(string name);
  
};

struct erray2D
{
  erray2D(int length1, int length2);
  erray2D(string name); 
  
  int len1, len2;
  enum {N=50};
  double v[N][N];
  double e[N][N];
  
  //erray2D operator+ (numberr x); 
  //erray2D operator- (numberr x); 
  //erray2D operator* (numberr x);     
  //erray2D operator/ (numberr x);   
  
  //erray2D operator+ (erray x);
  //erray2D operator- (erray x); 
  //erray2D operator* (erray x);
  //erray2D operator/ (erray x);
  
  //erray2D operator+ (erray2D x);
  //erray2D operator- (erray2D x); 
  //erray2D operator* (erray2D x);
  //erray2D operator/ (erray2D x);
    
  //erray2D topow(numberr x);
  //erray2D topow(erray x);
  //erray2D topow(erray2D x);
  erray mean();
  
  void print(); 
  void to_file(string name);
  void to_file(string name, string text);
};



#endif //NUMBERR_H
