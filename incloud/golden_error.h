#ifndef __GOLDEN_ERROR_H__
#define __GOLDEN_ERROR_H__

#define GoE_UNKNOWN_ERROR                                   0xFFFFFFFF  // δ֪����
#define GoE_OK                                              0x00000000  // �����ɹ����
#define GoE_WINDOWS_ERROR                                   0xFFF00000  // Windows����ϵͳ�������ʼֵ
#define GoE_WINDOWS_ERROR_MAX                               0xFFFF0000  // Windows����ϵͳ����Ľ���ֵ

#define GOLDEN_SOCKET_ADAPTER_FALSE(GOLDEN_ERROR) (GOLDEN_ERROR > 0xFFF02710 && GOLDEN_ERROR <= 0xFFF02AFC)
#define GOLDEN_WINDOWS_ERROR_TO_GOLDEN(WINDOWS_ERROR) (GoE_WINDOWS_ERROR + WINDOWS_ERROR)

#define GoE_INVALID_OPENMODE                                0xFFFF0001  // ��Ч���ļ��򿪷�ʽ
#define GoE_OPENFILE_FAILED                                 0xFFFF0002  // ���ļ�ʧ��
#define GoE_MOVETOEND_FAILED                                0xFFFF0003  // �ƶ��ļ�ָ�뵽�ļ�βʧ��
#define GoE_DIFFER_READBYTES                                0xFFFF0004  // ��ȡ���ݳ�����Ҫ�󲻷�
#define GoE_GETFILEPOS_FAILED                               0xFFFF0005  // ��ȡ��ǰ�ļ�ָ��ʧ��
#define GoE_FLUSHFILE_FAILED                                0xFFFF0006  // ˢ���ļ�������ʧ��
#define GoE_SETSIZE_FAILED                                  0xFFFF0007  // �����ļ���Сʧ��
#define GoE_FILE_NOT_CLOSED                                 0xFFFF0008  // ��ͼ��δ�رյ��ļ����󴴽�����ļ�
#define GoE_FILE_UNKNOWN                                    0xFFFF0009  // ��������ļ�ʱ����ָ���ļ���
#define GoE_INVALID_HEADER                                  0xFFFF000A  // �����ļ�ͷ��Ϣ����
#define GoE_DISABLED_FILE                                   0xFFFF000B  // �����ļ���Ч����ͼ������Ч�����ļ�
#define GoE_FILE_NOT_OPENED                                 0xFFFF000C  // ��ͼ������δ�򿪵������ļ�
#define GoE_POINT_NOT_FOUND                                 0xFFFF000D  // Ҫ����ʵı�ǩ�㲻���ڻ���Ч
#define GoE_READYBLOCK_NOT_FOUND                            0xFFFF000E  // �����ļ����Ҳ�����ָ�����ݿ��Ժ�Ŀ��õĿտ�
#define GoE_FILE_IS_INCULT                                  0xFFFF000F  // �ļ�δ��ʹ�ù�
#define GoE_FILE_IS_FULL                                    0xFFFF0010  // �����ļ�����
#define GoE_FILEEX_IS_FULL                                  0xFFFF0011  // �����ļ���չ���������޷�����װ������
#define GoE_INVALID_DATA_TYPE                               0xFFFF0012  // ��Ч����������
#define GoE_DATABLOCK_NOT_FOUND                             0xFFFF0013  // �Ҳ�������ʱ�����������ݿ�
#define GoE_DATA_BETWEEN_BLOCK                              0xFFFF0014  // ����ʱ��λ���ҵ��Ŀ����һ�����ݿ�֮��
#define GoE_CANT_MODIFY_EXIST_VALUE                         0xFFFF0015  // �������޸��Ѵ��ڵ�����
#define GoE_WRONGDATA_IN_BLOCK                              0xFFFF0016  // �����д������ݵ������ݿ�ͷ��Ϣ����
#define GoE_DATATIME_NOT_IN                                 0xFFFF0017  // �����ļ���û�иñ�ǩ��ָ��ʱ�������
#define GoE_NULL_ARCHIVE_PATH                               0xFFFF0018  // �����������ļ�·��Ϊ��
#define GoE_REG_ARCHIVE_PATH                                0xFFFF0019  // �����ļ��ѱ�ע��
#define GoE_UNREG_ARCHIVE_PATH                              0xFFFF001A  // δע��������ļ�
#define GoE_FILE_INEXISTENCE                                0xFFFF001B  // ָ�����ļ�������
#define GoE_DATA_TYPE_NOT_MATCH                             0xFFFF001C  // �������Ͳ�ƥ��
#define GoE_FILE_IS_READONLY                                0xFFFF001D  // �������޸�ֻ�������ļ��е�����
#define GoE_TOMANY_ARCHIVE_FILE                             0xFFFF001E  // ����������ļ�
#define GoE_NO_POINTS_LIST                                  0xFFFF001F  // ȱ�ٱ�ǩ���б�
#define GoE_NO_ACTIVED_ARCHIVE                              0xFFFF0020  // ȱ�ٻ�ĵ�
#define GoE_NO_ARCHIVE_FILE                                 0xFFFF0021  // ȱ�������ĵ�
#define GoE_NEED_ACTIVED_ARCHIVE                            0xFFFF0022  // ֻ���ڻ�ĵ���ִ�иò���
#define GoE_INVALID_TIMESTAMP                               0xFFFF0023  // ��Ч��ʱ���
#define GoE_NEED_MORE_WRITABLE                              0xFFFF0024  // ��ֻ���ĵ�����̫��
#define GoE_NO_ARCHIVE_FOR_PUT                              0xFFFF0025  // �Ҳ������ʵ�׷����ʷ���ݵ��ĵ�
#define GoE_INVALID_VALUE_MODE                              0xFFFF0026  // ��Ч��ȡֵģʽ
#define GoE_DATA_NOT_FOUND                                  0xFFFF0027  // �Ҳ�����Ҫ������
#define GoE_INVALID_PARAMETER                               0xFFFF0028  // ��Ч�Ĳ���
#define GoE_REDUPLICATE_TAG                                 0xFFFF0029  // �ظ��ı�ǩ����
#define GoE_REDUPLICATE_TABNAME                             0xFFFF002A  // �ظ��ı�����
#define GoE_REDUPLICATE_TABID                               0xFFFF002B  // �ظ��ı�ID
#define GoE_TABLE_NOT_FOUND                                 0xFFFF002C  // ָ���ı�����
#define GoE_UNSUPPORTED_CLASSOF                             0xFFFF002D  // ��֧�ֵı�ǩ�����
#define GoE_WRONG_OR_DUPLIC_TAG                             0xFFFF002E  // ����Ļ��ظ��ı�ǩ����
#define GoE_REDUPLICATE_PT                                  0xFFFF002F  // �ظ��ı�ǩ���ʶ
#define GoE_POINT_LICENSE_FULL                              0xFFFF0030  // ��ǩ�������������֤�涨�������Ŀ
#define GoE_TABLE_LICENSE_FULL                              0xFFFF0031  // ��ǩ���������������֤�涨�������Ŀ
#define GoE_WRONG_OR_DUPLIC_TABNAME                         0xFFFF0032  // ����Ļ��ظ��ı�����
#define GoE_INVALID_FILE_FORMAT                             0xFFFF0033  // ��Ч�������ļ���ʽ
#define GoE_WRONG_TABNAME                                   0xFFFF0034  // ����ı�����
#define GoE_WRONG_TAG                                       0xFFFF0035  // ����ı�ǩ����
#define GoE_NOT_IN_SCOPE                                    0xFFFF0036  // ��ֵ������Ӧ���ķ�Χ
#define GoE_CANT_LOAD_BASE                                  0xFFFF0037  // ����ͬ��ǩ����Ϣ����ȡ����ϵ
#define GoE_CANT_LOAD_SNAPSHOT                              0xFFFF0038  // ����ͬ�������ݷ���ȡ����ϵ
#define GoE_CANT_LOAD_HISTORY                               0xFFFF0039  // ����ͬ��ʷ���ݷ���ȡ����ϵ
#define GoE_CANT_LOAD_EQUATION                              0xFFFF003A  // ����ͬʵʩ����ʽ����ȡ����ϵ
#define GoE_ARRAY_SIZE_NOT_MATCH                            0xFFFF003B  // ����ߴ粻ƥ��
#define GoE_INVALID_HOST_ADDRESS                            0xFFFF003C  // ��Ч��������ַ
#define GoE_CONNECT_FALSE                                   0xFFFF003D  // �����ѶϿ�
#define GoE_TOOMANY_BYTES_RECVED                            0xFFFF003E  // ���յ������ݳ��ȳ�����ָ���ֽڳ���
#define GoE_REQID_RESPID_NOT_MATCH                          0xFFFF003F  // Ӧ���������ID��һ��
#define GoE_LESS_BYTES_RECVED                               0xFFFF0040  // ���յ������ݳ���С��ָ���ֽڳ���
#define GoE_UNSUPPORTED_CALC_MODE                           0xFFFF0041  // ��֧�ֵļ���ģʽ
#define GoE_UNSUPPORTED_DATA_TYPE                           0xFFFF0042  // ��֧�ֵı�ǩ������
#define GoE_INVALID_EXPRESSION                              0xFFFF0043  // ��Ч�ı��ʽ
#define GoE_INCOND_DATA_NOT_FOUND                           0xFFFF0044  // �Ҳ�����������������
#define GoE_VALID_DATA_NOT_FOUND                            0xFFFF0045  // �Ҳ�����Ҫ����Ч����
#define GoE_VALUE_OR_STATE_IS_NAN                           0xFFFF0046  // ���ݻ�״̬��������ΪNAN
#define GoE_CREATE_MUTEX_FAILED                             0xFFFF0047  // �����������ʧ��
#define GoE_TLSALLOCFAIL                                    0xFFFF0048  // ����TLSʱ����ϵͳ����LocalAlloc()ʧ�ܣ�������Ϊ�ڴ治�㵼��
#define GoE_TO_MANY_POINTS                                  0xFFFF0049  // ���ڵ��õ�API������֧�ֹ���ı�ǩ����������ο����������Ϳ����ֲ�
#define GoE_LIC_INFO_ERROR                                  0xFFFF004A  // ��ȡ��Ȩ���Э����Ϣʱ��������
#define GoE_ARCHIVE_BUFFER_FULL                             0xFFFF004B  // ��ǩ�����ʷ���ݲ�д���������������Ժ��ٲ�
#define GoE_USER_NOT_EXIST                                  0xFFFF004C  // �û�������
#define GoE_USER_IS_LOCKED                                  0xFFFF004D  // �ʻ�������,��Ҫ����ԱΪ������
#define GoE_WRONG_PASSWORD                                  0xFFFF004E  // ����Ŀ���
#define GoE_ACCESS_IS_DENIED                                0xFFFF004F  // ���ʱ��ܾ�����ȷ���Ƿ�����㹻��Ȩ��
#define GoE_HAVE_NOT_LOGIN                                  0xFFFF0050  // ����δ��¼�����ȵ�¼
#define GoE_USER_IS_DELETED                                 0xFFFF0051  // �ʻ��ѱ�ɾ��
#define GoE_USER_ALREADY_EXIST                              0xFFFF0052  // �ʻ��Ѵ���
#define GoE_WRONG_CREATE_TABNAME                            0xFFFF0053  // ����ɾ����ʧ��
#define GoE_WRONG_FIELD_VALUE                               0xFFFF0054  // ��ǩ������ֵ�д���
#define GoE_INVALID_TAG_ID                                  0xFFFF0055  // ��Ч�ı�ǩ��ID
#define GoE_CHECK_NAMED_TYPE_NAME_ERROR                     0xFFFF0056  // ��Ч���Զ����������ƻ��ֶ�����
#define GoE_CANT_LOAD_DISPATCH                              0xFFFF0057  // ����ͬת��������ȡ����ϵ
#define GoE_CONNECT_TIME_OUT                                0xFFFF0058  // �����ѳ�ʱ����Ҫ���µ�¼
#define GoE_WRONG_LOGIN_4                                   0xFFFF0059  // �˻���Ϣ��֤ʧ�ܣ�����4�γ��Ի���
#define GoE_WRONG_LOGIN_3                                   0xFFFF005A  // �˻���Ϣ��֤ʧ�ܣ�����3�γ��Ի���
#define GoE_WRONG_LOGIN_2                                   0xFFFF005B  // �˻���Ϣ��֤ʧ�ܣ�����2�γ��Ի���
#define GoE_WRONG_LOGIN_1                                   0xFFFF005C  // �˻���Ϣ��֤ʧ�ܣ�����1�γ��Ի���
#define GoE_WRONG_DESC										0xFFFF005D  //!< ����ı�����
#define GoE_WRONG_UNIT										0xFFFF005E  //!< ����Ĺ��̵�λ
#define GoE_WRONG_CHANGER									0xFFFF005F  //!< ��������һ�α��޸ĵ��û��� 
#define GoE_WRONG_CREATOR									0xFFFF0060  //!< ����ı�ǩ�㴴�����û���
#define GoE_WRONG_FULL										0xFFFF0061  //!< ����ı�ǩ��ȫ��
#define GoE_WRONG_SOURCE									0xFFFF0062  //!< ���������Դ
#define GoE_WRONG_INSTRUMENT								0xFFFF0063  //!< ������豸��ǩ
#define GoE_WRONG_USER										0xFFFF0064  //!< ����Ĵ�����
#define GoE_WRONG_EQUATION									0xFFFF0065  //!< �����ʵʱ����ʽ
#define GoE_WRONG_TYPE_NAME									0xFFFF0066  //!< ������Զ�����������
#define GoE_WRONG_ENCODE									0xFFFF0067  //!< ����ת��ʱ����
#define GoE_WRONG_OTHERMASK									0xFFFF0068  //!< �������������ת��maskֵ
#define GoE_WRONG_TYPE										0xFFFF0069  //!< �������������
#define GoE_POINT_HARDWARE_LIMITED                          0xFFFF0070  // ����Ӳ����Դ���ƣ�������ָ���ǩ��ʧ��


// v2.1 increased errors
#define GoE_NO_FREE_TABLE_ID                                0xFFFF1001  // û�п��еı�ID����
#define GoE_NO_FREE_TAG_POSITION                            0xFFFF1002  // û�п��еı�ǩ��λַ����
#define GoE_NO_FREE_SCAN_TAG_POSITION                       0xFFFF1003  // û�п��еĲɼ���ǩ��λַ����
#define GoE_NO_FREE_CALC_TAG_POSITION                       0xFFFF1004  // û�п��еļ����ǩ��λַ����
#define GoE_INVALID_IPC_POSITION                            0xFFFF1005  // ��Ч��λַ�����ڽ��̼��ڴ湲��
#define GoE_WRONG_IPC_POSITION                              0xFFFF1006  // �����λַ�����ڽ��̼��ڴ湲��
#define GoE_IPC_ACCESS_EXCEPTION                            0xFFFF1007  // �����ڴ�����쳣
#define GoE_ARV_PAGE_NOT_READY                              0xFFFF1008  // û�п��е���ʷ���ݻ���ҳ
#define GoE_ARVEX_PAGE_NOT_READY                            0xFFFF1009  // û�п��еĲ���ʷ���ݻ���ҳ
#define GoE_INVALID_POSITION_FROM_ID                        0xFFFF100A  // ���ݱ�ǩ��ID��õ�λַ��Ч
#define GoE_NO_ACTIVE_PAGE_ALLOCATOR                        0xFFFF100B  // �µĻ�浵�޷�����ҳ������
#define GoE_MAP_IS_NOT_READY                                0xFFFF100C  // �ڴ�ӳ����δ����
#define GoE_FILE_MAP_FAILED                                 0xFFFF100D  // �ļ�ӳ�䵽�ڴ�ʧ��
#define GoE_TIME_RANGE_NOT_ALLOWED                          0xFFFF100E  // ������ʹ�õ�ʱ������
#define GoE_NO_DATA_FOR_SUMMARY                             0xFFFF100F  // �Ҳ�������ͳ�Ƶ�Դ����
#define GoE_CANT_OPERATE_ON_ACTIVED                         0xFFFF1010  // �����������浵�ļ�
#define GoE_SCAN_POINT_LICENSE_FULL                         0xFFFF1011  // �ɼ���ǩ�������������֤�涨�������Ŀ
#define GoE_CALC_POINT_LICENSE_FULL                         0xFFFF1012  // �����ǩ�������������֤�涨�������Ŀ
#define GoE_HISTORIAN_IS_SHUTTINGDOWN                       0xFFFF1013  // ��ʷ���ݷ�������ֹͣ
#define GoE_SNAPSHOT_IS_SHUTTINGDOWN                        0xFFFF1014  // ʵʱ���ݷ�������ֹͣ
#define GoE_EQUATION_IS_SHUTTINGDOWN                        0xFFFF1015  // ʵʱ����ʽ��������ֹͣ
#define GoE_BASE_IS_SHUTTINGDOWN                            0xFFFF1016  // ��ǩ����Ϣ��������ֹͣ
#define GoE_SERVER_IS_SHUTTINGDOWN                          0xFFFF1017  // ����ͨ�ŷ�������ֹͣ
#define GoE_OUT_OF_MEMORY                                   0xFFFF1018  // �ڴ治��
#define GoE_INVALID_PAGE                                    0xFFFF1019  // ��Ч������ҳ���п�����δ����
#define GoE_PAGE_IS_EMPTY                                   0xFFFF101A  // �����յ�����ҳ
#define GoE_STR_OR_BLOB_TOO_LONG                            0xFFFF101B  // �ַ�����BLOB���ݳ��ȳ�������
#define GoE_CREATED_OR_OVERDUE                              0xFFFF101C  // ��δ�����κο��ջ�����ѹ���
#define GoE_ARCHIVE_INFO_NOT_MATCHING                       0xFFFF101D  // ��ʷ�浵�ļ�ͷ����Ϣ��ʵ�ʲ���
#define GoE_TIME_RANGE_OVERLAPPING                          0xFFFF101E  // ָ����ʱ�䷶Χ�����д浵�ļ��ص�
#define GoE_CANNOT_SHIFT_TO_ACTIVED                         0xFFFF101F  // �Ҳ������ʵĴ浵�ļ������л��ɻ�浵
#define GoE_INDEX_NOT_READY                                 0xFFFF1020  // ��ʷ�浵�ļ���Ӧ��������δ����
#define GoE_INDEX_NODE_NOT_MATCH                            0xFFFF1021  // �����ڵ���ָ������ݲ���
#define GoE_CAN_NOT_CREATE_INDEX                            0xFFFF1022  // �޷����������ڵ�
#define GoE_CAN_NOT_REMOVE_INDEX                            0xFFFF1023  // �޷�ɾ�������ڵ�
#define GoE_INVALID_FILTER_EXPRESS                          0xFFFF1024  // ��Ч�Ĺ��������ʽ
#define GoE_MORE_VAR_IN_FILTER_EXP                          0xFFFF1025  // ���������ʽ�еİ����˹���ı���
#define GoE_INVALID_ARV_PAGE_ALLOCATE                       0xFFFF1026  // �շ������ʷ���ݻ���ҳID���ǩ���¼�����ID��ƥ��
#define GoE_INVALID_ARVEX_PAGE_ALLOCATE                     0xFFFF1027  // �շ���Ĳ���ʷ���ݻ���ҳID���ǩ���¼�����ID��ƥ��
#define GoE_BIG_JOB_IS_NOT_DONE                             0xFFFF1028  // ����ִ����Ҫ���������Ժ�����
#define GoE_DATABASE_NEED_RESTART                           0xFFFF1029  // ���ݿ���Ҫ���������Ա�Ӧ���µĲ���
#define GoE_INVALID_TIME_FORMAT                             0xFFFF102A  // ��Ч��ʱ���ʽ�ַ���
#define GoE_DATA_PLAYBACK_DONE                              0xFFFF102B  // ��ʷ���ݻطŹ����ѽ���
#define GoE_BAD_EQUATION                                    0xFFFF102C  // ����ķ���ʽ
#define GoE_NOT_ENOUGH_SAPCE                                0xFFFF102D  // ʣ����̿ռ䲻��
#define GoE_ACTIVED_ARCHIVE_EXIST                           0xFFFF102E  // �Ѵ��ڻ�浵
#define GoE_ARCHIVE_HAVE_EX_FILES                           0xFFFF102F  // ָ���Ĵ浵�ļ����и����ļ�
#define GoE_ARCHIVE_IS_NOT_LATEST                           0xFFFF1030  // ָ���Ĵ浵�ļ����������
#define GoE_DB_SYSTEM_NOT_RUNNING                           0xFFFF1031  // ���ݿ����ϵͳ��δ��ȫ����
#define GoE_ARCHIVE_IS_ALTERED                              0xFFFF1032  // �浵�ļ����ݷ������
#define GoE_ARCHIVE_IS_TOO_SMALL                            0xFFFF1033  // ��������̫С�Ĵ浵�ļ��͸����ļ�
#define GoE_INVALID_INDEX_NODE                              0xFFFF1034  // ������Ч�������ڵ�
#define GoE_MODIFY_SNAPSHOT_NOT_ALLOWED                     0xFFFF1035  // ������ɾ�����޸Ŀ����¼�
#define GoE_SEARCH_INTERRUPTED                              0xFFFF1036  // ��Ŀ������������ɾ����ָ������������жϣ����Ժ�����
#define GoE_RECYCLE_SHUTDOWN                                0xFFFF1037  // ����վ��ʧЧ����ز����޷����
#define GoE_NEED_TO_REINDEX                                 0xFFFF1038  // �����ļ�ȱʧ���򲿷������ڵ㱻�𻵣���Ҫ�ؽ�����
#define GoE_INVALID_QUALITY                                 0xFFFF1039  // ��Ч��������
#define GoE_EQUATION_NOT_READY                              0xFFFF103A  // ʵʱ����ʽ�������ڽ��������Ժ�����
#define GoE_ARCHIVES_LICENSE_FULL                           0xFFFF103B  // �浵�ļ����Ѵﵽ���֤�涨�������Ŀ
#define GoE_RECYCLED_LICENSE_FULL                           0xFFFF103C  // ��ǩ�����վ�������������֤�涨�������Ŀ
#define GoE_STR_BLOB_LICENSE_FULL                           0xFFFF103D  // �ַ�����BLOB���ͱ�ǩ���������������֤�涨�������Ŀ
#define GoE_NOT_SUPPORT_WHEN_DEBUG                          0xFFFF103E  // �˹��ܱ�ĳ������ѡ�����
#define GoE_MAPPING_ALREADY_LOADED                          0xFFFF103F  // ӳ���Ѿ������أ��������ظ�����
#define GoE_ARCHIVE_IS_MODIFIED                             0xFFFF1040  // �浵�ļ����޸ģ��������ж�
#define GoE_ACTIVE_ARCHIVE_FULL                             0xFFFF1041  // ��ĵ�����
#define GoE_SPLIT_NO_DATA                                   0xFFFF1042  // �������ҳ������ʱ��������û������
#define GoE_INVALID_DIRECTORY                               0xFFFF1043  // ָ����·�������ڻ���Ч
#define GoE_ARCHIVE_LACK_EX_FILES                           0xFFFF1044  // ָ���浵�ļ��Ĳ��ָ����ļ�ȱʧ
#define GoE_BIG_JOB_IS_CANCELED                             0xFFFF1045  // ��̨����ȡ��

#define GoE_ARVEX_BLOB_PAGE_NOT_READY                       0xFFFF1046  // û�п��е�blob����ʷ���ݻ���ҳ
#define GoE_INVALID_ARVEX_BLOB_PAGE_ALLOCATE                0xFFFF1047  // �շ����blob����ʷ���ݻ���ҳID���ǩ���¼�����ID��ƥ��

#define GoE_TIMESTAMP_EQUALTO_SNAPSHOT                      0xFFFF1048  // д���ʱ�������ʱ����ͬ
#define GoE_TIMESTAMP_EARLIER_THAN_SNAPSHOT                 0xFFFF1049  // д���ʱ��ȵ�ǰ����ʱ�����
#define GoE_TIMESTAMP_GREATER_THAN_ALLOW                    0xFFFF104A  // д���ʱ�䳬���������ʱ��
#define GoE_TIMESTAMP_BEGINTIME_GREAGER_THAN_ENDTIME        0xFFFF104B  // ��ʼʱ����ڽ���ʱ��
#define GoE_TIMESTAMP_BEGINTIME_EQUALTO_ENDTIME             0xFFFF104C  // ��ʼʱ����ڽ���ʱ��

#define GoE_INVALID_COUNT                                   0xFFFF104D  //��Ч��count
#define GoE_INVALID_CAPACITY                                0xFFFF104E  //��Ч��capacity
#define GoE_INVALID_PATH                                    0xFFFF104F  //��Ч��·��
#define GoE_INVALID_POSITION                                0xFFFF1050  //��Ч��position
#define GoE_INVALID_ARV_PAGE                                0xFFFF1051  //��Ч��golden_arv_page<GOLDEN_T>,δ���أ�����sizeС�ڵ���0
#define GoE_INVALID_HISINFO_ITEM_STATE                      0xFFFF1052
#define GoE_INVALID_INTERVAL                                0xFFFF1053
#define GoE_INVALID_LENGTH                                  0xFFFF1054  //��Ч���ַ�������
#define GoE_INVALID_SERACH_MODE                             0xFFFF1055  //��Ч��search mode
#define GoE_INVALID_FILE_ID                                 0xFFFF1056  //��Ч�Ĵ浵�ļ�ID
#define GoE_INVALID_MILLISECOND                             0xFFFF1057  //��Ч�ĺ���ֵ
#define GoE_INVALID_DEADLINE                                0xFFFF1058  //��Ч�Ľ�ֹʱ��
#define GoE_INVALID_JOBNAME                                 0xFFFF1059  //
#define GoE_INVALID_JOBSTATE                                0xFFFF105A  //
#define GoE_INVALID_PROCESS_RATE                            0xFFFF105B  //




#define GoE_INVALID_TABLE_ID                                0xFFFF105C  // ��Ч�ı�ID
#define GoE_INVALID_DATA_SOURCE                             0xFFFF105D  // ��Ч������Դ��ʽ
#define GoE_INVALID_TRIGGER_METHOD                          0xFFFF105E  // ��Ч�Ĵ�����ʽ
#define GoE_INVALID_CALC_TIME_RES                           0xFFFF105F  // ��Ч�ļ�����ʱ����ο���ʽ
#define GoE_INVALID_TRIGGER_TIMER                           0xFFFF1060  // ��Ч�Ķ�ʱ������������,����С��1��
#define GoE_INVALID_LIMIT                                   0xFFFF1061  // �������޲��õ��ڹ�������
#define GoE_INVALID_COMP_TIME                               0xFFFF1062  // ��Ч��ѹ��������ѹ���������С�����ѹ�����
#define GoE_INVALID_EXT_TIME                                0xFFFF1063  // ��Ч���������������������С�����������
#define GoE_INVALID_DIGITS                                  0xFFFF1064  // ��Ч����ֵλ������ֵλ�������˷�Χ,-20~10
#define GoE_INVALID_FULL_TAG_NAME                           0xFFFF1065  // ��ǩ��ȫ�������Ҳ�������������ķָ�����.��
#define GoE_INVALID_TABLE_DESC                              0xFFFF1066  // ��������Ϣ������
#define GoE_INVALID_USER_COUNT                              0xFFFF1067  // �Ƿ����û�������С��0
#define GoE_INVALID_BLACKLIST_COUNT                         0xFFFF1068  // �Ƿ��ĺ�����������С��0
#define GoE_INVALID_AUTHORIZATION_COUNT                     0xFFFF1069  // �Ƿ����������Ӹ�����С��0
#define GoE_INVALID_BIG_JOB_TYPE                            0xFFFF106A  // �Ƿ��Ĵ���������
#define GoE_INVALID_SYS_PARAM                               0xFFFF106B  // ��Ч��ϵͳ����������db_set_db_info2ʱ����������
#define GoE_INVALID_FILE_PARAM                              0xFFFF106C  // ��Ч���ļ�·������������db_set_db_info1ʱ����������
#define GoE_INVALID_FILE_SIZE                               0xFFFF106D  // �ļ���������  < 1 baserecycle.dat��scanrecycle.dat��calcrecycle.dat��snaprecycle.dat
#define GoE_INVALID_TAG_TYPE                                0xFFFF106E  // ��ǩ���������󣬺Ϸ��� golden_bool ~ golden_blob)�����ǲ�������Ӧ�����Ĵ���Χ
#define GoE_INVALID_RECY_STRUCT_POS                         0xFFFF106F  // ����վ�������һ���ṹ��λ�÷Ƿ�
#define GoE_INVALID_RECYCLE_FILE                            0xFFFF1070  // scanrecycle.dat��baserecycle.dat  snaprecycle.dat�ļ������ڻ�ʧЧ
#define GoE_INVALID_SUFFIX_NAME                             0xFFFF1071  // ��Ч���ļ���׺��

#define GoE_INSERT_STRING_FALSE                             0xFFFF1072  // ������ҳ�в����ַ�������ʧ��
#define GoE_BLOB_PAGE_FULL                                  0xFFFF1073  // blob����ҳ����
#define GoE_INVALID_STRING_ITERATOR_POINTER                 0xFFFF1074  // ��Ч��str/blob������ָ��
#define GoE_NOT_EQUAL_TAGID                                 0xFFFF1075  // Ŀ��ҳ��ǩ��ID �� ��ǰID��һ��
#define GoE_PATHS_OF_ARCHIVE_AND_AUTOBACK_ARE_SAME          0xFFFF1076  // �浵�ļ�·�����Զ�����·����ͬ
#define GoE_XML_PARSE_FAIL                                  0xFFFF1077  // xml�ļ�����ʧ��
#define GoE_XML_ELEMENTS_ABSENT                             0xFFFF1078  // xml�嵥�ļ��ļ�����ȱʧ
#define GoE_XML_MISMATCH_ON_NAME                            0xFFFF1079  // xml�嵥�ļ��뱾��Ʒ��ƥ��
#define GoE_XML_MISMATCH_ON_VERSION                         0xFFFF107A  // xml�嵥�ļ��汾��ƥ��
#define GoE_XML_MISMATCH_ON_DATASIZE                        0xFFFF107B  // xml�嵥�ļ����ݳߴ粻ƥ��
#define GoE_XML_MISMATCH_ON_FILEINFO                        0xFFFF107C  // xml�嵥�ļ��������ļ���Ϣ��ƥ��
#define GoE_XML_MISMATCH_ON_WINDOW                          0xFFFF107D  // xml�嵥�ļ������������ļ��Ĵ��ڴ�С����һ��

#define GoE_XML_MISMATCH_ON_TYPECOUNT                       0xFFFF107F  // xml�嵥�ļ��Զ����������͵�������ƥ��
#define GoE_XML_MISMATCH_ON_FIELDCOUNT                      0xFFFF1080  // xml�嵥�ļ��Զ����������͵�field��ƥ��
#define GoE_XML_FIELD_MUST_IN_TYPE                          0xFFFF1081  // xml�嵥�ļ���field��ǩ����Ƕ����type��ǩ��
#define GoE_INVALID_NAMED_TYPE_FIELD_COUNT                  0xFFFF1082  // ��Ч��FIELD����
#define GoE_REDUPLICATE_FIELD_NAME                          0xFFFF1083  // �ظ���FIELD����
#define GoE_INVALID_NAMED_TYPE_NAME                         0xFFFF1084  // ��Ч���Զ����������͵�����
#define GoE_REDUPLICATE_NAMED_TYPE                          0xFFFF1085  // �Ѿ����ڵ��Զ�����������
#define GoE_NOT_EXIST_NAMED_TYPE                            0xFFFF1086  // �����ڵ��Զ�����������
#define GoE_UPDATE_XML_FAILED                               0xFFFF1087  // ����XML�嵥�ļ�ʧ��
#define GoE_NAMED_TYPE_USED_WITH_POINT                      0xFFFF1088  // ��Щ��ǩ������ʹ�ô��Զ����������ͣ�������ɾ��
#define GoE_NAMED_TYPE_UNSUPPORT_CALC_POINT                 0xFFFF1089  // �Զ����������Ͳ�֧�ּ����
#define GoE_XML_MISMATCH_ON_MAX_ID                          0xFFFF1090  // �Զ����������͵����ID��ʵ�ʵ��Զ�����������������һ��
#define GoE_NAMED_TYPE_LICENSE_FULL                         0xFFFF1091  // �Զ����������͵��������������֤�涨�������Ŀ
#define GoE_NO_FREE_NAMED_TYPE_ID                           0xFFFF1092  // û�п��е��Զ����������͵�ID
#define GoE_INVALID_NAMED_TYPE_ID                           0xFFFF1093  // ��Ч���Զ�����������ID
#define GoE_INVALID_NAMED_TYPE_FIELD_NAME                   0xFFFF1094  // ��Ч���Զ����������͵��ֶ�����
#define GoE_NAMED_TYPE_USED_WITH_RECYCLE_POINT              0xFFFF1095  // ��Щ����վ�еı�ǩ������ʹ�ô��Զ����������ͣ�������ɾ��
#define GoE_NAMED_TYPE_NAME_TOO_LONG                        0xFFFF1096  // �Զ������͵����ֳ������������󳤶�
#define GoE_NAMED_TYPE_FIELD_NAME_TOO_LONG                  0xFFFF1097  // �Զ������͵�field ���ֳ������������󳤶�
#define GoE_INVALID_NAMED_TYPE_FIELD_LENGTH                 0xFFFF1098  // ��Ч���Զ����������͵��ֶγ���
#define GoE_INVALID_SEARCH_MASK                             0xFFFF1099  // ��Ч�ĸ߼������ı�ǩ������mask
#define GoE_RECYCLED_SPACE_NOT_ENOUGH                       0xFFFF109A  // ��ǩ�����վ���пռ䲻��
#define GoE_DYNAMIC_LOADED_MEMORY_NOT_INIT                  0xFFFF109B  // ��̬���ص��ڴ�δ��ʼ��
#define GoE_FORBID_DYNAMIC_ALLOC_TYPE                       0xFFFF109C  // �ڴ���ֹ��̬��������
#define GoE_MEMORYDB_INDEX_CREATE_FAILED                    0xFFFF109D  // �ڴ����������ʧ��
#define GoE_WG_MAKE_QUERY_RETURN_NULL                       0xFFFF109F  //whitedb make_query_rc����null
#define GoE_THTREAD_POOL_CREATED_FAILED                     0xFFFF10A0  // �ڴ�ⴴ���̳߳�ʧ��
#define GoE_MEMORYDB_REMOVE_RECORD_FAILED                   0xFFFF10A1  //�ڴ��ɾ����¼ʧ��
#define GoE_MEMORYDB_CONFIG_LOAD_FAILED                     0xFFFF10A2  // �ڴ�������ļ�����ʧ��
#define GoE_MEMORYDB_PROHIBIT_DYNAMIC_ALLO_TYPE             0xFFFF10A3   //�ڴ���ֹ��̬��������
#define GoE_MEMORYDB_DYNAMIC_ALLOC_TYPE_FAILED              0xFFFF10A4   //�ڴ�⶯̬��������ʧ��
#define GoE_MEMORYDB_STORAGE_FILE_NAME_PARSE_FAILED         0xFFFF10A5   //�ڴ�����ȼ��ļ�������ʧ��
#define GoE_MEMORYDB_TTREE_INDEX_DAMAGE                     0xFFFF10A6   //�ڴ��T��������
#define GoE_MEMORYDB_CONFIG_FAILED                          0xFFFF10A7   //�ڴ�������ļ�����
#define GoE_MEMORYDB_VALUE_COUNT_NOT_MATCH                  0xFFFF10A8   //�ڴ���¼��ֵ������ƥ�䡣
#define GoE_MEMORYDB_FIELD_TYPE_NOT_MATCH                   0xFFFF10A9   //�ڴ����ֶ����Ͳ�ƥ��       
#define GoE_MEMORYDB_MEMORY_ALLOC_FAILED                    0xFFFF10AA   //�ڴ���ڴ����ʧ��
#define GoE_MEMORYDB_METHOD_PARAM_ERR                       0xFFFF10AB   //�ڴ�ⷽ����������
#define GoE_MEMORYDB_QUERY_RESULT_ALLOC_FAILED              0xFFFF10AC   //�ڴ���ѯ����������ʧ��
#define GoE_FILE_PATH_LENGTH                                0xFFFF10AD   //ָ�����ļ�·�����ȴ���
#define GoE_MEMORYDB_FILE_VERSION_MATCH                     0xFFFF10AE   //�ڴ���ļ��汾��ƥ��
#define GoE_MEMORYDB_FILE_CRC_ERROR                         0xFFFF10AF   //�ڴ���ļ�CRC����
#define GoE_MEMORYDB_FILE_FLAG_MATCH                        0xFFFF10B0   //�ڴ���ļ���־����
#define GoE_MEMORYDB_INEXISTENCE                            0xFFFF10B1   //�洢�ⲻ����
#define GoE_MEMORYDB_LOAD_FAILED                            0xFFFF10B2   //�洢�����ʧ��
#define GoE_NO_DATA_IN_INTERVAL                             0xFFFF10B3   //ָ���Ĳ�ѯ������û�����ݡ�
#define GoE_FILE_CREATED_FAIELD                             0xFFFF1004   //�ļ�����ʧ��
#define GoE_FILE_FLUSH_FAILED                               0xFFFF1005   //�ļ�ˢ��ʧ��
#define GoE_INVALID_WRITE_TYPE                              0xFFFF1006
#define GoE_MEMORYDB_WAIT_OUT                               0xFFFF1007   //�ڴ��ȴ���ʱ

#define GoE_CANT_LOAD_MEMORYDB                              0xFFFF10B4  // �������ڴ����ȡ����ϵ
#define GoE_QUERY_IN_WHITEDB                                0xFFFF10B5  // ��ѯ�ڴ������г����˴�������whitedb�ڲ�����
#define GoE_NO_DATABASE_MEMORYDB                            0xFFFF10B6  //��û���ҵ�ָ��������������Ӧ�ķֿ�
#define GoE_RECORD_NOT_GET                                  0xFFFF10B7  //  ��whitedb�л�ȡ��¼ʧ��
#define GoE_MEMORY_ALLOC_ERR                                0xFFFF10B8  //  �ڴ�����ڽ��տ��յĻ���������ʧ��
#define GoE_EVENT_CREATE_FAILED                             0xFFFF10B9  //  �����ڴ����ջ��������¼�����ʧ��
#define GoE_GET_POINT_FAILED                                0xFFFF10BA  //  ��ȡ��ǩ��ʧ��
#define GoE_MEMORY_INIT_FAILED                              0xFFFF10BB  //  �ڴ���ʼ��ʧ��
#define GoE_DATATYPE_NOT_MATCH                              0xFFFF10BC  //  �������Ͳ�ƥ��
#define GoE_GET_FIELD_ERR                                   0xFFFF10BD  //  ��whitedb��ȡ��¼���ֶ�ʱ�����˴���
#define GoE_MEMORYDB_INTERNAL_ERR                           0xFFFF10BE  //  whitedb�ڲ�δ֪����
#define GoE_MEMORYDB_RECORD_CREATED_FAILED                  0xFFFF10BF  //  �ڴ�ⴴ����¼ʧ��
#define GoE_PARSE_NORMAL_TYPE_SNAPSHOT_ERR                  0xFFFF10C0  //  ������ͨ�������͵Ŀ���ʧ��
#define GoE_PARSE_NAMED_TYPE_SNAPSHOT_ERR                   0xFFFF10C1  //  �����Զ����������͵Ŀ���ʧ��
#define GoE_STRING_BLOB_TYPE_UNSUPPORT_CALC_POINT           0xFFFF10C2  // string��blob���Ͳ�֧�ּ����
#define GoE_COOR_TYPE_UNSUPPORT_CALC_POINT                  0xFFFF10C3  // �������Ͳ�֧�ּ����
#define GoE_INCLUDE_HIS_DATA                                0xFFFF10C4  // ��¼����ʷ���ݣ���������Ч���ڵ�������
#define GoE_THREAD_CREATE_ERR                               0xFFFF10C5  // �̴߳���ʧ��
#define GoE_XML_CRC_ERROR                                   0xFFFF10C6  // xml�ļ�crcУ��ʧ��
#define GoE_OVERSIZE_INTERVALS                              0xFFFF10C7  // intervals >= system.ini���õĴ�С
#define GoE_DATETIMES_MUST_ASCENDING_ORDER                  0xFFFF10C8  // ʱ����밴��������
#define GoE_CANT_LOAD_PERF                                  0xFFFF10C9  // ����ͬ���ܼ�������ȡ����ϵ
#define GoE_PERF_TAG_NOT_FOUND                              0xFFFF10CA  // ���ܼ����㲻����
#define GoE_WAIT_DATA_EMPTY                                 0xFFFF10CB  //  ����Ϊ��
#define GoE_WAIT_DATA_FULL                                  0xFFFF10CC  //  ��������
#define GoE_DATA_TYPE_COUNT_LESS                            0xFFFF10CD  //
#define GoE_MEMORYDB_CREATE_FAILED                          0xFFFF10CE  //�ڴ�ⴴ��ʧ��
#define GoE_MEMORYDB_FIELD_ENCODE_FAILED                    0xFFFF10CF  //�ڴ���ֶα���ʧ��
#define GoE_RECORD_CREATE_FAILED                            0xFFFF10D0  //�ڴ���¼����ʧ��
#define GoE_REMOVE_RECORD_ERR                               0xFFFF10D1  //�ڴ���¼ɾ��ʧ��
#define GoE_MEMORYDB_FILE_OPEN_FIELD                        0xFFFF10D2  //�ڴ����ļ�ʧ��
#define GoE_MEMORYDB_FILE_WRITE_FAILED                      0xFFFF10D3  //�ڴ��д���ļ�ʧ��
#define GoE_FILTER_WTIH_FLOAT_AND_EQUAL                     0xFFFF10D4  //���и���������ʽ�в�����=��
#define GoE_DISPATCH_PLUGIN_NOT_EXSIT                       0xFFFF10D5  //ת�����������������
#define GoE_DISPATCH_PLUGIN_FILE_NOT_EXSIT					0xFFFF10D6  //ת�����������DLL�ļ�������
#define GoE_DISPATCH_PLUGIN_ALREADY_EXSIT					0xFFFF10D7  //ת������������Ѵ���
#define GoE_DISPATCH_REGISTER_PLUGIN_FAILURE				0xFFFF10D8  //���ע��ʧ��
#define GoE_DISPATCH_START_PLUGIN_FAILURE                   0xFFFF10D9  //�������ʧ��
#define GoE_DISPATCH_STOP_PLUGIN_FAILURE                    0xFFFF10DA  //ֹͣ���ʧ��
#define GoE_DISPATCH_SET_PLUGIN_ENABLE_STATUS_FAILURE       0xFFFF10DB  //���ò��״̬ʧ��
#define GoE_DISPATCH_GET_PLUGIN_COUNT_FAILURE               0xFFFF10DC  //��ȡ���������Ϣʧ��
#define GoE_DISPATCH_CONFIGFILE_NOT_EXIST					0xFFFF10DD    //ת�����������ļ�������
#define GoE_DISPATCH_CONFIG_DATA_PARSE_ERR					0xFFFF10DE    //ת�������������ݽ�������
#define GoE_DISPATCH_PLUGIN_ALREADY_RUNNING					0xFFFF10DF    //ת������������Ѿ�����
#define GoE_DISPATCH_PLUGIN_CANNOT_RUN						0xFFFF10E0    //ת�������������ֹ����
#define GoE_DISPATCH_PLUGIN_CONTAINER_UNRUN					0xFFFF10E1    //ת���������������δ����
#define GoE_DISPATCH_PLUGIN_INTERFACE_ERR					0xFFFF10E2    //ת������������ӿ�δʵ��
#define GoE_DISPATCH_PLUGIN_SAVE_CONFIG_ERR					0xFFFF10E3    //ת�����������������ļ�����
#define GoE_DISPATCH_PLUGIN_START_ERR						0xFFFF10E4	//ת���������������ʱʧ��
#define GoE_DISPATCH_PLUGIN_STOP_ERR						0xFFFF10E5	//ת�����������ֹͣʱʧ��
#define GoE_DISPATCH_PARSE_DATA_PAGE_ERR					0xFFFF10E6  //��֧�ֵ�����ҳ����
#define GoE_DISPATCH_NOT_RUN								0xFFFF10E7  //ת������δ����

#define GoE_PROTOCOLNOTIMPL                                 0xFFFF2001  // �û�����ı���δʵ��
#define GoE_CRCERROR                                        0xFFFF2002  // ����CRCУ�����
#define GoE_WRONG_USERPW                                    0xFFFF2003  // ��֤�û�������ʧ��
#define GoE_CHANGE_USERPW                                   0xFFFF2004  // �޸��û�������ʧ��
#define GoE_INVALID_HANDLE                                  0xFFFF2005  // ��Ч�ľ��
#define GoE_INVALID_SOCKET_HANDLE                           0xFFFF2006  // ��Ч���׽��־��
#define GoE_FALSE                                           0xFFFF2007  // ����δ�ɹ���ɣ�����ԭ��鿴С�����롣
#define GoE_SCAN_POINT_NOT_FOUND                            0xFFFF2008  // Ҫ����ʵĲɼ���ǩ�㲻���ڻ���Ч
#define GoE_CALC_POINT_NOT_FOUND                            0xFFFF2009  // Ҫ����ʵļ����ǩ�㲻���ڻ���Ч
#define GoE_REDUPLICATE_ID                                  0xFFFF200A  // �ظ��ı�ǩ���ʶ
#define GoE_HANDLE_SUBSCRIBED                               0xFFFF200B  // ����Ѿ�������
#define GoE_OTHER_SDK_DOING                                 0xFFFF200C  // ��һ��API����ִ��
#define GoE_BATCH_END                                       0xFFFF200D  // �ֶ����ݷ��ؽ���
#define GoE_AUTH_NOT_FOUND                                  0xFFFF200E  // �������Ӷβ�����
#define GoE_AUTH_EXIST                                      0xFFFF200F  // ���ӵ�ַ���Ѿ�λ�������б���
#define GoE_AUTH_FULL                                       0xFFFF2010  // �������Ӷ�����
#define GoE_USER_FULL                                       0xFFFF2011  // �û�����
#define GoE_VERSION_UNMATCH                                 0xFFFF2012  // ���Ļ����ݰ汾��ƥ��
#define GoE_INVALID_PRIV                                    0xFFFF2013  // ��Ч��Ȩ��
#define GoE_INVALID_MASK                                    0xFFFF2014  // ��Ч����������
#define GoE_INVALID_USERNAME                                0xFFFF2015  // ��Ч���û���
#define GoE_INVALID_MARK                                    0xFFFF2016  // �޷�ʶ��ı���ͷ���
#define GoE_UNEXPECTED_METHOD                               0xFFFF2017  // �������Ϣ ID
#define GoE_INVALID_PARAM_INDEX                             0xFFFF2018  // ��Ч��ϵͳ��������ֵ
#define GoE_DECODE_PACKET_ERROR                             0xFFFF2019  // �������
#define GoE_ENCODE_PACKET_ERROR                             0xFFFF201A  // �������
#define GoE_BLACKLIST_FULL                                  0xFFFF201B  // ��ֹ���Ӷ�����
#define GoE_BLACKLIST_EXIST                                 0xFFFF201C  // ���ӵ�ַ���Ѿ�λ�ں�������
#define GoE_BLACKLIST_NOT_FOUND                             0xFFFF201D  // ��ֹ���Ӷβ�����
#define GoE_IN_BLACKLIST                                    0xFFFF201E  // ���ӵ�ַλ�ں������У��������ܾ�
#define GoE_INCREASE_FILE_FAILED                            0xFFFF201F  // ��ͼ�����ļ�ʧ��
#define GoE_RPC_INTERFACE_FAILED                            0xFFFF2020  // Զ�̹��̽ӿڵ���ʧ��
#define GoE_CONNECTION_FULL                                 0xFFFF2021  // ��������
#define GoE_ONE_CLIENT_CONNECTION_FULL                      0xFFFF2022  // �����Ѵﵽ�����ͻ������������������ֵ
#define GoE_SERVER_CLUTTER_POOL_NOT_ENOUGH                  0xFFFF2023  // �������ݽ����ռ䲻��
#define GoE_EQUATION_CLUTTER_POOL_NOT_ENOUGH                0xFFFF2024  // ʵʱ����ʽ�����ռ䲻��
#define GoE_NAMED_TYPE_NAME_LEN_ERROR                       0xFFFF2025  // �Զ������͵����ƹ���
#define GoE_NAMED_TYPE_LENGTH_NOT_MATCH                     0xFFFF2026  // ��ֵ�������Զ������͵Ķ��岻��
#define GoE_CAN_NOT_UPDATE_SUMMARY                          0xFFFF2027  // �޷�������������
#define GoE_TOO_MANY_ARVEX_FILE                             0xFFFF2028  // �����ļ�̫�࣬�޷��������������ļ�
#define GoE_NOT_SUPPORTED_FEATURE                           0xFFFF2029  // ���԰汾����ʱ��֧�ִ˹���
#define GoE_ENSURE_ERROR                                    0xFFFF2030  // ��֤��Ϣʧ�ܣ���ϸ��Ϣ��鿴���ݿ���־
#define GoE_OPERATOR_IS_CANCEL                              0xFFFF2031  // ������ȡ��
#define GoE_MSGBODY_REV_ERROR                               0xFFFF2032  // ���������ʧ��
#define GoE_UNCOMPRESS_FAILED							    0xFFFF2033  // ��ѹ��ʧ��
#define GoE_COMPRESS_FAILED									0xFFFF2034  // ѹ��ʧ��
#define GoE_SUBSCRIBE_ERROR                                 0xFFFF2035  // ����ʧ�ܣ�ǰһ�������߳���δ�˳������Ժ�����
#define GoE_SUBSCRIBE_CANCEL_ERROR                          0xFFFF2036  // ȡ������ʧ��
#define GoE_SUBSCRIBE_CALLBACK_FAILED                       0xFFFF2037  // ���Ļص������в��ܵ���ȡ�����ġ��Ͽ�����
#define GoE_SUBSCRIBE_GREATER_MAX_COUNT                     0xFFFF2038  // ���������ӿɶ��ı�ǩ������



// Windows Socket Errors
#define GoE_NET_ERROR                                       0xFFFF7000  // ����������ʼֵ
#define GoE_SOCK_WSAEINTR                                   0xFFFF7004  // �����������ñ� WSACancelBlockingCall() ����ȡ��
#define GoE_SOCK_WSAEACCES                                  0xFFFF700D  // �����ַ�ǹ㲥��ַ��������Ӧ�� flags û����
#define GoE_SOCK_WSAEFAULT                                  0xFFFF700E  // �Ƿ��ڴ����
#define GoE_SOCK_WSAEMFILE                                  0xFFFF7018  // �޶��������������
#define GoE_SOCK_WSAEWOULDBLOCK                             0xFFFF7023  // �׽��ֱ���ʶΪ����������������������
#define GoE_SOCK_WSAEINPROGRESS                             0xFFFF7024  // һ�������� Windows Sockets �������ڽ���
#define GoE_SOCK_WSAEALREADY                                0xFFFF7025  // һ���������� connect() �����Ѿ���ָ�����׽����Ͻ���
#define GoE_SOCK_WSAENOTSOCK                                0xFFFF7026  // �����������׽���������
#define GoE_SOCK_WSAEDESTADDRREQ                            0xFFFF7027  // Ҫ��δָ����Ŀ�ĵ�ַ
#define GoE_SOCK_WSAEMSGSIZE                                0xFFFF7028  // �׽���Ϊ������Ϣ�ģ���Ϣ̫�󣨴��ڵײ㴫��֧�ֵ����ֵ��
#define GoE_SOCK_WSAEPROTOTYPE                              0xFFFF7029  // �Դ��׽�����˵��ָ��Э���Ǵ��������
#define GoE_SOCK_WSAEPROTONOSUPPORT                         0xFFFF702B  // ��֧��ָ��Э��
#define GoE_SOCK_WSAESOCKTNOSUPPORT                         0xFFFF702C  // �ڴ˵�ַ���в�֧��ָ���׽�������
#define GoE_SOCK_WSAEOPNOTSUPP                              0xFFFF702D  // MSG_OOB ��ָ���������׽��ֲ���������
#define GoE_SOCK_WSAEAFNOSUPPORT                            0xFFFF702F  // ��֧��ָ���ĵ�ַ��
#define GoE_SOCK_WSAEADDRINUSE                              0xFFFF7030  // �׽��ֵı��ص�ַ�ѱ�ʹ��
#define GoE_SOCK_WSAEADDRNOTAVAIL                           0xFFFF7031  // Զ�̵�ַ�Ƿ�
#define GoE_SOCK_WSAENETDOWN                                0xFFFF7032  // Windows Sockets ��⵽����ϵͳ�Ѿ�ʧЧ
#define GoE_SOCK_WSAENETUNREACH                             0xFFFF7033  // �����޷���������
#define GoE_SOCK_WSAENETRESET                               0xFFFF7034  // �ڲ�������ʱ keep-alive ���⵽һ��ʧ�ܣ����ӱ��ж�
#define GoE_SOCK_WSAECONNABORTED                            0xFFFF7035  // ������ʱ������ʧ�ܶ��ж�
#define GoE_SOCK_WSAECONNRESET                              0xFFFF7036  // ���ӱ���λ
#define GoE_SOCK_WSAENOBUFS                                 0xFFFF7037  // �޻������ռ����
#define GoE_SOCK_WSAEISCONN                                 0xFFFF7038  // �����ѽ���
#define GoE_SOCK_WSAENOTCONN                                0xFFFF7039  // �׽���δ��������
#define GoE_SOCK_WSAESHUTDOWN                               0xFFFF703A  // �׽����� shutdown�������ѶϿ�
#define GoE_SOCK_WSAETIMEDOUT                               0xFFFF703C  // ��������ʱ��δ�ܽ�������
#define GoE_SOCK_WSAECONNREFUSED                            0xFFFF703D  // ���ӱ��ܾ�
#define GoE_SOCK_WSAECLOSE                                  0xFFFF703E  // ���ӱ��ر�
#define GoE_SOCK_WSANOTINITIALISED                          0xFFFF705D  // Windows Sockets DLL δ��ʼ��

// C error number from errno
#define GoE_C_ERRNO_ERROR                                   0xFFFF8000  // C����errno�������ʼֵ
#define GoE_C_ERRNO_EPERM                                   0xFFFF8001  // operation not permitted
#define GoE_C_ERRNO_ENOENT                                  0xFFFF8002  // no such file or directory
#define GoE_C_ERRNO_ESRCH                                   0xFFFF8003  // no such process
#define GoE_C_ERRNO_EINTR                                   0xFFFF8004  // interrupted
#define GoE_C_ERRNO_EIO                                     0xFFFF8005  // io error
#define GoE_C_ERRNO_ENXIO                                   0xFFFF8006  // no such device or address
#define GoE_C_ERRNO_E2BIG                                   0xFFFF8007  // argument list too long
#define GoE_C_ERRNO_ENOEXEC                                 0xFFFF8008  // exec format error
#define GoE_C_ERRNO_EBADF                                   0xFFFF8009  // bad file descriptor
#define GoE_C_ERRNO_ECHILD                                  0xFFFF800A  // no child process
#define GoE_C_ERRNO_EAGAIN                                  0xFFFF800B  // resource unavailable try again
#define GoE_C_ERRNO_ENOMEM                                  0xFFFF800C  // not enough memory
#define GoE_C_ERRNO_EACCES                                  0xFFFF800D  // permission denied
#define GoE_C_ERRNO_EFAULT                                  0xFFFF800E  // bad address
#define GoE_C_ERRNO_EBUSY                                   0xFFFF8010  // device or resource busy
#define GoE_C_ERRNO_EEXIST                                  0xFFFF8011  // file exists
#define GoE_C_ERRNO_EXDEV                                   0xFFFF8012  // cross device link
#define GoE_C_ERRNO_ENODEV                                  0xFFFF8013  // no such device
#define GoE_C_ERRNO_ENOTDIR                                 0xFFFF8014  // not a directory
#define GoE_C_ERRNO_EISDIR                                  0xFFFF8015  // is a directory
#define GoE_C_ERRNO_EINVAL                                  0xFFFF8016  // invalid argument
#define GoE_C_ERRNO_ENFILE                                  0xFFFF8017  // too many files open in system
#define GoE_C_ERRNO_EMFILE                                  0xFFFF8018  // too many files open
#define GoE_C_ERRNO_ENOTTY                                  0xFFFF8019  // inappropriate io control operation
#define GoE_C_ERRNO_EFBIG                                   0xFFFF801A  // file too large
#define GoE_C_ERRNO_ENOSPC                                  0xFFFF801B  // no space on device
#define GoE_C_ERRNO_ESPIPE                                  0xFFFF801C  // invalid seek
#define GoE_C_ERRNO_EROFS                                   0xFFFF801D  // read only file system
#define GoE_C_ERRNO_EMLINK                                  0xFFFF801F  // too many links
#define GoE_C_ERRNO_EPIPE                                   0xFFFF8020  // broken pipe
#define GoE_C_ERRNO_EDOM                                    0xFFFF8021  // argument out of domain
#define GoE_C_ERRNO_ERANGE                                  0xFFFF8022  // result out of range
#define GoE_C_ERRNO_EDEADLK                                 0xFFFF8024  // resource deadlock would occur
#define GoE_C_ERRNO_ENAMETOOLONG                            0xFFFF8026  // filename too long
#define GoE_C_ERRNO_ENOLCK                                  0xFFFF8027  // no lock available
#define GoE_C_ERRNO_ENOSYS                                  0xFFFF8028  // function not supported
#define GoE_C_ERRNO_ENOTEMPTY                               0xFFFF8029  // directory not empty

#define GoE_C_ERRNO_EILSEQ                                  0xFFFF802A  // illegal byte sequence
#define GoE_C_ERRNO_STRUNCATE                               0xFFFF8050  // a string copy of concatenation resulted in a truncated string

/* POSIXGoE_C_ERRNO_ESUPPLEMENT */
#define GoE_C_ERRNO_EADDRINUSE                              0xFFFF8064  // address in use
#define GoE_C_ERRNO_EADDRNOTAVAIL                           0xFFFF8065  // address not available
#define GoE_C_ERRNO_EAFNOSUPPORT                            0xFFFF8066  // address family not supported
#define GoE_C_ERRNO_EALREADY                                0xFFFF8067  // connection already in progress
#define GoE_C_ERRNO_EBADMSG                                 0xFFFF8068  // bad message
#define GoE_C_ERRNO_ECANCELED                               0xFFFF8069  // operation canceled
#define GoE_C_ERRNO_ECONNABORTED                            0xFFFF806A  // connection aborted
#define GoE_C_ERRNO_ECONNREFUSED                            0xFFFF806B  // connection refused
#define GoE_C_ERRNO_ECONNRESET                              0xFFFF806C  // connection reset
#define GoE_C_ERRNO_EDESTADDRREQ                            0xFFFF806D  // destination address required
#define GoE_C_ERRNO_EHOSTUNREACH                            0xFFFF806E  // host unreachable
#define GoE_C_ERRNO_EIDRM                                   0xFFFF806F  // identifier removed
#define GoE_C_ERRNO_EINPROGRESS                             0xFFFF8070  // operation in progress
#define GoE_C_ERRNO_EISCONN                                 0xFFFF8071  // already connected
#define GoE_C_ERRNO_ELOOP                                   0xFFFF8072  // too many synbolic link levels
#define GoE_C_ERRNO_EMSGSIZE                                0xFFFF8073  // message size
#define GoE_C_ERRNO_ENETDOWN                                0xFFFF8074  // network down
#define GoE_C_ERRNO_ENETRESET                               0xFFFF8075  // network reset
#define GoE_C_ERRNO_ENETUNREACH                             0xFFFF8076  // network unreachable
#define GoE_C_ERRNO_ENOBUFS                                 0xFFFF8077  // no buffer space
#define GoE_C_ERRNO_ENODATA                                 0xFFFF8078  // no message available
#define GoE_C_ERRNO_ENOLINK                                 0xFFFF8079  // no link
#define GoE_C_ERRNO_ENOMSG                                  0xFFFF807A  // no message
#define GoE_C_ERRNO_ENOPROTOOPT                             0xFFFF807B  // no protocol option
#define GoE_C_ERRNO_ENOSR                                   0xFFFF807C  // no stream resources
#define GoE_C_ERRNO_ENOSTR                                  0xFFFF807D  // not a stream
#define GoE_C_ERRNO_ENOTCONN                                0xFFFF807E  // not connected
#define GoE_C_ERRNO_ENOTRECOVERABLE                         0xFFFF807F  // state not recoverable
#define GoE_C_ERRNO_ENOTSOCK                                0xFFFF8080  // not a socket
#define GoE_C_ERRNO_ENOTSUP                                 0xFFFF8081  // not supported
#define GoE_C_ERRNO_EOPNOTSUPP                              0xFFFF8082  // operation not supported
#define GoE_C_ERRNO_EOTHER                                  0xFFFF8083  // other
#define GoE_C_ERRNO_EOVERFLOW                               0xFFFF8084  // value too large
#define GoE_C_ERRNO_EOWNERDEAD                              0xFFFF8085  // owner dead
#define GoE_C_ERRNO_EPROTO                                  0xFFFF8086  // protocol error
#define GoE_C_ERRNO_EPROTONOSUPPORT                         0xFFFF8087  // protocol not supported
#define GoE_C_ERRNO_EPROTOTYPE                              0xFFFF8088  // wrong protocol type
#define GoE_C_ERRNO_ETIME                                   0xFFFF8089  // stream timeout
#define GoE_C_ERRNO_ETIMEDOUT                               0xFFFF808A  // timed out
#define GoE_C_ERRNO_ETXTBSY                                 0xFFFF808B  // text file busy
#define GoE_C_ERRNO_EWOULDBLOCK                             0xFFFF808C  // operation would block

#define GoE_IPC_ERROR                                       0xFFFFC000  // ipc error begin
#define GoE_IPC_ERROR_END                                   0xFFFFC09F  // ipc error end

#endif /* __GOLDEN_ERROR_H__ */
