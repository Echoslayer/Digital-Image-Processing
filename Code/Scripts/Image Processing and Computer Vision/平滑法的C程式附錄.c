/************************************************************/
/**  �\��G�Q�Υ��ƪk�ӧﵽ�v�����~��                      **/
/**  �ѼƤ@�G��l�v�����Ȧs��                              **/
/**  �ѼƤG�G�g�ѥ��ƪk�B��᪺���G�v�����Ȧs��            **/
/**  �ѼƤT�G��l�v������                                  **/
/**  �Ѽƥ|�G��l�v�����e                                  **/
/**  �ѼƤ��G���n�j�p(�ҡG3:���3��3�B5:���5��5�B7:���7��7) **/
/************************************************************/

void MeanFilter(unsigned char **arg_imgsrc_buf, unsigned char **arg_imgresult_buf, int arg_img_h, int arg_img_w, int arg_masksize)
{
  float meangray;
  int weightsum;

  /* weightsum��b���n���`�@�v�� */
  weightsum = arg_masksize * arg_masksize; 
  
  for(int y=0;y<arg_img_h-2;y++)
    for(int x=0;x<arg_img_w-2;x++)
    {
      meangray = 0;  /* ��l�s��g�ѥ��ƪk�B�⵲�G���ܼ� */
      
      /* ���ƪk�B��D�� */
      for(int i=y;i<arg_masksize+y;i++)
        for(int j=x;j<arg_masksize+x;j++)
          meangray = meangray + (float)(arg_imgsrc_buf[i][j] /weightsum);

      /* �N�g�ѥ��ƪk�B��ᤧ���G�s�^���G�v���Ȧs�� */
      arg_imgresult_buf[y+1][x+1] = meangray;
    }
}