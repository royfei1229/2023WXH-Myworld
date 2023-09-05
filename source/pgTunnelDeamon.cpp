#include "../include/TunnelDeamon.h"

/**
 * ��������ʼ���ػ�����
 *
 * ����ֵ���ɹ�����0��ʧ�ܷ�0
 */
int InitDeamon(void)
{
	TRACE();

	struct rlimit rl;

	/* ��ȡ������Դ�������ر��ļ������� */
	if (getrlimit(RLIMIT_NOFILE, &rl) == -1)
	{
		PRINT(2, "getrlimit = -1");
		return -1;
	}

	/* ��shellִ���������� */
	pid_t pid = fork();
	if (pid == -1)
	{
		PRINT(2, "fork = -1, errno = %d", errno);
		return -1;
	}
	else if (pid > 0)
	{
		exit(0);
	}
	
	/* �����Ự */
	if (setsid() == -1)
	{
		PRINT(2, "setsid = -1, errno = %d", errno);
		return -1;
	}

	/* SIGHUP�ź�����Ϊ���� */
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) == -1)
	{
		PRINT(2, "sigaction = -1, errno = %d", errno);
		return -1;
	}
	
	/* ���ӽ��̲���Ϊ�������鳤 */
	if ((pid = fork()) == -1)
	{
		PRINT(2, "fork = -1, errno = %d", errno);
		return -1;
	}
	else if (pid > 0)
	{
		exit(0);
	}
	
	/* ���ý��̴����ļ������� */
	umask(0);

	/* �رղ���Ҫ���ļ������� */
	if (rl.rlim_max == RLIM_INFINITY)
	{
		rl.rlim_max = 1024;
	}
	for (int i = 0, fd = fileno(change::trace.GetTraceFile()); i < rl.rlim_max; ++i)
	{
		if (i != fd)
		{
			close(i);
		}
	}
	
	/* ����ǰĿ¼�ƶ�����Ŀ¼, ���ó��򴴽��ļ� 
	if (chdir("/") == -1)
	{
		PRINT(1, "chdir = -1");
	}*/

	/* ��/dev/null�ļ���Ϊ��׼������� */
	int in_fd, out_fd, err_fd;
	in_fd = open("/dev/null", O_RDONLY);
	out_fd = dup(in_fd);
	err_fd = dup(in_fd);
	if (in_fd != 0 || out_fd != 1 || err_fd != 2)
	{
		PRINT(1, "in_fd != 0, out_fd != 1, err_fd != 2");
	}
	return 0;
}

/**
 * ��������ȡMAC��ַ
 *
 * macaddr[out]: ����MAC��ַ�Ļ�����
 *
 * size[in]: ��������С
 *
 * ����ֵ���ɹ����ػ�������ʧ��NULL
 */
char * GetMacAddr(char * macaddr, unsigned size)
{
	TRACE();

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		PRINT(2, "socket = -1");
		return NULL;
	}

	struct ifconf ifc;
	struct ifreq buf[DEAMON_MAC_MAX];
	ifc.ifc_len = sizeof buf;
	ifc.ifc_buf = (caddr_t)buf;

	if (ioctl(fd, SIOCGIFCONF, (char *)&ifc) == -1)
	{
		PRINT(2, "ioctl = -1");
		close(fd);
		return NULL;
	}

	int j = 0;
	unsigned char c;
	int mac_num = ifc.ifc_len / sizeof (struct ifreq);

	while (mac_num > 0)
	{
		--mac_num;
		if (ioctl(fd, SIOCGIFHWADDR, (char *)&buf[mac_num]) == -1)
		{
			PRINT(2, "ioctl = -1, mac_num = %d", mac_num);
			close(fd);
			return NULL;
		}

		for (int i = 0; i < 6 && j < size - 1; ++i)
		{
			c = (unsigned char)buf[mac_num].ifr_hwaddr.sa_data[i];
			sprintf(macaddr + j, "%02x-", c);
			j += 3;
		}
		if (j > 0)
		{
			macaddr[j - 1] = ',';
		}
	}
	if (j > 0)
	{
		macaddr[j - 1] = 0;
	}

	PRINT(0, macaddr);
	close(fd);
	return macaddr;
}

/**
 * ��������־����
 *
 * level[in]: ��־����
 *
 * output[in]: ��־�����Ϣ
 */
void LogOutPut(unsigned level, const char * output) {}

/**
 * ��������ȡ���޸ĵ������ļ�����
 *
 * info[out]: ���������ļ����ݵĻ�����
 *
 * size[in]: ��������С
 *
 * ����ֵ���ɹ����������ļ����ݣ�ʧ��NULL
 */
char * GetFileInfo(char * info, unsigned size)
{
	TRACE();

	int fd = open(DEAMON_INFO_FILE, O_RDONLY);
	if (fd == -1)
	{
		PRINT(2, "open = -1");
		return NULL;
	}

	int bitys = read(fd, info, size - 1);
	if (bitys == -1)
	{
		PRINT(2, "read = -1");
		close(fd);
		return NULL;
	}
	close(fd);
	info[bitys] = 0;

	PRINT(0, info);
	return info;
}

/**
 * ��������ȡһ���ı���ǰ��ǿյ��ַ�
 *
 * dest[out]: �����ַ����Ļ�����
 *
 * size[in]: ��������С
 *
 * source[in]: �ı��ַ���
 *
 * ����ֵ�����ػ�������ַ
 */
char * StrGetLine(char * dest, unsigned size, const char * source)
{
	TRACE();

	char c;
	int i = 0;
	int j = 0;

	/* ֱ��һ�зǿ��ַ�������ѭ�� */
	for (; source[i] != 0; ++i)
	{
		c = source[i];
		if (c == '\n')
		{
			dest[0] = 0;
			return dest;
		}
		if (c != ' ' && c != '\t')
		{
			break;
		}
	}

	/* ����һ���ַ��� */
	for (; source[i] != 0 && j < size - 1; ++i, ++j)
	{
		c = source[i];
		if (c == '\n')
		{
			break;
		}
		dest[j] = c;
	}
	dest[j] = 0;

	/* �ҵ��ַ������һ���ǿ��ַ� */
	for (; j > 0; )
	{
		j -= 1;
		if (isspace(dest[j]) == 0)
		{
			dest[j + 1] = 0;
			break;
		}
	}

	PRINT(0, dest);
	return dest;
}

/**
 * ��������ȡ����������
 *
 * buffer[out]: ������
 *
 * size[in]: ��������С
 *
 * info[in]: ������Ϣ
 *
 * sign[in]: ������
 *
 * ����ֵ���ɹ����ػ�������ַ��ʧ��NULL
 */
char * GetInfoLine(char * buffer, unsigned size, const char * info, const char * sign)
{
	TRACE();

	if ((info = strstr(info, sign)) == NULL)
	{
		PRINT(2, "strstr = NULL");
		return NULL;
	}
	return StrGetLine(buffer, size, info + strlen(sign));
}

/**
 * ����������������Ϣ
 *
 * info[in]: ���޸ĵ�������Ϣ
 *
 * ����ֵ[free]���ɹ�����������������Ϣ��ʧ��NULL
 */
char * CreateSysInfo(const char * info)
{
	TRACE();
	
	int status = 0;
	char * relay = NULL;
	char * p2p = NULL;

	char * comment = NULL;
	char * sysinfo = NULL;
	
	char * user = NULL;
	char * pass = NULL;

	do
	{
		/* ��ȡrelay */
		try
		{
			relay = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 1;
		if (GetInfoLine(relay, DEAMON_BUF_SIZE, info, DEAMON_RELAY) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}
		
		/* ��ȡp2p */
		try
		{
			p2p = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 2;
		if (GetInfoLine(p2p, DEAMON_BUF_SIZE, info, DEAMON_P2P) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}
		
		/* ��ȡuser */
		try
		{
			user = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 3;
		if (GetInfoLine(user, DEAMON_BUF_SIZE, info, DEAMON_USER) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}

		/* ��ȡpass */
		try
		{
			pass= new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 4;
		if (GetInfoLine(pass, DEAMON_BUF_SIZE, info, DEAMON_PASS) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}else{
            PRINT(1, "pass=%s",pass);
		}

		/* ��ȡcomment */
		try
		{
			comment = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 5;
		strcpy(comment, "mac:");
		unsigned len = strlen(comment);
		if (GetMacAddr(comment + len, DEAMON_BUF_SIZE - len) == NULL)
		{
			PRINT(2, "GetMacAddr = NULL");
			break;
		}
		len = strlen(comment);
		comment[len] = ';';
		comment[++len] = 0;

		if (GetInfoLine(comment + len, DEAMON_BUF_SIZE - len, info, DEAMON_COMMENT) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}

		/* ��ȡloglevel 0 - 3 */
		char log0[8] = { 0 };
		if (GetInfoLine(log0, sizeof log0, info, DEAMON_LOGLEVEL0) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}
		char log1[8] = { 0 };
		if (GetInfoLine(log1, sizeof log1, info, DEAMON_LOGLEVEL1) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}
		char log2[8] = { 0 };
		if (GetInfoLine(log2, sizeof log2, info, DEAMON_LOGLEVEL2) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}
		char log3[8] = { 0 };
		if (GetInfoLine(log3, sizeof log3, info, DEAMON_LOGLEVEL3) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}

		len = strlen(relay) + strlen(p2p) + strlen(user) + strlen(pass) +  strlen(comment)
				+ strlen(log0) + strlen(log1) + strlen(log2) + strlen(log3) + strlen(DEAMON_SYSINFO) + 1;
		
		try
		{
			sysinfo = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 6;
		
		sprintf(sysinfo, DEAMON_SYSINFO, relay, p2p, user , pass , comment, log0, log1, log2, log3);
		PRINT(0, sysinfo);
		
	}while (0);
	
	/* �������� */
	if (0 < status)
	{
		delete[] relay;
	}
	if (1 < status)
	{
		delete[] p2p;
	}
	if (2 < status)
	{
		delete[] user;
	}
	if (3 < status)
	{
		delete[] pass;
	}
	if (4 < status)
	{
		delete[] comment;
	}
	if (5 < status)
	{
		return sysinfo;
	}
	return NULL;
}

/**
 * ��ʼ�����ģ��
 *
 * ����ֵ���ɹ�����0��ʧ�ܷ�0
 */
int InitTunnel(void)
{
	TRACE();
	
	int status = 0;
	char * info = NULL;
	char * devid = NULL;
	char * sysinfo = NULL;
	
	do
	{
		/* ��ȡ���޸�������Ϣ */
		try
		{
			info = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 1;
		if (GetFileInfo(info, DEAMON_BUF_SIZE) == NULL)
		{
			PRINT(2, "GetFileInfo = NULL");
			break;
		}

		/* ��ȡdevid */
		try
		{
			devid = new char[DEAMON_BUF_SIZE];
		}
		catch (...)
		{
			PRINT(2, "new = NULL");
			break;
		}
		status = 2;
		if (GetInfoLine(devid, DEAMON_BUF_SIZE, info, DEAMON_DEVID) == NULL)
		{
			PRINT(2, "GetInfoLine = NULL");
			break;
		}

		/* ����������Ϣ */
		sysinfo = CreateSysInfo(info);
		if (NULL == sysinfo)
		{
			PRINT(2, "CreateSysInfo = NULL");
			break;
		}
		status = 3;

		/* �������ò��� */
		int err = pgTunnelSetCfgParam(sysinfo);
		if (err != 0)
		{
			PRINT(2, "pgTunnelSetCfgParam = %d", err);
			break;
		}

		/* �������ģ�� */
		sprintf(info, DEAMON_SYS, devid);
		if ((err = pgTunnelStart(DEAMON_SYSINFO_FILE, info, NULL, LogOutPut)) != 0)
		{
			PRINT(2, "pgTunnelStart = %d", err);
			break;
		}
		status = 4;
		
	}while (0);
	
	if (0 < status)
	{
		delete[] info;
	}
	if (1 < status)
	{
		delete[] devid;
	}
	if (2 < status)
	{
		delete[] sysinfo;
	}
	if (3 < status)
	{
		return 0;
	}
	return -1;
}

/**
* �������ź�SIGTERM������
*
* signo[in]: �źŴ���
*/
void SigtermFunc(int signo)
{
	TRACE();
	PRINT(0, "kill SIGTERM to exit(0)");
	pgTunnelStop();
	exit(0);
}

/**
* ��������װ�źŴ�����
*
* ����ֵ���ɹ�����0��ʧ�ܷ�0
*/
int SetSignal(void)
{
	TRACE();

	struct sigaction sa;
	sa.sa_handler = SigtermFunc;
	sigfillset(&sa.sa_mask);
	sigdelset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = 0;
	if (sigaction(SIGTERM, &sa, NULL) == -1)
	{
		PRINT(2, "sigaction = -1, errno = %d", errno);
		return -1;
	}
	return 0;
}
