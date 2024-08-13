/*1.	�۩w�@�Ӧs�I��X Y�y�Ф����c�C*/
typedef  struct xyPoint {
short int X;
  	short int Y;
}XYPoint;
/* 2.	�۩w�@�Ӧs��߮y�ЩM�b�|�����c�C*/
typedef struct circle{
short int CCX;
short int CCY;
short int Rr;
}CIRCLE;


/******************************************************************/
/*�H��������k(�K�ӿ�J�ܼƻP�@�ӿ�X�ܼ�)	*/
/*��J�ܼơG		*/
/*EdgePoin	���I��	*/
/*EdgeNum	�`���I��	*/
/*ThresholdRnd	���u���G	*/
/*ThresholdCoCircleDist	�s�ĥ|�I�M�e�T�I�զ�����P�W���Z��	*/
/*	�h�֤���@��	*/
/*Threshold2PDist	�����ꤧ�T�I�䩼�����Z���t����n�h	*/
/*	�֥H�W�����e��	*/
/*ThresholdCircleRatio	�O����줧���I�ƭn�ŦX�z�פW���I��	*/
/*	[4*�ڸ�2*�b�|] ���h�֦ʤ���	*/
/*ThresholdCirclePoint	���h���I�i�����@��, �Y�h�֭Ө䥦�I	*/
/*	�M��줧���~��o���I�����@�Ӷ�	*/
/*CircleData 	�Ҵ��쪺�ꪺ���(��ߩM�b�|)	*/
/*��X�ܼơG		*/
/*CountLine 	�`�@���쪺��Ӽ�	*/
/*****************************************************************/
int DetectCircleRand1(XYPoint *EdgePoint,int EdgeNum, int ThresholdRnd, 
int ThresholdCoCircleDist, int Threshold2PDist,
int ThresholdCircleRatio, int ThresholdCirclePoint, 
CIRCLE *CircleData)
{
  XYPoint TempEdgePoint[6000] ;
/*�s�ҧ�줧�H���|�I�bTempEdgePoint �@���}�C������m*/
  int  p[5]; 
  /*�I 1 �� RestEdgeNum �O�������u�I�����I*/
int RestEdgeNum ; 
/*�b�S���T�w�ҧ줧�I�u���O���@���u�W���I�e,RestEdgeNum ������*/
/*�ҥH�� TempRestNum �ӼȮɦs�{�ɧ��ܤ��Ҿl�n�B�z�����I��*/
int TempRestNum ;    
/*�O���ثe�w�i���h�֦����T�I���ѤΧ�h�֦��T�I��~�n�Ҥ����\[���ŦX���u]�K�����{�������e��*/
int RndCount; 
/*�Ω�j�鱱����Х�*/
int i;
/*�Ω�b���I���H����|�I���j�鱱�����*/
int i4;    
/*�H�����, �Y���n�洫��, �Φ��ӼȦs�洫�����I [�s���I x,y �y��]*/
XYPoint SwapTemp; 
/*�s�� random ��X����ƭ�, �Φ��Ȩӧ�X�@�����I�}�C�����Y�I*/
int RndValue; 
/*�s�|�I�� 4 �դ����T�I���ұo����ߪ� x, y �y��*/
float Cx123,Cy123, Cx124,Cy124, Cx134,Cy134, Cx234,Cy234; 
/*/����K��{���p��, ���D�X���(a,b)��TempD, �A�D�b�| r*/
float TempD123, TempD124, TempD134, TempD234; 
/*�s�|�I�� 4 �դ����T�I�ҨD�X����b�|*/
float Radius123, Radius124, Radius134, Radius234; 
/*�s�H���� 4 �I��, �ĥ|�I��e�T�I�զ�����P�W���Z��*/
float Dist4To123, Dist3To124, Dist2To134, Dist1To234;
/*���O�s�ҨD�ꤧ���(a=CenterX,b=CenterY) �Υb�| r=RadiusR*/
float CenterX,CenterY,RadiusR;
/*�s X1^2+Y1^2 ��, �Y�Ĥ@�I�M���I���Z��������*/
int Square1; 
/*�s Xi^2+Yi^2 ��, �Y�� 2,3,4 �I�M���I���Z��������*/
int Square2,Square3,Square4; 
/*���{������F��K, ��ҧ�줧�H�� 4 ���I�y�Эȩ�b���ܼƤW*/
int X1,Y1, X2,Y2, X3,Y3, X4,Y4; 
/*�s��2,3,4�I��Ĥ@�I�� x,y �W���t��*/
int X21,Y21; 
int X31,Y31; 
int X41,Y41; 
int X32,Y32; 
int X42,Y42; 
int X43,Y43; 
int denom123; 
/* denom234 = 2[(X3-X2)(Y4-Y2)-(Y3-Y2)(X4-X2)], ���� 123 ��� a,b �ɭn�Ψ줧���� */
int denom124,denom134,denom234 ; 
/*�T�w�Y���ꤧ�T�I�U, �O���ثe���h�ֲĥ|�I�M�o�T�I�@��*/
int CountCirclePoint; 
/*�����,�s�䥦�ĥ|�I�M�ҧ�줧�T�I�զ�����P�W���Z��*/
float DistToCircle; 
/*�ΨӰO�����X�Ӷ�*/
int CountCircle; 
/*�s�ҧ�줧�u�n�e�X�ɤ��C��*/
int DrawColor;  
/*���C�����üƮɬҤ��P, �ҥH�Φ����O*/
randomize();   
/*��EdgePoint�bTempEdgePoint�W�ƥ�,�H�@���᭱�B�z�ɤ��i�����*/
for( i = 1;i<=EdgeNum;i++)  
TempEdgePoint[i] = EdgePoint[i];
/*��@���ܼƭȪ�ɤ�*/
CountCircle = 0; 
RndCount = 0; 
RestEdgeNum = EdgeNum; 
TempRestNum = RestEdgeNum; 
while ( RndCount <= ThresholdRnd && RestEdgeNum >= 
ThresholdCirclePoint )
{
  /*��|�I�ӬݬO�_�����ꤧ�Ҿ�*/         
  for(i4 = 1; i4<=4;i4++)  
  {
    /*�O���U�ҧ줧��i4�I���ثeTempEdgePoint���I�}�C����m*/
    /*�]���ҧ줧�I����᭱, �ҥH�䬰�ثe�̫ᤧ�I*/
    p[i4] = TempRestNum; 
    RndValue = ( rand() % TempRestNum + 1); 
    /*��줧�I���᭱���T�I�W*/
    SwapTemp.X = TempEdgePoint[RndValue].X; 
    SwapTemp.Y = TempEdgePoint[RndValue].Y;
    TempEdgePoint[RndValue].X = TempEdgePoint[TempRestNum].X;
    TempEdgePoint[RndValue].Y = TempEdgePoint[TempRestNum].Y;
    TempEdgePoint[TempRestNum].X = SwapTemp.X;      
TempEdgePoint[TempRestNum].Y = SwapTemp.Y;
    TempRestNum = TempRestNum - 1; /*�{�ɩʪ����I�Ƥ֤@*/
 } 
 /*�ҧ줧�|�I�s�b TempEdgePoint �� p[1],p[2],p[3],p[4] ��m�W*/

  X1=TempEdgePoint[p[1]].X;
  Y1=TempEdgePoint[p[1]].Y;
  X2=TempEdgePoint[p[2]].X;
  Y2=TempEdgePoint[p[2]].Y;
  X3=TempEdgePoint[p[3]].X;
  Y3=TempEdgePoint[p[3]].Y;
  X4=TempEdgePoint[p[4]].X;
  Y4=TempEdgePoint[p[4]].Y;
  /*�s�ҧ줧�|�I�� X^2+Y^2 ��*/
  Square1= TempEdgePoint[p[1]].X*TempEdgePoint[p[1]].X+
TempEdgePoint[p[1]].Y*TempEdgePoint[p[1]].Y; 
  Square2= TempEdgePoint[p[2]].X*TempEdgePoint[p[2]].X+
TempEdgePoint[p[2]].Y*TempEdgePoint[p[2]].Y; 
  Square3= TempEdgePoint[p[3]].X*TempEdgePoint[p[3]].X+
TempEdgePoint[p[3]].Y*TempEdgePoint[p[3]].Y; 
  Square4= TempEdgePoint[p[4]].X*TempEdgePoint[p[4]].X+
TempEdgePoint[p[4]].Y*TempEdgePoint[p[4]].Y; 
  /*�D��2,3,4�I���1�I��X�PY��V�W���t��*/
  X21=X2-X1; 
  Y21=Y2-Y1; 
  X31=X3-X1; 
  Y31=Y3-Y1; 
  X41=X4-X1; 
  Y41=Y4-Y1; 
  X32=X3-X2; 
  Y32=Y3-Y2; 
  X42=X4-X2; 
  Y42=Y4-Y2; 
  X43=X4-X3; 
  Y43=Y4-Y3; 

  /*�s���I�����Z����*/
  int SquareDist21 = (X21*X21)+(Y21*Y21); 
  int SquareDist31 = (X31*X31)+(Y31*Y31);
  int SquareDist41 = (X41*X41)+(Y41*Y41);
  int SquareDist32 = (X32*X32)+(Y32*Y32);
  int SquareDist42 = (X42*X42)+(Y42*Y42);
  int SquareDist43 = (X43*X43)+(Y43*Y43);
  /*�ѥ�123,124,134,234,�I�զ����ꪺ���*/
  denom123 = 2*(X21*Y31 - X31*Y21); 
  denom124 = 2*(X21*Y41 - X41*Y21); 
  denom134 = 2*(X31*Y41 - X41*Y31);
  denom234 = 2*(X32*Y42 - X42*Y32);
  /*�D��4 �I�M�Һ�X���ꤧ�t���L�{*/
  if (denom123==0) /*������ 0 ���, 234 �T�I�@�u, ���|����*/
    Dist4To123= 1000;
  else 
  {
    Cx123=((Square2-Square1)*(Y31)-(Square3-Square1)*(Y21))/denom123;
    Cy123=((Square3-Square1)*(X21)-(Square2-Square1)*(X31))/denom123;
    /*2*X1*a+2*Y1*b+TempD123=X1^2+Y1^2 [�Ѥ�{���i�o]*/
    TempD123= Square1- 2*X1*Cx123 - 2*Y1*Cy123; 
    Radius123= sqrt(TempD123 + Cx123 * Cx123 + Cy123 * Cy123);
    /*TempD= r^2-a^2-b^2 , or r^2 = TempD + a^2 + b^2*/
    Dist4To123=sqrt((X4-Cx123)*(X4-Cx123)+(Y4-Cy123)*(Y4-Cy123))- 
    Radius123;
    /*�ĥ|�I�M��P���Z�����M��ߤ��Z�����b�|���t�������*/
    if (Dist4To123<0)
    Dist4To123 = -1 * Dist4To123; 
  }

  /*�D�� 3 �I�M�Һ�X���ꤧ�t���L�{*/
  if (denom124==0) // ������ 0 ���, 234 �T�I�@�u, ���|����   
    Dist3To124= 1000 ;
  else
 {
    Cx124=((Square2-Square1)*(Y41)-(Square4-Square1)*(Y21))/denom124;
    Cy124=((Square4-Square1)*(X21)-(Square2-Square1)*(X41))/denom124;
    TempD124= Square1- 2*X1*Cx124 - 2*Y1*Cy124; 
    Radius124= sqrt(TempD124 + Cx124 * Cx124 + Cy124 * Cy124);
    Dist3To124=sqrt((X3-Cx124)*(X3-Cx124)+ (Y3-Cy124)*(Y3-Cy124))- 
    Radius124;
    if (Dist3To124<0)
        Dist3To124 = -1 * Dist3To124 ; 
  }
  /*�D�� 2 �I�M�Һ�X���ꤧ�t���L�{*/
  if (denom134==0) /*������ 0 ���, 234 �T�I�@�u, ���|����*/   
    Dist2To134= 1000;
  else
  {
    Cx134=((Square3-Square1)*(Y41)-(Square4-Square1)*(Y31))/denom134;
    Cy134=((Square4-Square1)*(X31)-(Square3-Square1)*(X41))/denom134;
    TempD134= Square1- 2*X1*Cx134 - 2*Y1*Cy134; 
    Radius134= sqrt(TempD134 + Cx134 * Cx134 + Cy134 * Cy134);
    Dist2To134 = sqrt((X2-Cx134)*(X2-Cx134)+ (Y2-Cy134)*(Y2-Cy134))- 
    Radius134;
    if (Dist2To134<0) 
       Dist2To134 = -1 * Dist2To134;
  }

  /*�D�� 1 �I�M�Һ�X���ꤧ�t���L�{*/
  if (denom234==0)/*������ 0 ���, 234 �T�I�@�u, ���|����*/  
    Dist1To234= 1000;
  else 
  {
    Cx234=((Square3-Square2)*(Y42)-(Square4-Square2)*(Y32))/denom234;
    Cy234=((Square4-Square2)*(X32)-(Square3-Square2)*(X42))/denom234;
    TempD234= Square2- 2*X2*Cx234 - 2*Y2*Cy234;
    Radius234= sqrt(TempD234 + Cx234 * Cx234 + Cy234 * Cy234);
    Dist1To234 = sqrt((X1-Cx234)*(X1-Cx234)+ (Y1-Cy234)*(Y1-Cy234))- 
    Radius234;
    if (Dist1To234<0)
    Dist1To234 = -1 * Dist1To234;
  }
/*�W���|�ո�ƬҺ�n�F, �U���}�l�P�_���@�դ���, �i�ϥt�@�I�]�b��W, �Y�Ӳլ��i�ध��*/
/*�����O��T�I�զ����ꪺ�T�I���Z��������*/
  if((Dist4To123>ThresholdCoCircleDist || SquareDist21 <=Threshold2PDist ||
    SquareDist31 <=Threshold2PDist || SquareDist32<=Threshold2PDist) &&
    (Dist3To124>ThresholdCoCircleDist || SquareDist21<=Threshold2PDist ||
    SquareDist41<=Threshold2PDist || SquareDist42<=Threshold2PDist) &&
    (Dist2To134>ThresholdCoCircleDist || SquareDist31<=Threshold2PDist ||
    SquareDist41<=Threshold2PDist || SquareDist43<=Threshold2PDist) &&
    (Dist1To234>ThresholdCoCircleDist || SquareDist32<=Threshold2PDist ||
    SquareDist42<=Threshold2PDist || SquareDist43<=Threshold2PDist)  )
  {   

    /* �ĥ|�I�����T�I����L�j, ��ܳo���ҧ䤧�|�I���s�b�@�ꤧ�ҩ�, 
    �W�[��|�I�����Ѧ��Ƥ@��*/
    RndCount = RndCount + 1;  
    /*��˪��|�I�����\, �ҥHTempRestNum�n�V�e���|�I*/
    TempRestNum = TempRestNum + 4; 
  }
  else /*���@�դT�I����M��4�I�ܪ�, �Y�o��i��u�O�s�b�ϤW����*/
  {
    /*�s�ŦX���󤧶�, ��M�� 4 �I�Z���̪��*/
    float MinDist=ThresholdCoCircleDist; 
    if ( Dist4To123 <= ThresholdCoCircleDist && 
        SquareDist21>Threshold2PDist &&
        SquareDist31>Threshold2PDist && SquareDist32>Threshold2PDist )
    { /*123 �T�I�@��A�h�O�U��줧��ߩM�b�|*/
      CenterX=Cx123;   
      CenterY=Cy123;
      RadiusR=Radius123;
      MinDist = Dist4To123;
    }
    
    if (Dist3To124 < MinDist  && SquareDist21>Threshold2PDist &&
        SquareDist41>Threshold2PDist && SquareDist42>Threshold2PDist )
    { /*124 �T�I�@��*/
      CenterX=Cx124; 
      CenterY=Cy124;
      RadiusR=Radius124;
      MinDist = Dist3To124;
    }
    if ( Dist2To134 < MinDist && SquareDist31>Threshold2PDist &&
         SquareDist41>Threshold2PDist && SquareDist43>Threshold2PDist )
    {/*134 �T�I�@��*/
      CenterX=Cx134;
      CenterY=Cy134;
      RadiusR=Radius134;
      MinDist = Dist2To134;
    }
if ( Dist1To234 < MinDist && SquareDist32>Threshold2PDist &&
     SquareDist42>Threshold2PDist && SquareDist43>Threshold2PDist )
{ /* 234 �T�I�@��*/
  CenterX=Cx234;
  CenterY=Cy234;
  RadiusR=Radius234;
}
CountCirclePoint=0;
/*�T�I�����@���, �~��P�_�䥦�I�O�_�����u�W�I*/
for(i = TempRestNum ; i >=1 ; i-- ) 
{
 DistToCircle = sqrt((TempEdgePoint[i].X - CenterX)*(TempEdgePoint[i].X
                        - CenterX)+(TempEdgePoint[i].Y-CenterY)*
                        (TempEdgePoint[i].Y-CenterY))- RadiusR;
 /*�D�䥦�I��ҧ��P�W���Z��, �̦��ӧP�_�o���I�O�_�b��W*/
 if (DistToCircle <0 )  
   DistToCircle = -1 * DistToCircle; 
 /*�i���ثe�o�����I�b�o��P�W*/
 if ( DistToCircle <=  ThresholdCoCircleDist ) 
 {
     CountCirclePoint = CountCirclePoint + 1;
     /*��줧�I����W�I��, ���᭱�H��ܤw�B�z���F*/
     /*����i������줧��W�I���䥦�I�M�̫᭱���I�洫*/
     SwapTemp.X = TempEdgePoint[i].X; 
     SwapTemp.Y = TempEdgePoint[i].Y;
     TempEdgePoint[i].X = TempEdgePoint[TempRestNum].X; 
     TempEdgePoint[i].Y = TempEdgePoint[TempRestNum].Y;
     TempEdgePoint[TempRestNum].X = SwapTemp.X;
     TempEdgePoint[TempRestNum].Y = SwapTemp.Y;
     TempRestNum = TempRestNum - 1; 
   } 
}
/*�n�W�L�z�׶ꤧ�I�Ƥ��Y�ʤ���~��䬰��줧��*/
if(CountCirclePoint <= 4*sqrt(2)*RadiusR*ThresholdCircleRatio/100)
{
    TempRestNum = RestEdgeNum;
    RndCount = RndCount + 1;
}
else /*�e���ҧ��ŦX�զ��u���I�ư��j�{���䬰���*/
{
    CircleData[CountCircle].CCX=CenterX;
    CircleData[CountCircle].CCY=CenterY;
    CircleData[CountCircle].Rr=RadiusR;
    CountCircle = CountCircle + 1; 
    RndCount = 0  ; 
    /*�զ��u���I�ҦV�Ჾ�F, �ҥH�̫��I��m RestEdgeNum �V�e��*/
     RestEdgeNum = TempRestNum; 
} 
} 
} 
return CountCircle;
}

		
  








	
	
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