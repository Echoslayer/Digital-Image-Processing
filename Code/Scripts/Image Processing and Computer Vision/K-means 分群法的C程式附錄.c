/****************************************************************/
/* �\��G�N�¥ռv��Image�A����K�s�A���G�x�s��Cluster��     */
/* �ѼƤ@�G��l�¥ռv��Image                                */
/* �ѼƤG�G���s�����GCluster                                 */
/* �ѼƤT�G����K�s                                         */
/****************************************************************/

void k_means(int Image[M][N], int cluster[M][N], int K)
{
/* Dis:�p���@�I��s�ߪ��Z�� */
/* Min:�p���@�I��U�Ӹs�ߪ��Z�������̤p�� */
/* Dm:�������u�� */
/* Dn:�e�@�^�X���������u�� */
/* Error:���u�{�ɭ� */
/* Cents:�s��U�Ӹs�ߪ��y�� */
/* NCP:�@�s�ҥ]�t���I�� */
/* EN:�Ҧ��I���`�M */

    
  int i, j, k;
  int **Cents, **tmpcts, *NCP, **data_points;
  long double Error, Dm, Dn, Min, EN, Dis, *lmindis;
            
  /* �p��Ҧ��I�� */
  EN = 0;
  for(i = 0; i < M; i++){
    for(j = 0; j < N; j++){
        if(Image[i][j] == 1)
            EN++;
    }
  }

  /* �ŧi�}�Cdata_points�A�ΥH�x�s�Ҧ��I����m�y�� */
  data_points = new int * [EN];
  for(I = 0; I < EN; i++)
      data_points[i] = new int [2];

  /* �O���Ҧ��I����m�A�s��}�Cdata_points�� */
  int z;
  z = 0;
  for(i = 0; i < M; i++){
    for(j = 0; j < N; j++){
        if(Image[i][j] == 1){
            data_points[z][0] = i;
            data_points[z][1] = j;

            z++;
        }
    }
  }

  /* �ŧi�}�CCents�A�ΥH�x�s�s�ߪ���m�y�� */
  /* �ŧi�}�Ctmpcts�A�ΥH�x�s�Ӹs�ҥ]�t���I���y�Ъ��[�` */
  Cents = new int * [K + 1];   
  tmpcts = new int * [K + 1];
  for(int i = 1; i <= K; i++){
      Cents[i] = new int [2];
      tmpcts[i] = new int [2];
  }           

  /* �q�Ҧ��I������K���I�@����l�s�ߡA�æs��}�CCents�� */
  int v;
  randomize();
  for(i = 1; i <= K; i++){
      v = random(K);

      Cents[i][0] = data_points[v][0];
      Cents[i][1] = data_points[v][1];
  }
    
  /* �ŧi�}�CNCP�A�ΥH�x�s�U�s�ҥ]�t���I�ƩM */
  NCP = new int [K+1];
    
  /* �ŧi�}�Clmindis�A�Τw�x�s�U�s�����u�� */
  lmindis = new long double [K + 1];
      
  Dm = 0x7fffffff;   /* Dm:��l�Ȭ��L���j */
  Error = 0.005;
      
  do{
      /* �N�һݰѼ��k�s */
      for(i = 1; i <= K; i++){
          lmindis[i] = 0;

          tmpcts[i][0] = 0;
          tmpcts[i][1] = 0;
          NCP[i] = 0;
      }
        
      /* �p���@�I�P�U�s�ߪ��Z���A�N���I���t���P���Z���̪񤧸s�� */
      for(I = 0; I < M; i++){
        for(j = 0; j < N; j++){
            if(Image[i][j] == 1){
                //����Z���A����
                min = 0x7fffffff;
                for(k = 1; k <= K; k++){
                    Dis = sqrt((I - Cents[k][0])*( I -Cents[k][0])+( j -Cents[k][1])*(                           j -Cents[k][1]))

                    if(Min > Dis){
                        Min = Dis;
                        Cluster[i][j] = k;
                    }
                }
                  
                /* �p��s�ߨ�Ӹs�U�I���Z���M(��@�s�����u��) */
                T = Cluster[i][j];
                  
                NCP[T]++;
                lmindis[T] += Min;
                  
                tmpcts[T][0] += i;
                tmpcts[T][1] += j;
            }
        }
      }
    
      /* �D�X�s���s��(mean) */ 
      for(i = 1; i <= K; i++){
          if(NCP[i] > 0){   /* �i�঳�@�s�S��������I */
             Cents[i][0] = tmpcts[i][0]/NCP[i];
             Cents[i][1] = tmpcts[i][1]/NCP[i];
          }
      }

      /* Dm:�������u�� */
      /* Dn:�e�@�����������u�� */
      /* Error:���u�{�ɭ� */
      Dn = Dm;
      Dm = 0;
      for(i = 1; i <= K; i++)
          Dm += lmindis[i];

      Dm/=EN;        
  }while( ((Dn - Dm)/Dm) > Error );
}