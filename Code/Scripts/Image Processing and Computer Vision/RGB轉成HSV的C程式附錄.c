/************************************************************/
/**  �\��F�NRGB�Ҧ��x�s���v���ഫ��HSV�Ҧ��x�s���v��  **/
/**  �ѼƤ@�F��lRGB�v��                                 **/
/**  �ѼƤG�F�ഫ�X��HSV�v��                             **/
/************************************************************/
void RGB2HSV(double RGB[3][M][N], double HSV[3][M][N])
{
  int i, j, k;
  double H1, Max, min, R, G, B ; PI=3.1415926;
  for(i=0 ;i<M ;i++)
  {
    for(j=0 ;j<N ;j++)
    {
      B = RGB [0][i][j];
      G = RGB [1][i][j];
      R = RGB [2][i][j];          
/*Ū�XRGB�H�K�B��*/
      k=0;                     
/*HSV�x�}��H�BS�MV index*/
/*-----------�DRGB��Max�Mmin-----------*/
      Max=R;
      min=R;       
/*�@�}�l���NMax�Mmin�]��R*/
      if(Max<=G)
        Max=G;   
      else
        min=G;   
/*�YMax�p�󵥩�G�h�s��Max�]��G�F�_�h�s��min�]��G*/
      if(Max<=B)
        Max=B;
      else if(min>=B)
        min=B;
/*�YMax�p�󵥩�B�h�s��Max�]��B*/
/*�_�h�Ymin�j��B�h�s��min�]��B*/

/*------------�D���H(Hue)-----------------*/
       H1=acos(0.5*((R-G)+(R-B))/sqrt(((R-G)*(R-G)+(R-B)*(G-B))));
       if(B<=G)
         HSV[k][i][j]=H1;
       else
         HSV[k][i][j]=2*PI-H1;
       k++;
/*-------------�D���M��S----------------------*/
       HSV[k][i][j]=(Max-min)/Max;
       k++;
/*-------------�D���G��V----------------------*/
       HSV[k][i][j]=Max/255;
       k++;
    }/*end for j*/
  }/*end for i*/
}