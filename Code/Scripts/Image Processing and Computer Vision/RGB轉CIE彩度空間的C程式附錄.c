/******************************************************************************/
/* �\��G�NRGB�m��Ŷ��ഫ��CIE�G���y�бm�ץ����Ŷ�*/
/* �ѼƤ@�G��l�v����R�������Ȧs��*/
/* �ѼƤG�G��l�v����G�������Ȧs��*/
/* �ѼƤT�G��l�v����B�������Ȧs��*/
/* �Ѽƥ|�G�B��᪺CIE�v��X�����Ȧs��*/
/* �ѼƤ��G�B��᪺CIE�v��Y�����Ȧs��*/
/* �ѼƤ��G��l�v������*/
/* �ѼƤC�G��l�v�����e*/
/******************************************************************************/

void RGBtoCIE ( unsigned char ** OriginalImgR, unsigned char ** OriginalImgG, unsigned char ** OriginalImgB, unsigned char **CIEX, unsigned char **CIEY,int ImgHeight, int ImgWidth )
{
  int **CIEx, **CIEy, **CIEz;

  CIEx = new int *[ImgHeight];
  CIEy = new int *[ImgHeight];
  CIEz = new int *[ImgHeight];

  for(int i=0; i<ImgHeight; i++)
  {
    CIEx[i] = new int [ImgWidth];
    CIEy[i] = new int [ImgWidth];
    CIEz[i] = new int [ImgWidth];
  }

  // �NRGB�Ŷ��নCIE��xyz 
  for(int i=0; i<ImgHeight; i++)                   
    for(int j=0; j<ImgWidth; j++)
    {
      CIEx[i][j]=(int)((0.607*OriginalImgR[i][j])+(0.174*OriginalImgG[i][j])+(0.200*OriginalImgB[i][j]));      CIEy[i][j]=(int)((0.299*OriginalImgR[i][j])+(0.587*OriginalImgG[i][j])+(0.114*OriginalImgB[i][j])) ;
      CIEz[i][j]= (int)((0.066*OriginalImgG[i][j])+(1.111*OriginalImgB[i][j])) ;
    }

//�qCIE��xyz���XY�����y�Шt��
  for( int p=0; p<ImgHeight; p++)                      
    for( int q=0; q<ImgWidth; q++)
    {
      if(CIEx[p][q]!=0||CIEy[p][q]!=0||CIEz[p][q]!=0)
      {
        CIEX[p][q]= (int)(256*(CIEx[p][q])/(CIEx[p][q]+CIEy[p][q]+CIEz[p][q]));
        CIEY[p][q]= (int)(256*(CIEy[p][q])/(CIEx[p][q]+CIEy[p][q]+CIEz[p][q]));
      }
    }
}