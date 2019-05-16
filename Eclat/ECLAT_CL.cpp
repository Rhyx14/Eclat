#include "ECLAT.h"
using namespace std;
int ECLAT::CL_Process()
{
	cl_factory.Init(cl_factory.platforms[0]);
	cl_factory.Load("../kernal.txt");
	cl_factory.Complie();
	cl_factory.CreateBuffer(this->Item_Count, this->T_Count);
	while (true)
	{
		if (UsingA) {
			int cnt = Buffer_A.size();
			if (cnt == 0)break;
			_CL_ProcessA(Buffer_A, Buffer_B, cnt);
		}
		else {
			int cnt = Buffer_B.size();
			if (cnt == 0)break;
			_CL_ProcessA(Buffer_B, Buffer_A, cnt);
		}
		UsingA = !UsingA;
	}
	return 0;
}
void ECLAT::_CL_ProcessA(vector<Column> &source, vector<Column> &destination, int cnt)
{
	ClearBuffer(destination);
	for (int i = 0; i < cnt; i++) {
		cl_factory.WriteBufferA(source[i].Item_Array, source[i].T_Array);

		int j = i + 1;
		while(j < cnt)
		{
			int k = 0;
			if (j<cnt &&
				source[i].CanIntersectWith(source[j], this->Item_Count)) 
			{
				int _param[3] = { 0,this->Item_Count,this->T_Count };
				cl_factory.WriteBuffer(0, source[j].Item_Array, source[j].T_Array,_param);
				cl_factory.SetParamAndEnqueue(0);	
				k++;
			}
			j++;
			if (j < cnt &&
				source[i].CanIntersectWith(source[j], this->Item_Count))
			{
				int _param[3] = { 0,this->Item_Count,this->T_Count };
				cl_factory.WriteBuffer(1, source[j].Item_Array, source[j].T_Array, _param);
				cl_factory.SetParamAndEnqueue(1);			
				k++;
			}
			j++;
			if (j < cnt &&
				source[i].CanIntersectWith(source[j], this->Item_Count))
			{
				int _param[3] = { 0,this->Item_Count,this->T_Count };
				cl_factory.WriteBuffer(2, source[j].Item_Array, source[j].T_Array, _param);
				cl_factory.SetParamAndEnqueue(2);
				k++;
			}
			j++;
			if (j < cnt &&
				source[i].CanIntersectWith(source[j], this->Item_Count))
			{
				int _param[3] = { 0,this->Item_Count,this->T_Count };
				cl_factory.WriteBuffer(3, source[j].Item_Array, source[j].T_Array, _param);
				cl_factory.SetParamAndEnqueue(3);
				k++;
			}
			j++;
			cl_factory.ReadResult(destination,
								this->Threshold,
								this->Item_Count,
								this->T_Count,
								k);
		}
	}
	printf("Turn#:\n");
	Display(destination);
}
int ECLAT::CL_Intersect(Column & col1, Column & col2, Column & dest)
{
	return 0;
}