
#include <stdio.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

#define max 101
#define max1 3000

#define g 10 //unidades
#define c 0.2
#define m 0.3
#define velocidadInicial 300.0
#define t_maximo 100
#define pasos 1000
#define pi acos(-1)

float h = t_maximo/pasos;


vector<float> aceleracion_x(float v_x, float v_y)
{
  vector<float> a(2);
  float magnitud = v_x*v_x + v_y*v_y;
  float a_x = -(c/m)*magnitud;
  float a_y = - g - (c/m)*magnitud;
  a[0] = a_x;
  a[1] = a_y;
  return a;
}

vector<float> rungeVelocidad(float v_x, float v_y)
{
  float l1_x;
  float l1_y;
  float l2_x;
  float l2_y;
  float l3_x;
  float l3_y;
  float l4_x;
  float l4_y;
  vector<float> vel(2);

  vector<float> a1 = aceleracion_x(v_x,v_y);
  l1_x = h*a1[0];

  l1_y = h*a1[1];

  vector<float> a2 = aceleracion_x(v_x,v_y + 0.5*l1_y);
  l2_x = h*a2[0];

  l2_y = h*a2[1];

  vector<float> a3 = aceleracion_x(v_x, v_y + 0.5*l2_y);
  l3_x = h*a3[0];
  l3_y = h*(v_x + 0.5*l3_x);

  l3_y = h*a3[1];

  vector<float> a4 = aceleracion_x(v_x,v_y + 0.5*l3_y);
  l4_x = h*a4[0];

  l4_y = h*a4[1];

  vel[0] = v_x + (1/6)*(l1_x + 2*l2_x + 2*l3_x + l4_x);
  vel[1] = v_y + (1/6)*(l1_y + 2*l2_y + 2*l3_y + l4_y);

  return vel;
}

vector<float> rungePosicion(float v_x, float v_y, float x_0, float y_0)
{

  vector<float> pos(2);
  float l1_x, k1_x;
  float l1_y, k1_y;
  float l2_x, k2_x;
  float l2_y, k2_y;
  float l3_x, k3_x;
  float l3_y, k3_y;
  float l4_x, k4_x;
  float l4_y, k4_y;

  vector<float> a1 = aceleracion_x(v_x,v_y);
  l1_x = h*a1[0];
  k1_x = h*(v_x);

  l1_y = h*a1[1];
  k1_y = h*(v_y);

  vector<float> a2 = aceleracion_x(v_x,v_y+0.5*l1_y);
  l2_x = h*a2[0];
  k2_x = h*(v_x+0.5*l2_x);

  l2_y = h*a2[1];
  k2_y = h*(v_y+0.5*l2_y);

  vector<float> a3 = aceleracion_x(v_x,v_y+0.5*l2_y);
  l3_x = h*a3[0];
  k3_x = h*(v_x+0.5*l3_x);

  l3_y = h*a3[1];
  k3_y = h*(v_y+0.5*l3_y);

  vector<float> a4 = aceleracion_x(v_x,v_y+0.5*l3_y);
  l4_x = h*a4[0];
  k4_x = h*(v_x+0.5*l4_x);

  l4_y = h*a4[1];
  k4_y = h*(v_y+0.5*l4_y);

  pos[0] = x_0 + (1/6)*(k1_x + 2*k2_x + 2*k3_x + k4_x);
  pos[1] = y_0 + (1/6)*(k1_y + 2*k2_y + 2*k3_y + k4_y);

  return pos;
}


int main()
{

  float theta = 45;
  ofstream FILE;
  FILE.open("datos.txt");
  float tiempo = h;
  float h = t_maximo/pasos;
  int i = 0;
  vector<float> t;
  t.push_back(0.0);

  vector<float> posicionX;
  posicionX.push_back(0.0);

  vector<float> posicionY;
  posicionY.push_back(0.0);

  float velocidadInicialX = velocidadInicial*sin(theta*pi/180.0);
  float velocidadInicialY = velocidadInicial*cos(theta*pi/180.0);

  vector<float> velocidadX;
  velocidadX.push_back(velocidadInicialX);

  vector<float> velocidadY;
  velocidadY.push_back(velocidadInicialY);

  while ( posicionY[i] >= 10.0)
  {
    vector<float> rungeVel = rungeVelocidad(velocidadX[i],velocidadY[i]);
    velocidadX.push_back(rungeVel[0]);
    velocidadY.push_back(rungeVel[1]);

    vector<float> rungePos = rungePosicion(velocidadX[i], velocidadY[i], posicionX[i], posicionY[i]);
    posicionX.push_back(rungePos[0]);
    posicionY.push_back(rungePos[1]);

    FILE << rungePos[0] << "," << rungePos[1] << endl ;

    t.push_back(tiempo);
    tiempo += h;
    i +=1;
  }
  FILE.close();
  return 0;
}
