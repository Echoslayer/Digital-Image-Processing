/*******************************************************/
/*���{�����Ƕ��v����S�𪺵{���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*�����ϥΪ̥����۳]����n�B�~�t��th�B�H�Τ��\���~�t��cntlim*/
/*�b�B�zblock���L�{���A�ڭ̥��D�Xblock�|�Ө��I�A�@�@�@�@�@�@*/
/*�Ƕ��Ȭ۴��A������ȡA�@���j��~�t�ȫh�֥[��ӼơF�@�@�@*/
/*�M��Q�Υ|�Ө��I�Ƕ��Ȱ������A�ұo�줺���v���P��l�v�����@*/
/*�p�G�j��~�t�Ȫ��ӼƶW�L�w�]���~�t��( cntlim)�ɡA�h�i����ΡC*/
/*���U�ӨD����Ϋ�lblock ���|�Ө��I�A�í��ФW��B�J�C�@�@�@*/
/*******************************************************/

void find(int ii,int jj,int kk) 
{ 
  int ib,jb,kb,ic,jc,kc,kd; 
  int id,jd,fg,cnt;
  float x1, xa, ya, g5, g6, g7, g8, g12, g34;
  int g1,g2,g3,g4;
  cnt=0;
  /*�ѥ��W���I(ii,jj)�H�Υثe���h��kk�A�i�H�D��X
  ���U���I(ic,jj)�B�k�W���I(ii,jc)�B�k�U���I(ic,jc)����m*/ 
  kc=1<<((int) (kk+1)/2); 
  kd=1<<((int) kk/2);
  ic=ii+ma/kc;
  jc=jj+ma/kd;
  id=ii;
  fg=0;
  x1=(float) ic-ii;
  /*�I���|�Ө��I���Ƕ���*/
  g1=(int) greyc[ii][jj] & 0xff;
  g2=(int) greyc[ic][jj] & 0xff;
  g3=(int) greyc[ii][jc] & 0xff;
  g4=(int) greyc[ic][jc] & 0xff;
  g12=(float) (g2-g1)/x1;
  g34=(float) (g4-g3)/x1;
  if((jc-jj)>1)
  {
    while(id<=ic && fg==0)
    {
      /*�ھ�block���|�Ө��I���Ƕ��Ȱ�����*/
      xa=(float)(id-ii);   
      g5=(float) g1+g12*xa;
      g6=(float) g3+g34*xa;
      g8=(float)(g6-g5)/(jc-jj);
      jd=jj;
      while(jd<=jc && fg==0)
      {
        g7=g5+g8*(jd-jj);
        if(abs(g7-(((int) greyc[id][jd])&0xff))>TH)
        {
          /*******************************************/
          /*g7 �������X�Ӫ���                        */
          /*�����X���ȻP��Ϫ��Ƕ��Ȭ۴��������   */
          /*�p�G�j��~�t�ȡA�hcnt++�A                */
	  /*�@��cnt�j��cntlim�A�h�n���ΡAfg�]�� 1    */
	  /*******************************************/
	  if(cnt<CNTLIM)
	    cnt++;  
          else
            fg=1;
        }
	jd++;
      }
      id++;
    }
  }
  if(fg==0)
  {
    /*�p�G���ݤ��ΡA�h��Xblock�|�Ө��I��*/
    fprintf(fp1,"%d %d %d %d %d %d %d\n",
    ii+xlow,jj+ylow,kk+la,(int) greyc[ii][jj] & 0xff,
    (int) greyc[ic][jj] & 0xff,(int) greyc[ii][jc] & 0xff,
    (int) greyc[ic][jc] & 0xff);
    num++;
    if((kk+la)==(2*n))
      num1++;
  }
  else            
  { 
    /*�_�h�A�ϥλ��j�覡�~�����*/
    ib=ii;
    jb=jj;
    kb=kk+1;
    find(ib,jb,kb);
    if((kb&1)==1)
    {
      ib=ii+ma/kc/2;
    }
    else
    {
      jb=jj+ma/kd/2;
    }
    find(ib,jb,kb);
  }
}