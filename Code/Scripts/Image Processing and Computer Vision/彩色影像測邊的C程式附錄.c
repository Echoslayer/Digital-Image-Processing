/******************************************************************/
/*�V�q�Ƨǲέp����¦���m����侹*/
/*�ޥΨ�ơG*/
/* #include <math.h>*/
/*�`�ơG*/
/* Threshold  ���e��*/
/* SubImageSize	���n�j�p*/
/* MedianNum	���h�֭Ӥ���ƨӥ��������������T*/
/* AllowImpulsiveNoise	���n���e�Ԫ��߽����T�Ӽ�*/
/*��J�ܼơG*/
/* InputCIEColorMap	��J�v��/
/* ImageHeight	��J�v�����C��*/
/* ImageWidth	��J�v�������*/
/*�۩w���c�G*/
typedef struct
{		
  double Y;	
  double u;
  double v;
}CIEColor;		
/*��X�ܼơG*/
/* EdgeMap ���*/
/*****************************************************************/

//---���J�ƧǪk------------------------------------------------------------
void Insertion_sort(double *a,int *b)
{
  int l = SubImageSize;
  int i,j;
  int key2;
  double key1;

  for(j=1; j<l;j++)
  {
    key1 = a[j];
    key2 = b[j];

    for (i = j-1; i>=0 && a[i]>key1; i--)
    {
      a[i+1] = a[i];
      b[i+1] = b[i];
    }

    a[i+1] = key1;
    b[i+1] = key2;
  }
}

//---����t��k-----------------------------------------------------------
double MaskEdgeDetector(CIEColor *ColorPixel)
{
  double VD;
  CIEColor midXi,TempColor;

  MVD=infinte;
  int *order=new int [SubImageSize];
  double *d=new double [SubImageSize];

  for(int i=0;i<SubImageSize;i++)
  {
    d[i]=0.0;
  }

  //---���q���n���U�I�����Z��
  for (int m=0; m<SubImageSize; m++)
  {
    for (int n=0; n<SubImageSize; n++)
    {
      TempColor.Y=fabs(ColorPixel[m].Y - ColorPixel[n].Y);                 
      TempColor.u=fabs(ColorPixel[m].u - ColorPixel[n].u);                 
      TempColor.v=fabs(ColorPixel[m].v - ColorPixel[n].v);                 
      d[m] += TempColor.Y+TempColor.u+TempColor.v;             
    }
  }

  for (int k=0; k<SubImageSize; k++)
    order[k] = k;

  Insertion_sort(d,order);

   midXi.Y = 0;
   midXi.u = 0;
   midXi.v = 0;

  //---���ƭӤ���ƥ����A�H�h���������T
  for (int l=0; l<MedianNum; l++)
  {
    midXi.Y += ColorPixel[order[l]].Y;
    midXi.u += ColorPixel[order[l]].u;
    midXi.v += ColorPixel[order[l]].v;
  }
  midXi.Y /= MedianNum;
  midXi.u /= MedianNum;
  midXi.v /= MedianNum;

  //---���\���n���߽����T�A�H�h���߽����T
  for (int k=0; k<AllowImpulsiveNoise; k++)
  {
    TempColor.Y=fabs(ColorPixel[order[(SubImageSize-1)-k]].Y - midXi.Y);             
    TempColor.u=fabs(ColorPixel[order[(SubImageSize-1)-k]].u - midXi.u);             
    TempColor.v=fabs(ColorPixel[order[(SubImageSize-1)-k]].v - midXi.v);             
    //���oVD��
    VD=TempColor.Y+TempColor.u+TempColor.v;  
    if (VD < MVD)
      MVD = VD;   //���̤pVD��MVD
    }
    delete order;
    delete d;
    return MVD;
}

EdgeMapCreate(CIEColor **InputCIEColorMap, bool **EdgeMap int ImageHeight,int ImageWidth)
{
  double MVD;
  ImgWidth=ImageWidth;
  ImgHeight=ImageHeight;

  CIEColor *SubImageCIEColor;

  int Temp=(int)(sqrt(SubImageSize)/2); //���o���n���
  int StartCount=-Temp;
  int EndCount=Temp;
  SubImageCIEColor=new CIEColor [SubImageSize];
  for(int i=1;i<ImgHeight-1;i++)      //���˹Ϥ�
  {
    for(int j=1;j<ImgWidth-1;j++)
    {
      EdgeMap[i][j]=false;
      int tempNum=0;
      //���y���n���e
      for(int m=StartCount;m<=EndCount;m++)
      {
        for(int n=StartCount;n<=EndCount;n++)
        { 
          SubImageCIEColor[tempNum].Y =InputCIEColorMap[i+m][j+n].Y;                                          
          SubImageCIEColor[tempNum].u = InputCIEColorMap[i+m][j+n].u;
          SubImageCIEColor[tempNum].v = InputCIEColorMap[i+m][j+n].v;
          tempNum++;
        }
      }
      MVD=MaskEdgeDetector(SubImageCIEColor); //�⭱�n���e�e�J����t��k�p��
      If (MVD>=Threshold)                           
        EdgeMap[i][j]=true;
      }
    }
  }
  delete SubImageCIEColor;
}