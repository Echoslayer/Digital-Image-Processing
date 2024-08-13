// ����¼���ܧΨϥ� YUV420 �榡
#include<stdio.h>
#include<stdlib.h>


// �ŧi�ܼƤΨ禡
structParameter
{
	double focal;
	double baseline;
	double Znear;
	double Zfar;
	int height;
	int width;
	int frameNum;
	FILE *origColorMap; // �ثe������ color �ɮ�
	FILE *origDepthMap; // �ثe������ depth �ɮ�
	FILE *warpColorMap; // ���������� color �ɮ�
	// �ثe���� color �� YUV
	unsigned char **origColorY;
	unsigned char ***origColorUV;
	// �ثe���� depth �� YUV
	unsigned char **origDepthY;
	unsigned char ***origDepthUV;
	// �������� color �� YUV
	unsigned char **warpColorY;
	unsigned char ***warpColorUV;
};


// �O����ާ@�����禡�ŧi
void allocat3DMemory(unsigned char ****target, int dim1, int dim2, int dim3);
void allocat2DMemory(unsigned char ***target, int dim1, int dim2);
void free3DMemory(unsigned char ***target, int dim1, int dim2);
void free2DMemory(unsigned char **target, int dim1);
void InitMemory(Parameter *para);
void FreeMemory(Parameter *para);


//disparity �����禡�ŧi525 �� 15 ���@�T���v�����m�{
double DeQuantization(int DepthValue, double Znear, double Zfar);
double DoDisparity(double RealDistance, double Focal, double Baseline);
int Rounding(double Disparity);
int GetDisparity(int depthValue, Parameter *para);
void GenerateDisparityArray(Parameter *para, int *disparityArray);


// Ū�g YUV ���ɬ����禡�ŧi
void ReadOneFrameYUV(unsigned char **Y, unsigned char ***UV, int height, int width, FILE *file);
void WriteOneFrameYUV(unsigned char **Y, unsigned char ***UV, int height, int width, FILE *file);


// ¼���ܧά����禡�ŧi
void Warpping(Parameter *para, int *disparityArray);
void ClearWarpYUV(Parameter *para);


// �D�{��
void main(intargc, char* argv[])
{
	// �q�ѼƦC���o�����Ѽ�
	Parameter *para = (Parameter *)calloc(1, sizeof(Parameter));
	double baseline_curr;
	double baseline_target;
	int disparityArray[256];
	int frameIndex = 0, widthIndex = 0, HeightIndex = 0;
	if (argc< 12)
	{
		printf(" �ѼƤ���~~\n");
		return;
	}
	para->height = atoi(argv[1]); // �e������
	para->width = atoi(argv[2]); // �e���e��
	para->frameNum = atoi(argv[3]); // �v���i��
	baseline_curr = atof(argv[4]); // �ثe������ baseline
	baseline_target = atof(argv[5]); // ���������� baseline
	para->baseline = baseline_target - baseline_curr; // ��������� baseline �첾
	para->focal = atof(argv[6]); // ��v���J�Z
	para->Znear = atof(argv[7]); // ��v���̪�`��
	para->Zfar = atof(argv[8]); // ��v���̻��`��
	// �}���ɮ�
	para->origColorMap = fopen(argv[9], "rb");
	para->origDepthMap = fopen(argv[10], "rb");
	para->warpColorMap = fopen(argv[11], "wb");
	// ��l�Ƭ����ܼƪ��O����
	InitMemory(para);
	// �p��`�׭� 0-255 �� disparity
	GenerateDisparityArray(para, disparityArray);
	for (frameIndex = 0; frameIndex<para->frameNum; frameIndex++)
	{
		printf("Processing.....(%d/%d)\n", frameIndex, para->frameNum);
		// Ū���@�i frame
		Re adOneFrameYUV(para->origColorY, para->origColorUV, para->height,
		para->width, para->origColorMap);
		Re adOneFrameYUV(para->origDepthY, para->origDepthUV, para->height, para->width, para->origDepthMap);
		// �N�Ȧs�ϲM��
		ClearWarpYUV(para);
		// ¼���ܧΨ禡
		Warpping(para, disparityArray);
		// �g�J�@�i frame
		Wr iteOneFrameYUV(para->warpColorY, para->warpColorUV, para->height, para->width, para->warpColorMap);
	}
	// �����ɮ�
	fclose(para->origColorMap);
	fclose(para->origDepthMap);
	fclose(para->warpColorMap);
	// ����O����
	FreeMemory(para);
}


// �t�m�T���O����
void allocat3DMemory(unsigned char ****target, intdim1, intdim2, intdim3)
{
	int dim1Index, dim2Index;
		*target = (unsigned char ***)calloc(dim1, sizeof(unsigned char **));
	for (dim1Index = 0; dim1Index<dim1; dim1Index++)
	{
		(*target)[dim1Index] = (unsigned char **)calloc(dim2, sizeof(unsigned char *));
		for (dim2Index = 0; dim2Index<dim2; dim2Index++)
		{
			(*target)[dim1Index][dim2Index] = (unsigned char *)calloc(dim3, sizeof(unsigned char));
		}
	}
}


// �t�m�G���O����
void allocat2DMemory(unsigned char ***target, intdim1, intdim2)
{
	int dim1Index;
	*target = (unsigned char **)calloc(dim1, sizeof(unsigned char *));
	for (dim1Index = 0; dim1Index<dim1; dim1Index++)
		(*target)[dim1Index] = (unsigned char *)calloc(dim2, sizeof(unsigned char));
}


// ����T���O����
void free3DMemory(unsigned char ***target, intdim1, intdim2)
{
	int dim1Index, dim2Index;
	for (dim1Index = 0; dim1Index<dim1; dim1Index++)
	{
		for (dim2Index = 0; dim2Index<dim1; dim2Index++)
			free(target[dim1Index][dim2Index]);

		free(target[dim1Index]);
	}
	free(target);
}


// ����G���O����
void free2DMemory(unsigned char **target, intdim1)
{
	int dim1Index = 0, dim2Index = 0;
	for (dim1Index = 0; dim1Index<dim1; dim1Index++)
		free(target[dim1Index]);
	free(target);
}


// �t�m�O���鵹�����ܼ�
void InitMemory(Parameter *para)
{
	allocat2DMemory(&(para->origColorY), para->height, para->width);
	allocat2DMemory(&(para->warpColorY), para->height, para->width);
	allocat2DMemory(&(para->origDepthY), para->height, para->width);
	allocat3DMemory(&(para->origColorUV), 2, para->height, para->width);
	allocat3DMemory(&(para->warpColorUV), 2, para->height, para->width);
	allocat3DMemory(&(para->origDepthUV), 2, para->height, para->width);
}


// ����O����
void FreeMemory(Parameter *para)
{
	free2DMemory(para->origColorY, para->height);
	free2DMemory(para->warpColorY, para->height);
	free2DMemory(para->origDepthY, para->height);
	free3DMemory(para->origColorUV, 2, para->height);
	free3DMemory(para->warpColorUV, 2, para->height);
	free3DMemory(para->origDepthUV, 2, para->height);
}


// ��`�׭Ȥ϶q�ơA���o��ڲ`�׭�
double DeQuantization(int DepthValue, double Znear, double Zfar)
{
	double RealDistance;
	RealDistance = 1 / ((DepthValue / 255.0)*(1 / Znear - 1 / Zfar) + 1 / Zfar);
	return RealDistance;
}


// ������ڲ`�׭ȡA�p�� disparity
double DoDisparity(double RealDistance, double Focal, double Baseline)
{
	double Disparity;
	Disparity = Focal*Baseline / RealDistance;
	return Disparity;
}


// �|�ˤ��J
int Rounding(double Disparity)
{
	if (Disparity >= 0.0f)
		return ((int)(Disparity + 0.5f));

	return ((int)(Disparity - 0.5f));
}


// �����@�Ӳ`�׭ȡA��o�@�� disparity
int GetDisparity(int depthValue, Parameter *para)
{
	double realZ;
	double disparity;
	int RoundDisparity;
	realZ = DeQuantization(depthValue, para->Znear, para->Zfar);
	disparity = DoDisparity(realZ, para->focal, para->baseline);
	RoundDisparity = Rounding(disparity);
	return RoundDisparity;
}


// ���Ͳ`�׭� 0 �� 255 �� disparity
void GenerateDisparityArray(Parameter *para, int *disparityArray)
{
	int depthValue;
	for (depthValue = 0; depthValue<256; depthValue++)
		disparityArray[depthValue] = GetDisparity(depthValue, para);
}


// Ū�@�i YUV420 ����
void ReadOneFrameYUV(unsigned char **Y, unsigned char ***UV, int height,
int width, FILE *file)
{
	int heightIndex, uvIndex;
	for (heightIndex = 0; heightIndex<height; heightIndex++)
		fread(Y[heightIndex], sizeof(unsigned char), width, file);
	for (uvIndex = 0; uvIndex<2; uvIndex++)
	for (heightIndex = 0; heightIndex<height / 2; heightIndex++)
	{
		fread(UV[uvIndex][heightIndex], sizeof(unsigned char), width / 2, file);
	}
}


// �g�@�i YUV420 ����
void WriteOneFrameYUV(unsigned char **Y, unsigned char ***UV, int height,
	int width, FILE *file)
{
	int heightIndex, uvIndex;
	for (heightIndex = 0; heightIndex<height; heightIndex++)
		fwrite(Y[heightIndex], sizeof(unsigned char), width, file);
	for (uvIndex = 0; uvIndex<2; uvIndex++)
	for (heightIndex = 0; heightIndex<height / 2; heightIndex++)
	{
		fwrite(UV[uvIndex][heightIndex], sizeof(unsigned char), width / 2, file);
	}
	fflush(file);
}


// ¼���ܧε{��
void Warpping(Parameter *para, int *disparityArray)
{
	int widthIndex = 0, heightIndex = 0;
	for (heightIndex = 0; heightIndex<para->height; heightIndex++)
	for (widthIndex = 0; widthIndex<para->width; widthIndex++)
	{
		int disparity;
		// ��o�Ӳ`�׭Ȫ� disparity
		disparity = disparityArray[para->origDepthY[heightIndex][widthIndex]];
		// ��ɧP�_
		if (widthInd ex + disparity > 0 && widthIndex + disparity < para->width)
		{
			// �@��¼���ܧΡA�h��@�ɥH�̫��л\���������D
			para->warpColorY[heightIndex][widthIndex + disparity] = para->origColorY[heightIndex][widthIndex];
			para->warpColorUV[0][heightIndex / 2][(widthIndex + disparity) / 2] = para->origColorUV[0][heightIndex / 2][widthIndex / 2];
			para->warpColorUV[1][heightIndex / 2][(widthIndex + disparity) / 2] = para->origColorUV[1][heightIndex / 2][widthIndex / 2];
		}
	}
}


// �M��¼���ܼƼȦs��
void ClearWarpYUV(Parameter *para)
{
	int heightIndex, widthIndex, uvIndex;
	for (heightIndex = 0; heightIndex<para->height; heightIndex++)
	for (widthIndex = 0; widthIndex<para->width; widthIndex++)
		para->warpColorY[heightIndex][widthIndex] = 0;

	for (uvIndex = 0; uvIndex<2; uvIndex++)
	for (heightIndex = 0; heightIndex<para->height; heightIndex++)
	for (widthIndex = 0; widthIndex<para->width; widthIndex++)
	{
		// UV �L�Ȯɬ� 128
		para->warpColorUV[uvIndex][heightIndex][widthIndex] = 128;
	}
}