�۾��~���ѼƨD�Ѫ�C�{������
/****************************************************************/
/* structure calipoint                                          */
/* Xw,Yw,Zw : �@�ɮy��(mm)                                      */
/* Xd,Yd : �v���y��(pixel)                                      */
/****************************************************************/

struct calipoint{
  double Xw,Yw,Zw;
  float Xd,Yd;
} CALIPOINT;

/**********************************************************************/
/* function ftk_funcs                                                 */
/* y(x;a)= -Yi*f+(-Ydi)*T_z_(wi*Ydi*r^2)*kuppa_1+(Ydi*r^2)*T_z*kuppa_1*/
/* input -                                                            */
/* x : ��x��calipoint	                                              */
/* a[] : �ثe���Ѽƭ�                                                 */
/* na : �ѼƭӼ�                                                      */
/* ouput -                                                            */
/* y : �ثe����ƭ�                                                   */
/* dyda : �ثe�禡y(x;a)��C�@��a[]�����L����                         */
/**********************************************************************/
void ftk_funcs(float x,float a[],float *y,float dyda[],int na)
{
  /* y(x;a)=                                                    */
  /* -Yi*f+(-Ydi)*T_z_(wi*Ydi*r^2)*kuppa_1+(Ydi*r^2)*T_z*kuppa_1*/
  double yi,wi,r_sq;
  calipoint *i=&data_set[x];
  yi=Extri_R[4]*i->Xw+Extri_R[5]*i->Yw+T_y;
  wi=Extri_R[1]*i->Xw+Extri_R[8]*i->Yw;
  r_sq=i->Xd*i->Xd+i->Yd*i->Yd;
  *y=(-1)*yi*a[1]+i->Yd*a[2]+wi*i->Yd*r_sq*a[3]+i->Yd*r_sq*a[2]*a[3];
  dyda[1]=(-1)*yi;
  dyda[2]=i->Yd*(1+r_sq*a[3]);
  dyda[3]=i->Yd*r_sq*(wi+a[2]);
}

/*************************************************************************************/
/* function MonoviewCoplanarSetofPoints                                              */
/* Input-                                                                            */  
/* data_set : calibration points                                                     */
/* Output-                                                                           */
/* R_x,R_y,R_z : �~���ѼƤ����ਤ��                                                  */
/* T_x,T_y,T_z : �~���ѼƤ������V�q                                                  */
/*                                                                                   */
/* �䤤                                                                              */
/*-Guass-Jordan Elimination                                                          */
/* void gaussj(float **a,int n,float **b,int m)                    	             */
/*-Levenberg-Marquardt Method                                                        */
/* void mrqmin(float x[],float y[],float sig[],int ndata,float a[],int ia[],         */
/*           int ma,float **covar,float **alpha,float *chisq,	                     */
/*           void (*funcs)(float,float [],float *,float [],int),float *alamda)       */
/* ���~���Ƶ{��,�аѦ�NUMERICAL RECIPES in C, SECOND EDITION                         */
/*************************************************************************************/
void MonoviewCoplanarSetofPoints(vector<calipoint> data_set,
  double* R_x,double* R_y,double* R_z,
  double* T_x,double* T_y,double* T_z)
{
  /*��l�Ѽ�*/
  R_x=R_y=R_z=0.0;
  T_x=T_y=T_z=0.0;
  double Intri_f=0.0;
  double Intri_kappa1=0.0;
  /*�bcoplanar����k��,Sx�]��1*/
  double Intri_Sx=1.0;               
/* �Ĥ@���q -- �p��3D���첾�α���*/
  /*��1�B : �p��5�ӥ�����T^-1_y*r_1, T^-1_y*r_2,T^-1_y*T_x,*/
  /*                     T^-1_y*r_4, and T^-1_y*r_5.       */
  float **a,**b;
  a=new float*[6];
  for(int i=0;i<6;i++) a[i]=new float[6];
  b=new float*[6];
  for(int i=0;i<6;i++) b[i]=new float[2];

  vector<calipoint>::iterator i;
  float coff[1];
  for( i=data_set.begin();i<data_set.end();i++ ){
    /*Normal equations*/
    coff[1]=i->Yd*i->Xw;
    coff[2]=i->Yd*i->Yw;
    coff[3]=i->Yd;
    coff[4]=(-1)*i->Xd*i->Xw;
    coff[5]=(-1)*i->Xd*i->Yw;
    coff[6]=i->Xd;
    for(int k=1;k<=5;k++){
      a[k][1]+=coff[1]*coff[k]; a[k][2]+=coff[2]*coff[k];
      a[k][3]+=coff[3]*coff[k]; a[k][4]+=coff[4]*coff[k];
      a[k][5]+=coff[5]*coff[k]; b[k][1]+=i->Xd*coff[k];
    }
  }
  /*�Q��Guass-Jordan Elimination�k�Ѥ�*/
  gaussj(a,5,b,1);
  /*b�O������*/
  /*��2�B : �p��r_1,...,r_9*/
  /*��2.1�B : �p��T_y^2*/
  /*C=[ r_1' r_2' ]*/
  /*  [ r_4' r_5' ]*/
  float pr_1=b[1][1]; float pr_2=b[2][1];
  float pr_3=b[3][1]; float pr_4=b[4][1];
  float pr_5=b[5][1];
  double Sr=pr_1*pr_1+pr_2*pr_2+pr_4*pr_4+pr_5*pr_5;
  double square_Ty;
  if( !(pr_1 == 0 && pr_2 == 0) || !(pr_1 == 0 && pr_4 == 0) ||
      !(pr_2 == 0 && pr_5 == 0) || !(pr_4 == 0 && pr_5 == 0))
  {
    square_Ty=(Sr-sqrt(Sr*Sr-4*pow(pr_1*pr_5-pr_4*pr_2,2)))/
              (2*pow(pr_1*pr_5-pr_4*pr_2,2));
  }
  else{
    if(pr_1 == 0 && pr_2 == 0) square_Ty=1/(pr_4*pr_4+pr_5*pr_5);
    if(pr_1 == 0 && pr_4 == 0) square_Ty=1/(pr_2*pr_2+pr_5*pr_5);
    if(pr_2 == 0 && pr_5 == 0) square_Ty=1/(pr_1*pr_1+pr_4*pr_4);
    if(pr_4 == 0 && pr_5 == 0) square_Ty=1/(pr_1*pr_1+pr_2*pr_2);
  }
  T_y=sqrt(square_Ty);

  /*��2.2�B : �M�wTy�����t��*/
  /*����@�IP*/ 
  vector<calipoint>::iterator P=data_set.end()-1;
  /*�����]����*/
  int sign_of_Ty=1;
  Extri_R[1]=pr_1*T_y;
  Extri_R[2]=pr_2*T_y;
  Extri_R[4]=pr_4*T_y;
  Extri_R[5]=pr_5*T_y;
  T_x=pr_3*T_y;
  float xx=Extri_R[1]*P->Xw+Extri_R[2]*P->Yw+T_x;
  float yy=Extri_R[4]*P->Xw+Extri_R[5]*P->Yw+T_y;
  if( (xx*P->Xd >= 0.0) || (yy*P->Yd >=0.0) ){
    sign_of_Ty=1;
  }
  else{
    sign_of_Ty=-1;
  }
  T_y*=sign_of_Ty;

  /*��2.3�B : �p��3D����x�}*/
  Extri_R[1]=pr_1*T_y;
  Extri_R[2]=pr_2*T_y;
  Extri_R[4]=pr_4*T_y;
  Extri_R[5]=pr_5*T_y;
  T_x=pr_3*T_y;

  int sign=(-1)*(Extri_R[1]*Extri_R[4]+Extri_R[2]*Extri_R[5]>0?1:-1);
  Extri_R[3]=sqrt(1-Extri_R[1]*Extri_R[1]-Extri_R[2]*Extri_R[2]);
  Extri_R[6]=sign*sqrt(1-Extri_R[4]*Extri_R[4]-Extri_R[5]*Extri_R[5]);
  Extri_R[1]=sqrt(1-Extri_R[1]*Extri_R[1]-Extri_R[4]*Extri_R[4]);
  Extri_R[8]=sqrt(1-Extri_R[2]*Extri_R[2]-Extri_R[5]*Extri_R[5]);
  Extri_R[2]=sqrt(1-Extri_R[1]*Extri_R[1]-Extri_R[8]*Extri_R[8]);

/*�ĤG���q -- �p��J�Z��,���u�Y��,��z��V�������q*/
  /*��3�B : �p��f��Tz�����p�Ȧb�������Y���u�����p�U*/

  float yi,wi;
  for(i=data_set.begin();i<data_set.end();i++ ){
    // Normal equations
    yi=Extri_R[4]*i->Xw+Extri_R[5]*i->Yw+T_y;
    wi=Extri_R[1]*i->Xw+Extri_R[8]*i->Yw;
    coff[1]=yi;
    coff[2]=-1*i->Yd;
    for(int k=1;k<=2;k++){
      a[k][1]+=yi*coff[k];
      a[k][2]+=-1*i->Yd*coff[k];
      b[k][1]+=wi*i->Yd*coff[k];
    }
  }
  gaussj(a,2,b,1);
  Intri_f=b[1][1];
  T_z=b[2][1];

  /*�Yf<0,���s�p�����x�}*/
  while(Intri_f <= 0.0){
    if(Intri_f < 0.0){
      Intri_f*=-1;
      Extri_R[3]*=-1;
      Extri_R[6]*=-1;
      Extri_R[1]*=-1;
      Extri_R[8]*=-1;
    }
    for(i=data_set.begin();i<data_set.end();i++ ){
      /*Normal equations*/
      yi=Extri_R[4]*i->Xw+Extri_R[5]*i->Yw+T_y;
      wi=Extri_R[1]*i->Xw+Extri_R[8]*i->Yw;
      coff[1]=yi;
      coff[2]=-1*i->Yd;
      for(int k=1;k<=2;k++){
        a[k][1]+=yi*coff[k];
        a[k][2]+=-1*i->Yd*coff[k];
        b[k][1]+=wi*i->Yd*coff[k];
      }
    }
    gaussj(a,2,b,1);
    Intri_f=b[1][1];
    T_z=b[2][1];
  }
  /*�p��R_x,R_y,R_z*/
  R_z=atan(Extri_R[2]/Extri_R[1]);
  R_y=acos(Extri_R[2]/sin(R_z));
  R_x=asin(Extri_R[6]/cos(R_y));

  /*��4�B : �p��T�ꪺf,T_z,kuppa_1*/        
  int ndata=data_set.size();
  float *x=new float[ndata+1];
  float *y=new float[ndata+1];
  float *sig=new float[ndata+1];
  float *p=new float[4];
  p[1]=Intri_f;
  p[2]=T_z;
  p[3]=0.0;
  int *ia=new int[4];
  for(int i=1;i<4;i++) ia[i]=1;
  float **covar,**alpha;
  covar=new float*[4];
  alpha=new float*[4];
  for(int i=0;i<4;i++){
    covar[i]=new float[4];
    alpha[i]=new float[4];
  }
  float chisq,alamda=-1;
  for(int i=0;i<=ndata;i++){
    float wi=Extri_R[1]*data_set[i].Xw+Extri_R[8]*data_set[i].Yw;
    x[i+1]=i;
    y[i+1]=-1*wi*data_set[i].Yd;
    float mean=(data_set[i].Xw+data_set[i].Yw+
                data_set[i].Xd+data_set[i].Yd)/5;
    float var=(pow(data_set[i].Xw-mean,2)+pow(data_set[i].Yw-mean,2)+
               pow(data_set[i].Xd-mean,2)+pow(data_set[i].Yd-mean,2))/4;
    sig[i+1]=sqrt(var);
  }
  mrqmin(x,y,sig,ndata,p,ia,3,covar,alpha,&chisq,&ftk_funcs,&alamda);
  
  Intri_f=p[1];
  T_z=p[2];
  Intri_kappa1=p[3];

  /*����O����*/
  for(int i=0;i<4;i++){
    delete [] covar[i];
    delete [] alpha[i];
  }
  delete [] covar,alpha,ia,p,sig,y,x;
  delete [] p;
  for(int i=0;i<6;i++)
    delete [] a[i];
  delete [] a;
  for(int i=0;i<6;i++)
    delete [] b[i];
  delete [] b;
}