/************************************************************************************************/
/*�{����OriginalImg����J���Ƕ��v��																*/
/*EdgeImg����X������x�}��̤j�p�Ҭ�M X N														*/
/*�䤤M�MN���v�������M�e																		*/
/************************************************************************************************/
void Marr_Hildreth(int OriginalImg[M][N], int EdgeImg[M][N])
{
	int i,j,k;
	int PixelCounter = 0, TH;
	float TmpSum;
	int TempImg[M][N];
	
	for(i=2;i<M-2;i++)
	{
		for(j=2;j<N-2;j++)
		{
			/*�a�J�p��(3.3.4)���Y�Ʀܿ�J���Ƕ��v�T�p��*/
			TempImg[i][j]=OriginalImg[i][j]*16-OriginalImg[i][j-1]*2
			-OriginalImg[i][j+1]*2-OriginalImg[i-1][j]*2
			-OriginalImg[i+1][j]*2-OriginalImg[i-1][j-1]*2
			-OriginalImg[i-1][j+1]*2-OriginalImg[i+1][j-1]*2
			-OriginalImg[i+1][j+1]*2-OriginalImg[i][j-2]*2
			-OriginalImg[i][j+2]*2-OriginalImg[i-2][j]*2
			-OriginalImg[i+2][j];
		}
	}
	/*�p��Zero Crossing���{�ɭ�*/
	TmpSum=0;
	for(i=1;i<M-1;i++)
	{
		for(j=1;j<N-1;j++)
		{
			PixelCounter++;
			TmpSum=TmpSum+abs(TempImg[i][j]);
		}
	}
	TH=2*(TmpSum/PixelCounter);
	for(i=0;i<M-2;i++)
	{
		for(j=0;j<N-2;j++)
		{
			/*��X�q�L�{���I����*/
			EdgeImg[i+1][j+1]=255;/*�N�v���]�����I*/
			
			/*���I�j��s�B�k�I�p��s�A�B���k���I���t�j���{�ɭ�
			�h���I�����I�A��ȳ]�����I*/
			if(((TempImg[i][j+1]>=0)&&(TempImg[i+2][j+1]<=0))
			&&((TempImg[i][j+1]-TempImg[i+2][j+1])>=TH))
			{
				EdgeImg[i+1][j+1]=0;
				continue;
			}
			
			/*���I�p��s�B�k�I�j��s�A�B���k���I���t�j���{�ɭ�
			�h���I�����I�A��ȳ]�����I*/
			if(((TempImg[i][j+1]<=0)&&(TempImg[i+2][j+1]>=0))
			&&((TempImg[i+2][j+1]-TempImg[i][j+1])>=TH))
			{
				EdgeImg[i+1][j+1]=0;
				continue;
			}
			
			/*��W�I�j��s�B�U�I�p��s�A�B�W�U���I���t�j���{�ɭ�
			�h���I�����I�A��ȳ]�����I*/
			if(((TempImg[i+1][j]>=0)&&(TempImg[i+1][j+2]<=0))
			&&((TempImg[i+1][j]-TempImg[i+1][j+2])>=TH))
			{
				EdgeImg[i+1][j+1]=0;
				continue;
			}
			
			/*��W�I�p��s�B�U�I�j��s�A�B�W�U���I���t�j���{�ɭ�
			�h���I�����I�A��ȳ]�����I*/
			if(((TempImg[i+1][j]<=0)&&(TempImg[i+1][j+2]>=0))
			&&((TempImg[i+1][j+2]-TempImg[i+1][j])>=TH))
			{
				EdgeImg[i+1][j+1]=0;
				continue;
			}
		}
	}
}