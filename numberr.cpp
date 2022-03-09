#include <cmath>
#include <math.h>
#include <iostream>
#include <fstream>
#include "numberr.h"
#include <string>
using namespace std;

//Konstruktoren////////////////////////////////////////////////////////////////////////////////
//Einzelwerte
numberr::numberr ()
{//Default 
  //v = 0;
  //e = 0;
}

numberr::numberr (double value, double error)
{//Wert und Fehler
  v = value;
  e = error;
}

numberr::numberr (double value)
{//Fehlerlose Größen
  v = value;
  e = 0;
}

//Konstruktoren////////////////////////////////////////////////////////////////////////////////
//Felder
erray::erray (int length)
{//Leerer array
  len = length;
  for (int i=0; i<length; i++)
    {
    v[i] = 0;
    e[i] = 0;
    };
}

erray::erray (string name)
{//Weise dem array die Werte aus "name.csv" zu
  name = name + ".csv";
  
  string value, error;
  double consterror;
  int iter = 0; //iterator for the erray to place the values to the right spot
  ifstream data(name);
  bool one = false;
  bool zero = false;
  
  //First look for the first line whether an error is given:
  getline (data, value);
  if (value.find(",") == -1) {
    v[iter] = atof(value.c_str());
    e[iter] = 0;
    zero = true;
    cout << "Keine Fehler gegeben, setze Werte auf 0." << endl;
  } else {
    int komma = value.find(",");
    error = value;
    value.erase(komma,value.length());
    error.erase(0,komma + 1);
    v[iter] = atof(value.c_str());
    e[iter] = atof(error.c_str());
  }
  iter++;
  
  //Now the second line
  getline (data, value);
  if (zero) {
    v[iter] = atof(value.c_str());
    e[iter] = 0;
  } else if (value.find(",") == -1) {
    v[iter] = atof(value.c_str());
    e[iter] = atof(error.c_str());
    one = true;
    cout << "Nur ein Fehler gegeben, weise diesen allen Werten im Array zu." << endl;
  } else {
    int komma = value.find(",");
    error = value;
    value.erase(komma,value.length());
    error.erase(0,komma + 1);
    v[iter] = atof(value.c_str());
    e[iter] = atof(error.c_str());
    cout << "Fehler für Einzelwerte gegeben." << endl;
  }
  iter++;
  
//Jetzt entsprechend demnach wie viele Fehler gegeben sind über den Rest:  
  if (zero) {
    while (getline (data, value)) {
      v[iter] = atof(value.c_str());
      e[iter] = 0;
      iter++;
    }
  } else if (one) {
    while (getline (data, value)) {
      v[iter] = atof(value.c_str());
      e[iter] = atof(error.c_str());
      iter++;
    }
  } else {
    while (getline (data, value)) {
      int komma = value.find(",");
      error = value;
      value.erase(komma,value.length());
      error.erase(0,komma + 1);
      v[iter] = atof(value.c_str());
      e[iter] = atof(error.c_str());
      iter++;
    }
  }
  data.close();
  len = iter;
  
}

//Konstruktoren////////////////////////////////////////////////////////////////////////////////
//2DFelder
erray2D::erray2D (int length1, int length2)
{//Leerer array
  len1 = length1; len2 = length2;
  for (int i=0; i<length1; i++) {
    for (int j=0; j<length2; j++) {
      v[i][j] = 0;
      e[i][j] = 0;
    }
  };
}


erray2D::erray2D (string name)
{//Weise dem array die Werte aus "name.csv" zu
  name = name + ".csv";
  
  string value, line;
  int iter1 = 0; int iter2 = 0; //iterator for the erray to place the values to the right spot
  ifstream data(name);
  
  getline (data, line);
  while (line.find(",") != -1) {
    int komma = line.find(",");
    value = line;
    value.erase(komma,value.length());
    v[iter1][iter2] = atof(value.c_str());
    line.erase(0,komma + 1);
    iter2++;
  }
  v[iter1][iter2] = atof(line.c_str());
  
  iter1++;
  len2 = iter2 + 1;
  
  while (getline (data, line)) {
    if (line.find(",") != -1) {
      iter2 = 0;
      while (line.find(",") != -1) {
        int komma = line.find(",");
        value = line;
        value.erase(komma,line.length());
        v[iter1][iter2] = atof(value.c_str());
        line.erase(0,komma + 1);
        iter2++;
      }
      v[iter1][iter2] = atof(line.c_str());
      iter1++;
    } else {
      len1 = iter1;
      cout << line << endl;
      break;
    }
  };
  
  getline (data, line);
  if (line.find(",") == -1) {
    if (atof(line.c_str()) == 0) {
      cout << "Keine Fehler gegeben." << endl;
    } else {
      cout << "Nur ein Fehler gegeben weise diesen allen Werten zu." << endl;
    };
    for (int i=0; i<len1; i++) {
      for (int j=0; j<len2; j++) {
        e[i][j] = atof(line.c_str());
      }
    }
  } else {
    cout << "Alle Fehler gegeben, weise diese einzeln zu." << endl;
    iter1 = 0; iter2 = 0;
    while (getline (data, line)) {
      while (line.find(",") != -1) {
        int komma = line.find(",");
        value = line;
        value.erase(komma,line.length());
        e[iter1][iter2] = atof(value.c_str());
        line.erase(0,komma + 1);
        iter2++;
      };
      e[iter1][iter2] = atof(line.c_str());
      iter1++;
    }
  }
}




///////////////////////////////////////////////////////////////////////////////////////////////
//Operatoren und Funktionen
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//Operatoren und Funktionen
//Operatoren für Einzelwerte
numberr numberr::operator+ (numberr x)
{
  return numberr(v + x.v, sqrt(e*e + x.e*x.e));
}

numberr numberr::operator- (numberr x)
{
  return numberr(v - x.v, sqrt(e*e + x.e*x.e));
}

numberr numberr::operator* (numberr x)
{
  return numberr(v * x.v, v * x.v*sqrt(e/v*e/v + x.e/x.v*x.e/x.v));
}

numberr numberr::operator/ (numberr x)
{
  return numberr(v / x.v, v / x.v*sqrt(e/v*e/v + x.e/x.v*x.e/x.v));
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Funktionen für Mittelwerte und Potenzieren
//Für Numberrs
numberr numberr::topow (numberr x)
{
  return numberr(pow(v, x.v), sqrt((x.v*pow(v, x.v-1)*e)*(x.v*pow(v, x.v-1)*e) + (pow(v,x.v)*log(v)*x.e)*(pow(v,x.v)*log(v)*x.e)));
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Operatoren
//Für 1D Errays
//Feld und Wert
erray erray::operator+ (numberr x)
{
  erray ergebnis(len);
  for (int iter = 0; iter < len; iter++) {
    ergebnis.v[iter] = v[iter] + x.v;
    ergebnis.e[iter] = sqrt(e[iter]*e[iter] + x.e*x.e);
  };
  return ergebnis;
}

erray erray::operator- (numberr x)
{
  erray ergebnis(len);
  for (int iter = 0; iter < len; iter++) {
    ergebnis.v[iter] = v[iter] - x.v;
    ergebnis.e[iter] = sqrt(e[iter]*e[iter] + x.e*x.e);
  };
  return ergebnis;
}

erray erray::operator* (numberr x)
{
  erray ergebnis(len);
  for (int iter = 0; iter < len; iter++) {
    ergebnis.v[iter] = v[iter] * x.v;
    ergebnis.e[iter] = v[iter] * x.v*sqrt(e[iter]/v[iter]*e[iter]/v[iter] + x.e/x.v*x.e/x.v);
  };
  return ergebnis;
}

erray erray::operator/ (numberr x)
{
  erray ergebnis(len);
  for (int iter = 0; iter < len; iter++) {
    ergebnis.v[iter] = v[iter] / x.v;
    ergebnis.e[iter] = v[iter] / x.v * sqrt(e[iter]/v[iter]*e[iter]/v[iter] + x.e/x.v*x.e/x.v);
  };
  return ergebnis;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Operatoren
//Für 1D Errays
//Feld und Feld
erray erray::operator+ (erray x)
{
  erray ergebnis(len);
  if (len != x.len) {cout << "Errays können nicht verarbeitet werden, da die Länge nicht übereinstimmt." << endl;
  } else {
      for (int iter = 0; iter < len; iter++) {
        ergebnis.v[iter] = v[iter] + x.v[iter];
        ergebnis.e[iter] = sqrt(e[iter]*e[iter] + x.e[iter]*x.e[iter]);
      };
    }
  return ergebnis;
}

erray erray::operator- (erray x)
{
  erray ergebnis(len);
  if (len != x.len) {cout << "Errays können nicht verarbeitet werden, da die Länge nicht übereinstimmt." << endl;
  } else {
    for (int iter = 0; iter < len; iter++) {
      ergebnis.v[iter] = v[iter] - x.v[iter];
      ergebnis.e[iter] = sqrt(e[iter]*e[iter] + x.e[iter]*x.e[iter]);
    };
  }
  return ergebnis;
}

erray erray::operator* (erray x)
{
  erray ergebnis(len);
  if (len != x.len) {cout << "Errays können nicht verarbeitet werden, da die Länge nicht übereinstimmt." << endl;
  } else {
    for (int iter = 0; iter < len; iter++) {
      ergebnis.v[iter] = v[iter] * x.v[iter];
      ergebnis.e[iter] = v[iter] * x.v[iter]*sqrt(e[iter]/v[iter]*e[iter]/v[iter] + x.e[iter]/x.v[iter]*x.e[iter]/x.v[iter]);
    };
  }
  return ergebnis;
}

erray erray::operator/ (erray x)
{
  erray ergebnis(len);
  if (len != x.len) {cout << "Errays können nicht verarbeitet werden, da die Länge nicht übereinstimmt." << endl;
  } else {
    for (int iter = 0; iter < len; iter++) {
      ergebnis.v[iter] = v[iter] / x.v[iter];
      ergebnis.e[iter] = v[iter] / x.v[iter]*sqrt(e[iter]/v[iter]*e[iter]/v[iter] + x.e[iter]/x.v[iter]*x.e[iter]/x.v[iter]);
    };
  }
  return ergebnis;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Funktionen für Mittelwerte und Potenzieren
//Für 1D Errays
erray erray::topow(numberr x)
{//erray hoch numberr
  erray ergebnis(len);
  for (int iter = 0; iter < len; iter++) {
      ergebnis.v[iter] = pow(v[iter], x.v);
      ergebnis.e[iter] = sqrt( (x.v*pow(v[iter], x.v-1)*e[iter])*(x.v*pow(v[iter], x.v-1)*e[iter]) + (pow(v[iter], x.v)*log(v[iter])*x.e)*(pow(v[iter], x.v)*log(v[iter])*x.e) );
  };
  return ergebnis;
}

erray erray::topow(erray x)
{//erray hoch erray
  erray ergebnis(len);
  if (len != x.len) {cout << "Errays können nicht verarbeitet werden, da die Länge nicht übereinstimmt." << endl;
  } else {
    for (int iter = 0; iter < len; iter++) {
      ergebnis.v[iter] = pow(v[iter], x.v[iter]);
      ergebnis.e[iter] = sqrt( (x.v[iter]*pow(v[iter], x.v[iter]-1)*e[iter])*(x.v[iter]*pow(v[iter], x.v[iter]-1)*e[iter]) + (pow(v[iter], x.v[iter])*log(v[iter])*x.e[iter])*(pow(v[iter], x.v[iter])*log(v[iter])*x.e[iter]) );
    };
  }
  return ergebnis;
}

numberr erray::mean()
{
  double mean = 0;
  double error = 0;
  double stabw = 0;
  for (int iter = 0; iter < len; iter++) {
    mean = mean + v[iter];
    error = error + e[iter];
  };
  mean = mean/len;
  for (int iter = 0; iter < len; iter++) {
    stabw = stabw + (v[iter] -mean)*(v[iter] -mean);
  };
  stabw = sqrt(stabw/(len-1));
  error = error + stabw;
  return numberr(mean, error);
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Operatoren
//Für 2D Errays
//Feld und Wert



///////////////////////////////////////////////////////////////////////////////////////////////
//Funktionen für Mittelwerte und Potenzieren
//Für 2D Errays
erray erray2D::mean()
{
  erray ergebnis(len1);
  double stabw;
  for (int i=0; i<len1; i++) {
    for (int j=0; j<len2; j++) {
      ergebnis.v[i] = ergebnis.v[i] + v[i][j];
      ergebnis.e[i] = ergebnis.e[i] + e[i][j];
    };
    ergebnis.v[i] = ergebnis.v[i]/len2;
    ergebnis.e[i] = ergebnis.e[i]/len2;
    stabw = 0;
    for (int j=0; j<len2; j++) {
      stabw = stabw + (v[i][j] - ergebnis.v[i])*(v[i][j] - ergebnis.v[i]);
    };
    stabw = sqrt(stabw/(len2-1));
    ergebnis.e[i] = ergebnis.e[i] + stabw;
  };
  return ergebnis;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//Print Funktionen zum bequemen darstellen
//Zunächst Anpassung der Stellen:
string konvert (double value, double error) {
  string err = to_string(error);
  string val = to_string(value);
  string res;
  
  int komma_v = 0;
  int first_v = 999;
  int komma_e = 0;
  int sig_e = 0;
    
  int rund;
  bool first = 1;
  bool longerr = 0;
  //Zuerst werden die Positionen der Kommas sowie der ersten von 0 verschiedenen Stellen im Wert und Fehler gesucht
  for (int i = 0; (i<err.length()) || (i<val.length()); i++) {
    if (err[i] == '.') {
      komma_e = i;
    } else if ((err[i] != '0') && first) {
      if ((err[i] != '1') && (err[i] != '2')) {
        sig_e = i;
      } else {
        sig_e = i+1;
        longerr = 1;
      };
      first = 0;
    };
    if (val[i] == '.') {
      komma_v = i;
    } else if ((val[i] != '0') && (first_v == 999)) {
      first_v = i;
    };
  };
  //Jetzt wird die Stelle nach der signifikanten bestimmt um die Rundung zu entscheiden
  if (val[sig_e + (komma_v - komma_e)] == '.') {sig_e++;};
  rund = (val[sig_e + 1 + (komma_v - komma_e)]) - '0';
  
  //Jetzt wird der Ergebnis-String Stück für Stück aufgebaut
  val.erase(sig_e + 1 + (komma_v - komma_e), val.length());
  res = val[first_v];
  res += '.';
  for (int i=first_v+1; i<=val.length()-2; i++) {//-1, wegen der 0-Terminierung, ohne die -1 wird die 0-Terminierung angehängt.
    if (val[i] != '.') {
      res += val[i];
    }
  };
  //Entsprechend der Rundung wird die letzte Stelle angehängt 
  if (rund < 5) {
    res += val[val.length()-1];
  } else {
    res += to_string( (int)val[val.length()-1] - 47);
  };
  
  res += '(';
  
  //Der Fehler wird nun aufgerundet, dafür wird die int rund wieder verwendet
  rund = 0;
  if (longerr) {
    if (err[sig_e-1] == '.') {
      rund += (10* ((int)err[sig_e-2] - 48));
    } else {
      rund += (10* ((int)err[sig_e-1] - 48));
    };
  };
  if (err[sig_e] == '.') {
    rund +=  (((int)err[sig_e+1]) - 47);
  } else {
    rund +=  (((int)err[sig_e]) - 47);
  };
  res += to_string(rund);
  res += ')';
  
  //Es wird noch die Zehnerpotenz ausgegeben
  if ((first_v < komma_v) && (komma_v != 1)) {
    res = res + "e" + to_string(komma_v-1);
  } else if (first_v > komma_v) {
    res = res + "e-" + to_string(first_v-1);
  };   
  
  return res;
}



//Für Einzelwerte
void numberr::print ()
{
  cout << "\\SI{" << konvert(v,e) << "}" << endl;
}

void numberr::to_file (string name)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  data << "\\SI{" << konvert(v,e) << "}" << endl;
  data.close();
}

void numberr::to_file (string name, string einheit)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  data << "\\SI{" << konvert(v,e) << "}{" << einheit << "}" << endl;
  data.close();
}

void numberr::to_file (string name, string einheit, string text)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  //cout << konvert(v,e) << endl;
  data << text << endl << "\\SI{" << konvert(v,e) << "}{" << einheit << "}" << endl;
  //data << v << "\\pm" << e << endl;
  data.close();
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Print Funktionen zum bequemen darstellen
//Für 1D Errays
void erray::print ()
{
  for (int i=0; i<len; i++) {
    cout << v[i] << " \\pm " << e[i] << endl;
  }
}
 
void erray::to_file (string name)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  for (int i=0; i<len; i++) {
    data << "\\SI{" << konvert(v[i],e[i]) << "}" << endl;
  };
  data.close();
} 

void erray::to_file (string name, string einheit)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  for (int i=0; i<len; i++) {
    data << "\\SI{" << konvert(v[i],e[i]) << "}{" << einheit << "}" << endl;
  };
  data.close();
}

void erray::to_file (string name, string einheit, string text)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  data << text << endl;
  for (int i=0; i<len; i++) {
    //cout << "\\SI{" << konvert(v[i],e[i]) << "}{" << einheit << "}" << endl;
    data << "\\SI{" << konvert(v[i],e[i]) << "}{" << einheit << "}" << endl;
    data << v[i] << "\\pm" << e[i] << endl;
  };
  data.close();
}

void erray::to_tablerow (string name)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  for (int i=0; i<len; i++) {
    //cout << "\\SI{" << konvert(v[i],e[i]) << "}{" << einheit << "}" << endl;
    data << "\\num{" << konvert(v[i],e[i]) << "}" << "&";
  };
  data << endl;
  data.close();
}

   
///////////////////////////////////////////////////////////////////////////////////////////////
//Print Funktionen zum bequemen darstellen
//Für 2D Errays
void erray2D::print ()
{
  for (int i=0; i<len1; i++) {
    cout << i << ". Datenreihe:" << endl;
    for (int j=0; j<len2; j++) {
      cout << v[i][j] << " \\pm " << e[i][j] << endl;
    }
    cout << endl;
  }
}

void erray2D::to_file (string name, string text)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  data << text << endl;
  for (int i=0; i<len1; i++) {
    data << i << ". Datenreihe:" << endl;
    for (int j=0; j<len2; j++) {
      data << v[i][j] << " \\pm " << e[i][j] << endl;
    }
    data << endl;
  };
  data.close();
}
  
void erray2D::to_file (string name)
{
  ofstream data;
  data.open(name + ".csv", std::ios_base::app);
  //data.seekp(ios_base::end);
  for (int i=0; i<len1; i++) {
    data << i << ". Datenreihe:" << endl;
    for (int j=0; j<len2; j++) {
      data << v[i][j] << " \\pm " << e[i][j] << endl;
    }
    data << endl;
  };
  data.close();
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
