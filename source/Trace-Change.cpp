/**
 * ����: Traceʵ���ļ�
 *
 */

#include"../include/Trace-Change.h"

namespace change
{
	const char* Trace::kSTR_NAME = "trace.txt";		/* ���������ļ���Ĭ���� */
	const char* Trace::kSTR_INFO = "Info    ";		/* ��Ϣ */
	const char* Trace::kSTR_WARNING = "Warning ";	/* ���� */
	const char* Trace::kSTR_ERROR = "Error   ";		/* ���� */
	/**
	* ����: ����Trace����, ���������ļ�
	*
	* file[in]: ���������ļ���
	*/
	Trace::Trace(const char * file)
	{
		if (NULL == file || NULL == (fp_ = fopen(file, "w")))
		{
			on_ = false;
			return;
		}

		if (0 != setvbuf(fp_, NULL, _IONBF, 0))
		{
			on_ = false;
			return;
		}

		THREAD_MUTEX_INIT(&mt_);
		on_ = true;
	}

	/**
	 * ����: ��ȡ���ٿ���״̬
	 *
	 * ����ֵ: true��, false�ر�
	 */
	bool Trace::GetTraceStatus(void)
	{
		return on_;
	}

	/**
	 * ����: ���ø��ٿ���״̬
	 *
	 * ����ֵ: true��, false�ر�
	 */
	void Trace::SetTraceStatus(bool on)
	{
		on_ = on;
	}

	/**
	 * ����: ��ȡ�����ļ�ָ��
	 *
	 * ����ֵ: �ɹ������ļ�ָ��, ʧ��NULL
	 */
	FILE * Trace::GetTraceFile(void)
	{
		return fp_;
	}

	/**
	 * ����: ��ȡö���ַ���
	 *
	 * level[in]: ����ȼ�
	 *
	 * ����ֵ: �ɹ����س����ַ���, ʧ��NULL
	 */
	const char * Trace::GetStrLevel(int level)
	{
		switch (level)
		{
		case kINFO:
			return kSTR_INFO;

		case kWARNING:
			return kSTR_WARNING;

		case kERROR:
			return kSTR_ERROR;
		}
		return NULL;
	}

	/**
	 * ����: ��ȡ����ʱ��
	 *
	 * time_str[out]: ���汾��ʱ���ַ����Ļ�����
	 *
	 * ����ֵ: �ɹ������ַ���, ʧ��NULL
	 */
	char * Trace::GetStrLocalTime(char * time_str, unsigned size)
	{
		if (24 > size)
		{
			return NULL;
		}

		time_t now_time = time(NULL);
		struct tm * now_tm = localtime(&now_time);

		sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d  ", now_tm->tm_year + 1900, now_tm->tm_mon + 1, \
			now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);

		return time_str;
	}

	/**
	 * ����: ���ļ�·���ҳ��ļ���, ������_Trace����
	 *
	 *file[in]: �ļ�·��
	 *
	 *����ֵ: �ɹ���NULL, ʧ��NULL
	 */
	static const char * TruncateFileName(const char * file)
	{
		if (NULL == file)
		{
			return NULL;
		}

		const char * tmp = file;
		for (; 0 != *file; ++file)
		{
			if ('\\' == file[0] || '/' == file[0])
			{
				tmp = file + 1;
			}
		}
		return tmp;
	}



	/**
	 * ����: ��ӡ������Ϣ���ļ�ϵͳ
	 *
	 * file[in]: ԭ�ļ���
	 *
	 * func[in]: ������
	 *
	 * line[in]: �к�
	 */
	void Trace::_Trace(const char * file, const char * func, unsigned line)
	{
		if (!on_)
		{
			return;
		}

		try
		{

			
			THREAD_MUTEX_LOCK(&mt_);

			char time_str[24];

			if (NULL != GetStrLocalTime(time_str, sizeof time_str) && (file = TruncateFileName(file)))
			{
				fprintf(fp_, "\n%s%-20s  %-20s  %-8u\n", time_str, file, func, line);
			}

			THREAD_MUTEX_UNLOCK(&mt_);
		}
		catch (...)
		{
			THREAD_MUTEX_UNLOCK(&mt_);
			on_ = false;
		}
	}

	/**
	 * ����: ��ӡ������Ϣ���ļ�ϵͳ
	 *
	 * level[in]: ����ȼ�
	 *
	 * format[in]: ��ʽ���ַ���
	 */
	void Trace::_Print(int level, const char * format, ...)
	{
		if (!on_)
		{
			return;
		}

		try
		{
			THREAD_MUTEX_LOCK(&mt_);

			va_list list;
			va_start(list, format);

			char buffer[4096];
			strcpy(buffer, GetStrLevel(level));
			int len = strlen(buffer);
			vsnprintf(buffer + len, sizeof buffer - len - 1, format, list);

			len = strlen(buffer);
			buffer[len] = '\n';
			len += 1;
			if (fwrite(buffer, sizeof(char), len, fp_) != len)
			{
				on_ = false;
			}

			THREAD_MUTEX_UNLOCK(&mt_);
		}
		catch (...)
		{
			THREAD_MUTEX_UNLOCK(&mt_);
		}
	}

	/**
	 * ����: ��������
	 *
	 */
	Trace::~Trace(void)
	{
		fclose(fp_);
		THREAD_MUTEX_DESTROY(&mt_);
	}

	Trace trace;		/* Ψһ�Ķ��� */
}
