/*1.�۩w�@�Ӧs�I��X Y�y�Ф����c*/
typedef  struct xyPoint {
  short int X;
  short int Y;
}XYPoint;
/*2.�۩w�@�Ӧs���J�ѼƪŶ��W�Y�Ѽ��I�y�ЭȪ����c�A�Φ��ӰO���b�ѼƪŶ����ҧ�줧�ĴX���u�A�p��l(Cell) ��b�ѼƪŶ��W����m {I1, I2} �O���Э�*/
typedef  struct htlinePoint {
  short int I1;         // �O���ѼƪŶ��W�Ĥ@�Ѽƪ��y�Э�
  short int I2;         // �O���ѼƪŶ��W�ĤG�Ѽƪ��y�Э�
}HTLinePoint ;  
/*3.�۩w�@�Ӹ�Ƶ��c���x�s���J�ഫ�����u���G*/
typedef struct htline
{
  float DeltaNormAngle;    	// �s�k���t��
  float DeltaNormDistance; 	// �s�k�u�t[���j��] 
  int ThetaNum;         	// �s�k���q�ƫᤧ(�϶�)�Ӽ�
  int DistNum;          	// �s�k�Z�q�ƫᤧ(�϶�)�Ӽ�
  float MinNormdistance;  	// �s�k�Z���̤p�ȥ�
  HTLinePoint *LinePoint;   // �s�b���J�ѼƪŶ��W���䬰�@�u���p�Фl����Ӯy��index��
}HTLine;

/************************************************************/
/*���J�ഫ���u�t��k	*/
/*��J	*/
/*EdgePoin	���I��	*/
/*EdgeNum	�`���I��	*/
/*DetectedLine	���u���G	*/
/*MaxPointCount	�s�ѼƪŶ����@�Ӥp�Фl�h���I�i�Q�������@�u�����e��*/
/*ThetaNum  	�k���q�ƫᤧ(�϶�)�Ӽ�	*/
/*DistNum 	�k�Z�q�ƫᤧ(�϶�)�Ӽ�	*/
/*ImgHeight 	�ݴ��v��������	*/
/*ImgWidth 	�ݴ��v�����e��	*/
 /*��X�G	*/
/*CountLine	�`�@���쪺���u��	*/
/************************************************************/

int HTDetectLine ( XYPoint *EdgePoint, int EdgeNum, HTLine *DetectedLine, int MaxPointCount, int ThetaNum, int DistNum, int ImgHeight, int ImgWidth)
{
  /*�s�k���Ϊk�u�t[���j��], ���D���J�ѼƪŶ��i�����h�֤p�Фl��*/
  float  DeltaNormAngle, DeltaNormDistance ;
  /*�s�k�Z���̤j�ȩM�̤p�ȥ�*/
  float MaxNormdistance, MinNormdistance ;
  /*�N�U���IX,Y�b�벼���ন�ѼƪŶ�(Theta, Dist)����*/
  float Theta , Dist;
  /*�ΨӰO�����X���u*/
  int CountLine  ;
  /*�@���벼�ɦb���J�Ŷ����Y���I(x,y)�Ҧb���p�Фl��Ĥ@index�U, �ҨD�X���ĤGindex���{    ���x�s�ܼ� */
  short int TempIndex2 ;
  /*�G�����ѼƪŶ�(�ֿn�}�C)*/
  int **HSCellCount;
  /*�̷ӨϥΪ̩ҩw�j�p�ʺA�t�m�ֿn�}�C*/
  HSCellCount=new int *[ThetaNum];
  for(int i=0;i<ThetaNum;i++)
    HSCellCount[i]=new int [DistNum];

  /*�k�Z�̤j�Ȭ�sqrt(x^2+y^2)*/
  MaxNormdistance=sqrt(ImgWidth*ImgWidth+ImgHeight*ImgHeight);
  /*�k�Z�t�̤j�Ȭ�x�b���j�p*/
  MinNormdistance= -1*ImgWidth; /*�k�Z�t�̤j���t x �b*/
  /*�T�w�Ѽƪk���ƥؤU, ��k���t���`��/�Ӽ� [�`���� pi]*/
  DeltaNormAngle = M_PI/(ThetaNum -1) ;
  /*�T�w�Ѽƪk�Z�ƥؤU, ��k�Z�t*/
  DeltaNormDistance= (MaxNormdistance - MinNormdistance)/(DistNum -1) ;
  /*�G�����ѼƪŶ�, HSCellCount1(i, j) �s�벼��, �{�]�U�p�Фl���Ƭ� 0*/
  for (int i=0;i<ThetaNum;i++ )
    for(int j=0;j<DistNum;j++ )
      HSCellCount[i][j]=0  ;
  Theta=0;
  Dist=EdgePoint[0].X*cos(Theta)+EdgePoint[0].Y*sin(Theta) ;
  for(int i=0;i<EdgeNum;i++)
    for(int j=0;j<ThetaNum;j++)
    {
       /*�����[�̤p�k��, �]�� 0 �G����, �D�k���W�U�q�ư϶����k����
       �h��*/
       Theta=j*DeltaNormAngle ;
       /*�D�Y���I�b�k���U��k�Z���h��*/
       Dist=EdgePoint[i].X*cos(Theta)+EdgePoint[i].Y*sin(Theta) ;
       /*��ҨD�k�Z�ݩ�ĴX�Ӱ϶�, �åB�b�۹�����cell�벼*/
       HSCellCount[j][(int)((Dist-MinNormdistance)/DeltaNormDistance)]++;
    }
  /*��ȳ]�ثe�S���u, �{�b���X���u�`�Ƭ�0*/
  CountLine = 0 ;
  /*�x�s�������u�ҨϥΪ��U���ѼƳ]�w*/
  DetectedLine->DeltaNormAngle=DeltaNormAngle;
  DetectedLine->DeltaNormDistance=DeltaNormDistance;
  DetectedLine->MinNormdistance=MinNormdistance;
  DetectedLine->ThetaNum=ThetaNum;
  DetectedLine->DistNum=DistNum;
  /*�D���X�Ӥp�Фl���벼�Ƥj��MaxPointCount, �Y�b���J�Ŷ������X���u*/
  for(int i=0;i<ThetaNum;i++)     
    for(int j=0;j<DistNum;j++)
    /*���@�p�Фl�벼�I�ư��j��, �Y�{�w���@�u�s�b*/
      if (HSCellCount[i][j]>=MaxPointCount)
      {
        CountLine++;
        DetectedLine->LinePoint[CountLine].I1=i;
        DetectedLine->LinePoint[CountLine].I2=j;
      }

  for(int i=0;i<ThetaNum;i++)
    delete [] HSCellCount[i];

  delete[] HSCellCount;
  return CountLine;
}