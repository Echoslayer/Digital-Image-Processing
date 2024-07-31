/*****************************************************************/
/**  �\��FCH_array��type�w�q**/
/**  �ѼƤ@�Fflag�Y��0�hvalue��Si��,�Y��1�h�����D�� **/
/**  �ѼƤG�Fvalue��**/
/*****************************************************************/
typedef struct ch_array{
  int flag;
  int value;
}cha;
/*******************************************************************************/ 
/**  �\��F�N�ҰҤG���r�ꪺ�ֳt�ѽX **/
/**  �ѼƤ@�Fd��**/
/**  �ѼƤG�F��J��Huffman array**/
/**  �ѼƤT�F��J��CH array**/
/*******************************************************************************/

int Huffman_Decode(int d_prom,int *Huf_array,cha *CH_array)
{
  int i,j,code_ptr=0,array_ptr;
  /*��l��code_ptr*/
  code_ptr=d_prom;
  /*��l��array_ptr*/
  for(i=0;i<d_prom;i++)
    array_ptr=array_ptr+2*Huf_array[i];
  /*�ѽX�j��*/
  while(CH_array[array_ptr].flag!=0){
    array_ptr=array_ptr+CH_array[array_ptr].value;
    /*���V���Ĥl*/
    if(Huff_array[code_ptr]!=0)
      array_ptr++;
      /*�Y�X=��1��,�h���V�k�Ĥl*/
      code_ptr++;
    /*���V�U�@�줸*/
  }
  return CH_array[array_ptr].value;
}