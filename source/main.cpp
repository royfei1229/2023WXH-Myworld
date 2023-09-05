#include "../include/TunnelDeamon.h"

int main(int argc, char * argv[])
{
    TRACE();

	/* ��ʼ���ػ����� */
    if (InitDeamon() == -1)
    {
        PRINT(2, "InitDeamon = -1");
        exit(-1);
    }
	/* �������ģ�� */
    if (InitTunnel() == -1)
    {
        PRINT(2, "TunnelStartt = -1");
        exit(-1);
    }
	/* ��װ�źŴ����� */
    if (SetSignal() == -1)
    {
        PRINT(2, "SetSignal = -1");
       	TunnelStop();
        exit(-1);
    }
    
	PRINT(0, "pause");

    while (1)
    {
        pause();	/* ������߳� */
    }

   	TunnelStop();
    return 0;
}
